import serial.tools.list_ports as list_ports
import serial as srl
import codeHandling as ch
import os
import time

reading = False

def findPorts():
    ardus = list()
    for p in list(list_ports.comports()):
        if "Arduino" in p[1]:
            ardus.append(srl.Serial(p[0], 9600, timeout=1))
    return ardus

def readSerial(ardus, timeto=30):
    stop_at = time.time()+timeto
    print("stop_at:", stop_at)
    while time.time() < stop_at:
        print("time:", time.time())
        for ardu in ardus:
            line = ardu.readline()
            if line != b"":
                writeCode(line.strip())

def writeCode(code):
    with open(time.strftime("[%y]%d-%m.cha"), "a") as file:
        file.write("{0},{1}\n".format(ch.parseCode(code, 5), time.strftime("%H:%M:%S")))

def main():
    readSerial(findPorts(),10)

if __name__ == "__main__":
    main()
