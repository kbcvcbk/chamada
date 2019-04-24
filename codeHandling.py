import serial as srl

def stripCode(num, debug=False):
    code_size = num&15
    if debug: print("code_size:", code_size)
    return (num >> 4, code_size - 2)

def parseCode(num, code_size, sep_ans=True, debug=False):
    if debug: print(f"num = {num}")
    code = str()
    if debug: print(f"code size = {code_size}")
    if debug: print(f"num2parse = {num:b}")

    for i in range(code_size):
        if (i == 1) and (sep_ans): code += " "
        cur = (num >> (2*i))&3
        if debug:
            print("i = {0}\nnum = {1:b}\nnum&3: {2}".format(
                i, (num >> 2*i), (num >> 2*i)&3
                ))
        if   cur == 0: code += "A"
        elif cur == 1: code += "B"
        elif cur == 2: code += "C"
        elif cur == 3: code += "D"
    return code[::-1]
