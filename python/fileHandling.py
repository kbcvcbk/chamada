import codeHandling as ch
import os
import time

def genTurma(name, filename):
    with open(filename) as al_file:
        al_list = dict()
        idx = 0
        for line in al_file:
            al_list[ch.parseCode(idx, 4, False)] = line.strip()
            idx += 1
    with open(name+".tur", "w") as al_codes:
        for code in al_list.keys():
            print("aluno:", al_list[code])
            print("código:", code)
            print("-------------")
            al_codes.write(code+","+al_list[code]+"\n")

def loadTurma(name):
    al_list = dict()
    with open(name+".tur") as tur_file:
        for aluno in tur_file:
            aluno = aluno.split(",")
            al_list[aluno[0]] = al_list[aluno[1]]
    return al_list

def doChamada(turma):
    with open(time.strftime("[%y]%d-%m.cha")) as resps:
        for line in resps:
            presente.append(line.split(",")[0].split(" ")[0])
    for aluno in al_list.keys():
        if aluno in presente:
            print(al_list[aluno], "presente")
        else:
            print(al_list[aluno], "faltou")

            
al = genTurma("p1", "alunos.txt")
for aluno in al.items():
    print(aluno)
