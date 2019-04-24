import code_translate as co

def genTurma(name, filename):
    with open(filename) as al_file:
        al_list = dict()
        idx = 0
        for line in al_file:
            al_list[co.parseCode(idx, False)] = line.strip()
            idx += 1
            return al_list
##    with open("turma"+name, "w") as al_codes:
##        for aluno in al_list:

al = genTurma("p1", "alunos.txt")
for aluno in al.items():
    print(aluno)
