import os
import subprocess

if __name__ == "__main__":
    heuristicas = "../heuristicas"
    inputs = "../inputs"

    for heuristica in os.listdir(heuristicas):
        dir_heu = os.path.join(heuristicas, heuristica)
        # Deleta resultados anteriores se já existem e cria novo arquivo de resultados
        if os.path.exists(dir_heu + "/results.csv"):
            os.remove(dir_heu + "/results.csv")
        f_out = open(dir_heu + "/results.csv", "a")
        f_out.write("variavel,numero_filmes,alocacao_tempo,tempo_execucao,nome_arquivo\n")
        f_out.close()
        f_out = open(dir_heu + "/results.csv", "a")

        f_heu = "./" + dir_heu + "/filmes_" + heuristica

        for variable_dir in os.listdir(inputs):
            dir_in = os.path.join(inputs, variable_dir)
            variavel = variable_dir.split("_")[1].lower()

            for in_file in os.listdir(dir_in):
                f_in = open(os.path.join(dir_in, in_file))
                proc = subprocess.Popen([f_heu, variavel, in_file], stdin = f_in)
                proc.wait()
          