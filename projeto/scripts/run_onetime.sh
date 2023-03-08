#!/bin/bash
echo "Heurística para utilizar:"
read heuristica
echo Utilizando $heuristica

echo "Numero de filmes:"
read nFilmes
echo "Numero de categorias:"
read nCategorias
echo "Media duração filmes:"
read duracaoMedia

#gera input de filmes
./../gerador/gerador $nFilmes $nCategorias $duracaoMedia $varname

#testa heuristica
#./../$heuristica/filmes_$heuristica < ./../$heuristica/inputs/filmes_${heuristica}_${nFilmes}_${nCategorias}_${duracaoMedia}.txt