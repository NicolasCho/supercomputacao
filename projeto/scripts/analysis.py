from subprocess import Popen, PIPE
import pandas as pd
import os


if __name__ == "__main__":
    df_dict = {}
    heuristicas = "../heuristicas"

    for heuristica in os.listdir(heuristicas):
        f = os.path.join(heuristicas, heuristica)
        df_dict[heuristica] = pd.read_csv(f+"/results.csv")
    
    