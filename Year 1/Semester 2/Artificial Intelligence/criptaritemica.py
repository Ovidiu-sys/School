""" Aplicati algoritmul Hill Climbing pentru rezolvarea urmatorului puzzle de criptaritmetica: trei+doi=cinci"""

import random as rn

N = 10
cuv1 = "trei"
cuv2 = "doi"
cuv3 = "cinci"
litere = list(set(cuv1 + cuv2 + cuv3))
for i in range(len(litere), 10):
    litere.append('_')

def initializare():
    M = [i for i in range(N)]
    config = rn.sample(M, k=N)
    return config


def evaluare(config):
    mapare = {litera: cifra for litera, cifra in zip(litere, config)}
    nr1 = int("".join(str(mapare[litera]) for litera in cuv1))
    nr2 = int("".join(str(mapare[litera]) for litera in cuv2))
    nr3 = int("".join(str(mapare[litera]) for litera in cuv3))
    dif = nr3 - nr2 - nr1
    if dif == 0:
        print(cuv1, " = ", nr1)
        print(cuv2, " = ", nr2)
        print(cuv3, " = ", nr3)
    return dif


def perturbare(config):
    x = rn.randrange(N)
    y = rn.randrange(N)
    while x == y:
        y = rn.randrange(N)
    # print(x, y)
    config[x], config[y] = config[y], config[x]
    return config


def Hill_Climbing():
    print(litere)
    configuratie = initializare()
    print("Configuratia initiala: ")
    print(configuratie)
    eval_curent = evaluare(configuratie)
    print("Evaluare: ", eval_curent)
    for i in range(1000):
        if eval_curent == 0:
            break
        copy_config = [i for i in configuratie]  # facem o copie a configuratiei pentru a o trimite ca parametru
        new_config = perturbare(copy_config)
        new_eval = evaluare(new_config)
        if abs(new_eval) < abs(eval_curent):
            configuratie = new_config
            eval_curent = new_eval
    print("Iteratii efectuate: ", i)
    print("Configuratia finala:\n", configuratie)
    print("Evaluare: ", eval_curent)


Hill_Climbing()
