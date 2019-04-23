import serial.tools.list_ports as list_ports
import serial as srl
import time

reading = False

def flipRead(): reading = !reading

def findPorts():
    ardus = list()
    for p in list(list_ports.comports()):
        if "Arduino" in p[1]:
            ardus.append(srl.Serial(p[0], 9600, timeout=1))
    return ardus

def readSerial(ardus):
    while true:
        if reading == False:
            break
        for ardu in ardus:
            line = ardu.readline()
            if line != b"":
                writeCode(line.strip())

def writeCode(code):
    with open("[%y]%d-%m", "a") as file:
        file.write("{0},{1}\n".format(code, time.strftime("%H:%M:%S"))
