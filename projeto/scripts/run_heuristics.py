import os
import subprocess

if __name__ == "__main__":
    heuristicas = "../heuristicas"
    inputs = "../inputs"

    for heuristica in os.listdir(heuristicas):
        dir_heu = os.path.join(heuristicas, heuristica)
        f_heu = dir_heu + "/filmes_" + heuristica

        for variable_dir in os.listdir(inputs):
            dir_in = os.path.join(inputs, variable_dir)

            for in_file in os.listdir(dir_in):
                f_in = os.path.join(dir_in, in_file)
                proc = subprocess.Popen([f_heu, heuristica, "<", f_in])
                proc.wait()
