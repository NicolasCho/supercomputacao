# Maratona de filmes

## Recomendação

Criar ambiente virtual

    python -m venv venv

Ativar ambiente

    ./venv/Scripts/activate

Instalar dependências

    pip install -r requirements.txt

## Para gerar os inputs

Para gerar os inputs é necessário definir a variável a analisar. São 3 opções: número de filmes, número de categorias
e duração média do filme

O script recebe como input essas 3 variáveis (nessa ordem) e o nome da variável a testar. As outras duas serão 
invariáveis.
Por exemplo, para gerar inputs com a quantidade de filmes variando poderíamos utilizar (no diretório *scripts*):

    python input_batch_generator.py 10010 5 2 filme

Assim o script geraria um diretório chamado "VARIAVEL_FILME_10010filmes_5categorias_2media" contendo arquivos de 
inputs em que o número de filmes varia em cada arquivo, mas as outras variáveis não.

O arquivo "in70.txt", por exemplo, possuiria 70 filmes enquanto o "in_3000.txt", possuiria 3000.

## Para testar as heurísticas

Rodar no diretório *scripts*:

    python run_heuristics.py

Como resultado, o script populará um arquivo "results.csv" no diretório de cada heurística. Esse arquivo contém os logs
de cada batch de teste rodado (diretórios de input)

## Para realizar a análise

