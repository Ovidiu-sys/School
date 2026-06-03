import random as rn


def citire(filename):
    # Citeste distantele din fisier si construieste matricea de adiacenta simetrica.
    matrice = [[0] * N for _ in range(N)]
    try:
        with open(filename, 'r') as f:
            date = [int(x) for line in f for x in line.split()]
    except FileNotFoundError:
        print(f"Eroare: Nu s-a găsit fișierul '{filename}'.")
        return None

    idx = 0
    for i in range(N - 1):
        for j in range(i + 1, N):
            if idx < len(date):
                matrice[i][j] = date[idx]
                matrice[j][i] = date[idx]
                idx += 1

    return matrice


def initializare():
    # Genereaza o configuratie initiala aleatoare (o permutare a oraselor).
    return rn.sample(range(N), N)


def evaluare(configuratie, matrice):
    # Calculeaza distanta totala a rutei (circuit).
    distanta_totala = sum(matrice[configuratie[i]][configuratie[i + 1]] for i in range(N - 1))
    distanta_totala += matrice[configuratie[-1]][configuratie[0]]
    return distanta_totala

# variatie clasica, schimba doar doua orase intre ele in configuratie
def perturbare(configuratie):
    noua_config = configuratie[:]
    x = rn.randrange(N)
    y = rn.randrange(N)
    while x == y:
        y = rn.randrange(N)
    noua_config[x], noua_config[y] = noua_config[y], noua_config[x]
    return config

# variatie in care inversam o portiune din configuratie
def variatie_inversiune(configuratie):
    noua_config = configuratie[:]
    # Alegem două puncte de tăiere
    i, j = sorted(rn.sample(range(N), 2))
    # Inversăm bucata dintre cele două puncte
    noua_config[i:j] = reversed(noua_config[i:j])
    return noua_config


# variatie mare (curs)
def variatie(configuratie, pm=0.5):
    # Modifica (muta) configuratia curenta pentru a explora vecinii.
    noua_config = configuratie[:]

    for j in range(N):
        if rn.random() < pm:
            x = rn.randrange(N)
            while x == j:
                x = rn.randrange(N)
            noua_config[j], noua_config[x] = noua_config[x], noua_config[j]
    return noua_config


def hill_climbing(matrice, iteratii_maxime=10000, max_pasi_fara_succes=500):
    configuratie = initializare()
    cost_curent = evaluare(configuratie, matrice)

    print(f"\nConfigurația inițială: {configuratie}")
    print(f"Cost inițial: {cost_curent}\n")

    pasi_fara_imbunatatire = 0

    for i in range(iteratii_maxime):
        #config_noua = perturbare(configuratie)
        config_noua = variatie_inversiune(configuratie)
        cost_nou = evaluare(config_noua, matrice)

        if cost_nou < cost_curent:
            configuratie = config_noua
            cost_curent = cost_nou
            # Resetăm contorul deoarece am găsit o soluție mai bună
            pasi_fara_imbunatatire = 0
        else:
            # Incrementăm contorul dacă soluția nouă nu e mai bună
            pasi_fara_imbunatatire += 1

        # Verificăm criteriul de oprire inteligent
        if pasi_fara_imbunatatire >= max_pasi_fara_succes:
            print(f"Algoritmul s-a oprit devreme la iterația {i}!")
            print(f"Motiv: Nu s-a găsit nicio rută mai bună timp de {max_pasi_fara_succes} de pași consecutivi.")
            break

    return configuratie, cost_curent



N = 20
matrice_distante = citire("in.txt")

if matrice_distante:
    # Permitem un număr teoretic foarte mare de iterații, bazați pe oprirea inteligentă
    config_finala, cost_final = hill_climbing(matrice_distante, iteratii_maxime=20000, max_pasi_fara_succes=500)

    print(f"\n--- REZULTAT FINAL ---")
    print(f"Cea mai bună rută găsită: {config_finala}")
    print(f"Cost minim obținut: {cost_final}")
