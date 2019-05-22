'''
## login.py ##
# by kbcv

func login(user, password) -> True if match, false otherwise
func register(user, password) -> True if success, false otherwise
csv shadow {
    username,password
}

depende:
    bcrypt

todo:
    [x] sistema básico
    [ ] validação de senha (tamanho, letra+número)

referencias:
    https://www.youtube.com/watch?v=O6cmuiTBZV - so que é que esse modulo faz?
    https://www.youtube.com/watch?v=hNa05wr0DS - tutorial python bcrypy
    https://github.com/pyca/bcrypt/            - bcrypt documentation
'''
from os import chdir
from bcrypt import hashpw,gensalt

def read_file():
    passw = dict()
    with open("shadow", "rb") as db_file:
        for linha in db_file:
            dados = linha.strip().split(b",")
            user = dados[0].decode("utf-8")
            pw = dados[1]
            passw[user] = pw
    return passw

def write_file(passw):
    with open("shadow", "wb") as db_file:
        for key in passw.keys():
            user = bytes(key, "UTF-8")
            pw = passw[key]
            line = user + b"," + pw + b"\n"
            db_file.write(line)

def register(username, password):
    db = read_file()
    db[username] = hashpw(bytes(password, "utf-8"), gensalt())
    write_file(db)

def login(username, password):
    db = read_file()
    if not username in db.keys():
        print("Usuário inválido")
        return False
    target = db[username]
    attempt = hashpw(bytes(password, "utf-8"), target)
    if attempt == target:
        print("Olá,", username)
        return True
    else:
        print("Senha inválida")
        return False
