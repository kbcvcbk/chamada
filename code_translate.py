import serial as srl

comm = str(11)

def configComm(porta):
    global comm
    comm = str(porta)

def getCode(): 
    with srl.Serial("COM"+comm) as ardu:
        didntRead = True
        while didntRead:
            lineRead = ardu.readline()
            if lineRead != b'':
                didntRead = False
                return int(lineRead)

def parseCode(num, debug=False):
    if debug: print(f"num = {num:b}")
    code = str()
    codeSize = num&7
    if debug: print(f"code size = {codeSize}")
    num = num >> 4
    if debug: print(f"num2parse = {num:b}")

    for i in range(codeSize):
        if i == 1: code += " "
        cur = (num >> (2*i))&3
        if debug: print("i = {0}\nnum = {1:b}\nnum&3: {2}".format(i, (num >> 2*i), (num >> 2*i)&3))
        if   cur == 0: code += "A"
        elif cur == 1: code += "B"
        elif cur == 2: code += "C"
        elif cur == 3: code += "D"
    return code[::-1]
