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
from os import path,chdir
from bcrypt import hashpw,gensalt

path_current_file = path.abspath(__file__)
path_current_dir = path_current_file [:path_current_file.rfind("/")]
shadow_file = path_current_dir + "/shadow"

def read_file():
    """Open shadow file as a {user: password} dict and returns the dict"""
    passw = dict()
    with open(shadow_file, "rb") as db_file:
        for linha in db_file:
            dados = linha.strip().split(b",")
            user = dados[0].decode("utf-8")
            pw = dados[1]
            passw[user] = pw
    return passw

def write_file(passw):
    """Write a {user: password} dict into the shadow file"""
    with open(shadow_file, "wb") as db_file:
        for key in passw.keys():
            user = bytes(key, "UTF-8")
            pw = passw[key]
            line = user + b"," + pw + b"\n"
            db_file.write(line)

def register(username, password):
    db = read_file()
    db[username] = hashpw(bytes(password, "utf-8"), gensalt())
    write_file(db)

def login(*args):
    from getpass import getpass
    db = read_file()
    if len(args) > 0 and type(args[0]) == str:
        username = args[0]
    else:
        username = input("User: ")
    if not username in db.keys():
        print("Usuário inválido")
        return ""
    target = db[username]
    password = getpass("Pass: ")
    attempt = hashpw(bytes(password, "utf-8"), target)
    if attempt == target:
        print("Olá,", username)
        return username
    else:
        print("Senha inválida")
        return ""

def user_register(*args):
    from getpass import getpass
    name = input("User: ")
    email = input("Email: ")
    fpw, spw = 0, 1
    while fpw != spw:
        fpw = getpass("Pass: ")
        spw = getpass("Confirm pass: ")
    register(name, fpw)
    return (name, email)
    
user = ""

def main():
    commands = {
            "login": login,
            "register": user_register }
    prompt = "> "
    print("""=== AQ! Command Line Interface ===
    Please type register or login""")
    while True:
        inp = input(prompt).split()
        if inp[0] in commands:
            commands[inp[0]](*inp[1:])
        elif inp[0] == "exit":
            break
        else:
            print("Invalid usage")

if __name__ == "__main__":
    main()
