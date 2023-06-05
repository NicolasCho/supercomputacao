import os
import subprocess

if __name__ == "__main__":
    dir_heu = "../heuristicas/exaustiva_paralela"
    dir_inputs = "../inputs/VARIAVEL_FILME_41filmes_7categorias_2media"

    if os.path.exists(dir_heu + "/results.csv"):
        os.remove(dir_heu + "/results.csv")

    f_out = open(dir_heu + "/results.csv", "a")
    f_out.write("variavel,numero_filmes,alocacao_tempo,tempo_execucao,nome_arquivo\n")
    f_out.close()

    for i in range(10, 510, 10):
        f_in = open(dir_inputs + "/in"+str(i)+".txt")
        proc = subprocess.Popen([dir_heu+"/filmes_exaustiva_paralela", "filme", "in"+str(i)+".txt"], stdin = f_in)
        proc.wait()        