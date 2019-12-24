import os
import serial
import time


class Target:
    def __init__(self, hex_file, device_name):
        self.hex_file = hex_file
        self.device_name = device_name


def jlink_download(targetname, hexname, erase=True, speed=4000):

    jlink_script = open('script.jlink', 'w')  # open J-Link script file
    jlink_script.write('h\n')
    if erase:
        jlink_script.write('erase\n')
    jlink_script.write('loadfile ' + hexname + '\nr\nq')  # fulfil J-Link script file
    # close J-Link script file
    jlink_script.close()
    # execute J-Link erase&flash command based on J-Link script file
    os.system('jlink -device '
              + targetname +
              ' -if SWD -speed ' + str(speed) +
              ' -autoconnect 1 -CommanderScript script.jlink > jlink.log')
    # remove J-Link script file
    os.remove("script.jlink")
    #searching for special strings in J-link log to recognize failure
    ret = 0
    jlink_log = open('jlink.log', 'r')
    if 'Cannot connect to target.' in jlink_log.read():
        ret = 1

    jlink_log.close()
    os.remove('jlink.log')
    return ret


class Multiplexer:
    def __init__(self, targets_list, com_port='COM1'):
        self.serial = serial.Serial(com_port, 115200, timeout=0.1)  # open serial port
        self._target_no = 0
        self.serial.write(b'\n')
        self.serial.read(2137)
        self.targets_list = targets_list

    def __del__(self):
        self.serial.close()

    def select_target(self, target_no):
        if target_no < 0 or target_no > 7:
            return 0
        self._target_no = target_no
        feedback = 'ERR'
        sending_counter = 0
        while 'OK' not in feedback:
            self.serial.write(b'select ' + str(self._target_no).encode('utf-8') + b'\n')
            print('selecting target #' + str(self._target_no))
            feedback = self.serial.readline().decode()
            sending_counter += 1
            assert (sending_counter < 4), 'more than 4 resends of command'

    def reset_one(self, target_no, state='pulse'):
        self.select_target(target_no)
        jlink_script = open('script.jlink', 'w')  # open J-Link script file
        if state == 'set' or state == 'push' or state == 'pulse':
            jlink_script.write('r0\n')  # turn on 'reset' signal
        else:
            jlink_script.write('r1\n')  # turn off 'reset' signal
        jlink_script.write('q\n')  # quit J-Link script
        # close J-Link script file
        jlink_script.close()
        # execute J-Link reset set/reset depending on 'state' argument
        os.system('jlink -CommanderScript script.jlink > jlink.log')
        if state == 'pulse':
            jlink_script = open('script.jlink', 'w')  # open J-Link script file
            jlink_script.write('r1\n')  # turn off 'reset' signal
            jlink_script.write('q\n')  # quit J-Link script
            # close J-Link script file
            jlink_script.close()
            # execute J-Link erase&flash command based on J-Link script file
            os.system('jlink -CommanderScript script.jlink > jlink.log')
        # remove J-Link script file
        os.remove("script.jlink")
        os.remove('jlink.log')

    def reset_all(self, state=''):
        feedback = 'ERR'
        sending_counter = 0
        while 'OK' not in feedback:
            self.serial.write(b'reset_all ' + state.encode('utf-8') + b'\n')
            print('reseting all targets with option:', state)
            feedback = self.serial.readline().decode()
            sending_counter += 1
            assert (sending_counter < 4), 'more than 2 resends of command'

    def select_and_download(self, target_no, erase=True, speed=4000):
        assert target_no <= len(self.targets_list), "can't download unspecified binary to unspecified target"
        self.select_target(target_no)
        return jlink_download(self.targets_list[target_no].device_name,
                               self.targets_list[target_no].hex_file, erase, speed)


def select_test(mux):
    for i in range(8):
        mux.select_target(i)
        time.sleep(0.1)

    for i in range(7, -1, -1):
        mux.select_target(i)
        time.sleep(0.1)


def reset_test(mux):
    mux.reset_all('set')
    time.sleep(0.1)
    mux.reset_all('clear')
    time.sleep(0.1)
    mux.reset_all()
    time.sleep(0.1)
    mux.reset_one(5, 'pulse')



def test(mux):
    select_test(mux)
    reset_test(mux)

    tests_per_port = 10

    for current_port in range(len(mux.targets_list)):
        errors_per_port = 0
        for x in range(tests_per_port):
            errors_per_port += mux.select_and_download(current_port)
        print('errors per port #' + str(current_port) + ' =', errors_per_port)


multiplexer_handle = Multiplexer([Target('ezr.hex', 'EZR32WG330F256RXX'), Target('ezr.hex', 'EZR32WG330F256RXX')],
                                 'COM18')
test(multiplexer_handle)
