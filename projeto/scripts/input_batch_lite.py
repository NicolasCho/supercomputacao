import os
import subprocess
import sys

def create_directory(batch_name):
    #Cria diretório, se não existe
    path = "../inputs/{}".format(batch_name)
    if not os.path.isdir(path):
        os.makedirs(path)

    #Deleta conteúdo do diretório
    for f in os.listdir(path):
        os.remove(os.path.join(path, f))

def generate_inputs_movies(batch_name, n_mov, m, len_mean):
    for i in range(1, int(n_mov), 1):
        proc = subprocess.Popen(["./../gerador/gerador", str(i), m, len_mean, batch_name, "in"+str(i)+".txt"])
        proc.wait()

def generate_inputs_categories(batch_name, n_mov, m, len_mean):
    for i in range(1, int(m), 1):
        proc = subprocess.Popen(["./../gerador/gerador", n_mov, str(i), len_mean, batch_name, "in"+str(i)+".txt"])
        proc.wait()


if __name__ == "__main__":
    batch_name = "VARIAVEL_FILME_" + "40filmes_" + "7categorias_"  + "2media"  
    create_directory(batch_name)
    generate_inputs_movies(batch_name, "41", "7", "2")
  
    batch_name = "VARIAVEL_CATEGORIA_" + "30filmes_" + "15categorias_" + "2media"  
    create_directory(batch_name)
    generate_inputs_categories(batch_name, "30", "16", "2")

