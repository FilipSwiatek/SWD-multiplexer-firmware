import os
import serial
import time


def jlink_download(targetname='STM32F103C8', hexname='arm.hex'):
    jlink_script = open('script.jlink', 'w')  # open J-Link script file
    jlink_script.write('h\nerase\nloadfile ' + hexname + '\nr\nq')  # fulfil J-Link script file
    jlink_script.close()  # close J-Link script file
    os.system('jlink -device ' + targetname + ' -if SWD -speed 4000 -autoconnect 1 -CommanderScript script.jlink')  # execute J-Link erase&flash command based on J-Link script file
    os.remove("script.jlink")  # remove J-Link script file

debug_print = 1

class Multiplexer:
    def __init__(self, com_port='COM1'):
        self.serial = serial.Serial(com_port, 115200, timeout=0.1)  # open serial port
        self._target_no = 0

    def __del__(self):
        self.serial.close()

    def select_target(self, target_no):
        if target_no < 0 or target_no > 7:
            return 0
        self._target_no = target_no
        self.serial.write(b'select ' + str(self._target_no).encode('utf-8') + b'\n')
        print('selecting target #' + str(self._target_no))
        feedback = self.serial.readline().decode()
        if feedback != 'OK':  # resend if error
            self.serial.write(b'select ' + str(self._target_no).encode('utf-8') + b'\n')
        print(self.serial.readline().decode())

    def reset_all(self, state=''):
        self.serial.write(b'reset_all ' + state.encode('utf-8') + b'\n')
        print('reseting all targets with option:', state)
        feedback = self.serial.readline().decode()
        if feedback != 'OK':  # resend if error
            self.serial.write(b'reset_all ' + state.encode('utf-8') + b'\n')
        print(self.serial.readline().decode())


def select_test(mux):
    for i in range(8):
        mux.select_target(i)
        time.sleep(0.1)

    for i in range(7, -1, -1):
        mux.select_target(i)
        time.sleep(0.1)


def download_test(mux, target_no=0, target_name='STM32F103C8', hex_name='arm.hex'):
    mux.select_target(target_no)
    jlink_download(target_name, hex_name)


def reset_test(mux):
    mux.reset_all('set')
    time.sleep(0.5)
    mux.reset_all('clear')
    time.sleep(0.5)
    mux.reset_all()


def test(mux_handle, binary, target_device='?'):
    select_test(mux_handle)
    reset_test(mux_handle)

    download_test(mux_handle, 0, target_device, binary)
    download_test(mux_handle, 1, target_device, binary)


target = 'EZR32WG330F256RXX'
target_binary = 'target.hex'
connected_mux = Multiplexer('COM18')

test(connected_mux, target_binary, target)

connected_mux.__del__()



