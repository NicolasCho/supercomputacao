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


if __name__ == "__main__":
    n_movies = sys.argv[1]      #41
    m = sys.argv[2]             #7
    length_mean = sys.argv[3]   #Média de duração = 2
    variable = sys.argv[4]      #Qual variável iterar

    if variable == "filme":
        batch_name = "VARIAVEL_FILME_" + n_movies + "filmes_" + m + "categorias_" + length_mean + "media"  
        create_directory(batch_name)
        generate_inputs_movies(batch_name, n_movies, m, length_mean)
    else:
        raise Exception("Erro")

