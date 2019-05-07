import serial.tools.list_ports as list_ports
import serial as srl
import time
import sys
import os

def findPorts():        # essa função lê a portas e acha os arduinos conectados
    ardus = list()
    for p in list(list_ports.comports()):
        if "Arduino" in p[1]:
            ardus.append(srl.Serial(p[0], 9600, timeout=1))
    return ardus

def readSerial(timeto):     # essa função lê as seriais conectadas uma por uma
                            # e gera um dicionário com os alunos e suas respostas
    print("\nPrepare-se para inserir as respostas! :)\n")
    time.sleep(3)
    ardus = findPorts()
    chamada = dict()
    stop_at = time.time()+timeto
    while time.time() < stop_at:
        sys.stdout.write("\rtime remaining: {:.1f}".format(stop_at - time.time()))
        sys.stdout.flush()
        for ardu in ardus:
            line = ardu.readline()
            if line != b"":
                chamada[str(line)[2:6]] = [str(line)[7], time.strftime("%m/%d-%H:%M:%S")]
    return chamada

def saveChamada(chamada):       # salva as respostas num arquivo log.cha
    with open("log.cha", "a") as log:
        log.write(time.strftime("======== RESPOSTAS %d/%m/%y - %H:%M ========\n"))
        for code in chamada:
            log.write(code+","+chamada[code][0]+","+chamada[code][1]+"\n")
    return chamada

def loadAlunos():       # carrega a lista de alunos de um arquivo "aluno.txt"
                        # e retorna um dicionário com alunos e códigos
    with open("alunos.txt") as alunos_file:
        alunos = dict()
        idx = 0
        for line in alunos_file:
            code = parseCode(idx)
            alunos[code] = str(line).strip()
            idx += 1
            print("aluno: "+line.strip())
            print("code:  "+code.strip())
            print("----------------")
    return alunos

def parseCode(num, debug=False):    # gera um código de code_size dígitos dado
                                    # um número qualquer
    code_size = 4
    if debug: print(f"num = {num}")
    code = str()
    if debug: print(f"code size = {code_size}")
    if debug: print(f"num2parse = {num:b}")

    for i in range(code_size):
        cur = (num >> (2*i))&3
        if debug:
            print("i = {0}\nnum = {1:b}\nnum&3: {2}".format(i, (num >> 2*i), (num >> 2*i)&3))
        if   cur == 0: code += "A"
        elif cur == 1: code += "B"
        elif cur == 2: code += "C"
        elif cur == 3: code += "D"
    return code[::-1]

def doChamada(alunos, chamada):     # confere quais alunos da lista responderam
                                    # a pergunta
    print(time.strftime("\n\n === Chamada do dia %d/%m ==="))
    for code in alunos.keys():
        if code in chamada.keys():
            status = "P"
        else:
            status = "F"
        print(alunos[code]+": "+status)


def main():                     # programa principal
    alunos = loadAlunos()
    tempo = float(input("\nQuanto tempo de chamada, anjo? (em segundos)\n"))
    print("\nMassa! Começando...")
    time.sleep(1)
    chamada = saveChamada(readSerial(tempo))
    doChamada(alunos, chamada)

if __name__ == "__main__":
    main()
