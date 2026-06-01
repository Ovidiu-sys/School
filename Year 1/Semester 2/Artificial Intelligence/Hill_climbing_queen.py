import random as rn

N = 8


def initializare():
    M = [i for i in range(1, N + 1)]
    config = rn.sample(M, k=N)
    return config


def evaluare(config):
    erori = 0
    for i in range(N - 1):
        for j in range(i + 1, N):
            if abs(config[i] - config[j]) == abs(i - j):
                erori += 1
    return erori


def print_table(config):
    for i in range(N):
        print("\n_________________________________")
        for j in range(N):
            if config[j] - 1 == i:
                print("| * ", end="")
            else:
                print("|   ", end="")
        print("|", end="")
    print("\n_________________________________")


def perturbare(config):
    x = rn.randrange(N)
    y = rn.randrange(N)
    while x == y:
        y = rn.randrange(N)
    config[x], config[y] = config[y], config[x]
    return config

# functia Hill Climbing cu restart aleatoriu
def Hill_Climbing_aleator():
    gasit_sol = False
    restart = 0
    while not gasit_sol:
        restart += 1
        configuratie = initializare()
        print("Configuratia initiala: ")
        print(configuratie)
        print("Atacuri: ", evaluare(configuratie))
        for i in range(100):
            eval_curent = evaluare(configuratie)
            if eval_curent == 0:
                gasit_sol = True
                break
            copy_config = configuratie[:]
            new_config = perturbare(copy_config)
            if evaluare(new_config) < eval_curent:
                configuratie = new_config
        print("Iteratii efectuate: ", i)
        print("Configuratia finala:\n", configuratie)
        print("Atacuri: ", evaluare(configuratie))
    print(f"S-au efectuat {restart} restarturi aleatorii")


Hill_Climbing_aleator()
