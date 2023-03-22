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
    for i in range(0, int(n_mov), 10):
        proc = subprocess.Popen(["./../gerador/gerador", str(i), m, len_mean, batch_name, "in"+str(i)])
        proc.wait()

def generate_inputs_categories(batch_name, n_mov, m, len_mean):
    for i in range(0, int(m), 2):
        proc = subprocess.Popen(["./../gerador/gerador", str(i), m, len_mean, batch_name, "in"+str(i)])
        proc.wait()

def generate_inputs_mean(batch_name, n_mov, m, len_mean):
    for i in range(int(len_mean)):
        proc = subprocess.Popen(["./../gerador/gerador", str(i), m, len_mean, batch_name, "in"+str(i)])
        proc.wait()

if __name__ == "__main__":
    n_movies = sys.argv[1]      #Número de filmes por arquivo
    m = sys.argv[2]             #Número de categorias
    length_mean = sys.argv[3]   #Média de duração
    variable = sys.argv[4]

    if variable == "filme":
        batch_name = "VARIAVEL_FILME_" + n_movies + "filmes_" + m + "categorias_" + length_mean + "media"  
        create_directory(batch_name)
        generate_inputs_movies(batch_name, n_movies, m, length_mean)
    elif variable == "categoria":
        batch_name = "VARIAVEL_CATEGORIA_" + n_movies + "filmes_" + m + "categorias_" + length_mean + "media"  
        create_directory(batch_name)
        generate_inputs_categories(batch_name, n_movies, m, length_mean)
    elif variable == "media":
        batch_name = "VARIAVEL_MEDIA_" + n_movies + "filmes_" + m + "categorias_" + length_mean + "media"  
        create_directory(batch_name)
        generate_inputs_mean(batch_name, n_movies, m, length_mean)
    else:
        raise Exception("Erro")

