import os
import subprocess

if __name__ == "__main__":
    heuristicas = "../heuristicas"
    dir_inputs = "../inputs/VARIAVEL_FILME_40filmes_7categorias_2media"

    for heuristica in os.listdir(heuristicas):
        if heuristica != "paralelismo_gpu":
            dir_heu = os.path.join(heuristicas, heuristica)
            # Deleta resultados anteriores se já existem e cria novo arquivo de resultados
            if os.path.exists(dir_heu + "/results.csv"):
                os.remove(dir_heu + "/results.csv")
            f_out = open(dir_heu + "/results.csv", "a")
            f_out.write("variavel,numero_filmes,alocacao_tempo,tempo_execucao,nome_arquivo\n")
            f_out.close()
            f_out = open(dir_heu + "/results.csv", "a")

            f_heu = "./" + dir_heu + "/filmes_" + heuristica

            for in_file in os.listdir(dir_inputs):
                f_in = open(dir_inputs+"/"+in_file)
                proc = subprocess.Popen([f_heu, "filme", in_file], stdin = f_in)
                proc.wait()

    dir_inputs = "../inputs/VARIAVEL_CATEGORIA_30filmes_15categorias_2media"

    for heuristica in os.listdir(heuristicas):
        if heuristica != "paralelismo_gpu":
            dir_heu = os.path.join(heuristicas, heuristica)
            f_out = open(dir_heu + "/results.csv", "a")

            f_heu = "./" + dir_heu + "/filmes_" + heuristica

            for in_file in os.listdir(dir_inputs):
                f_in = open(dir_inputs+"/"+in_file)
                proc = subprocess.Popen([f_heu, "categoria", in_file], stdin = f_in)
                proc.wait()
            