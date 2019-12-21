import os
import serial
import time


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
              ' -autoconnect 1 -CommanderScript script.jlink >> jlink.log')
    # remove J-Link script file
    os.remove("script.jlink")
    #searching for special strings in J-link log to recognize failure
    ret = 0
    jlink_log = open('jlink.log', 'r')
    if 'Cannot connect to target.' in jlink_log.read():
        ret = 1

    jlink_log.close()
    #os.remove('jlink.log')
    return ret



class Multiplexer:
    def __init__(self, com_port='COM1'):
        self.serial = serial.Serial(com_port, 115200, timeout=0.1)  # open serial port
        self._target_no = 0
        self.serial.write(b'\n')
        self.serial.read(2137)

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
            assert (sending_counter < 4), 'more than 2 resends of command'

    def reset_all(self, state=''):
        feedback = 'ERR'
        sending_counter = 0
        while 'OK' not in feedback:
            self.serial.write(b'reset_all ' + state.encode('utf-8') + b'\n')
            print('reseting all targets with option:', state)
            feedback = self.serial.readline().decode()
            sending_counter += 1
            assert (sending_counter < 4), 'more than 2 resends of command'


def select_test(mux):
    for i in range(8):
        mux.select_target(i)
        time.sleep(0.1)

    for i in range(7, -1, -1):
        mux.select_target(i)
        time.sleep(0.1)


def download_test(mux, target_name, hex_name, target_no, erase, speed):
    mux.select_target(target_no)
    jlink_download(target_name, hex_name, erase, speed)


def reset_test(mux):
    mux.reset_all('set')
    time.sleep(0.1)
    mux.reset_all('clear')
    mux.reset_all()


def select_and_download(mux, target_no, binary, target_device='?', erase=True, speed=4000):
    mux.select_target(target_no)
    return jlink_download(target_device, binary, erase, speed)


def test(mux, binary, target_device='?'):
    select_test(mux)
    reset_test(mux)
    tests_per_port = 10
    used_ports = 1
    for current_port in range(used_ports):
        errors_per_port = 0
        for x in range(tests_per_port):
            errors_per_port += select_and_download(mux, current_port, binary, target_device, True, 9000)
        print('errors per port #' + str(current_port) + ' =', errors_per_port)
