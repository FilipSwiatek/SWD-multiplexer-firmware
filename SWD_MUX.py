import os
import serial
import time


def jlink_download(targetname='STM32F103C8', hexname='arm.hex'):
    jlink_script = open('script.jlink', 'w')  # open J-Link script file
    jlink_script.write('h\nerase\nloadfile ' + hexname + '\nr\nq')  # fulfil J-Link script file
    jlink_script.close()  # close J-Link script file
    os.system('jlink -device ' + targetname + ' -if SWD -speed 4000 -autoconnect 1 -CommanderScript script.jlink')  # execute J-Link erase&flash command based on J-Link script file
    os.remove("script.jlink")  # remove J-Link script file


class Multiplexer:
    def __init__(self, com_port):
        self.serial = serial.Serial(com_port, 115200, timeout=0.1)  # open serial port
        self._target_no = 0

    def __del__(self):
        self.serial.close()

    def select_target(self, target_no):
        if target_no < 0 or target_no > 7:
            return 0
        self._target_no = target_no
        self.serial.write(b'select ' + str(self._target_no).encode('utf-8') + b'\n\r')

    def reset_all(self, state=''):
        self.serial.write(b'reset_all ' + state.encode('utf-8') + b'\n\r')


def select_test(com_port='COM1'):
    mux = Multiplexer(com_port)
    for i in range(8):
        mux.select_target(i)
        time.sleep(0.1)


def download_test(target_no=0, target_name='STM32F103C8', hex_name = 'arm.hex', com_port='COM1'):
    mux = Multiplexer(com_port)
    mux.select_target(target_no)
    jlink_download(target_name, hex_name)


def reset_test(com_port='COM1'):
    mux = Multiplexer(com_port)
    mux.reset_all()
    time.sleep(0.2)
    mux.reset_all('set')
    time.sleep(0.5)
    mux.reset_all('clear')


select_test()
reset_test()
download_test()
