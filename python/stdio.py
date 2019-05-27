from sys import stdout
from time import sleep

stdout.write("something")
stdout.flush()
sleep(0.5)
for i in range(3):
    stdout.write(".")
    stdout.flush()
    sleep(0.2)
stdout.write("\r...else...  ")
stdout.flush()
stdout.write("\r            \r")

def slowtype(string, time=0.3):
    for char in string:
        stdout.write(char)
        stdout.flush()
        sleep(time)
slowtype("hello world.", 0.1)
stdout.write("\r            \r")

with open("aq_logo") as logo:
    aq = logo.read()
slowtype(aq, 0.01)

stdout.write("\n")
