#!/bin/bash

#set -x

SOURCE=$1
SIN=$2

#Testa numero de parametros
if [[ $# -lt 2 || $# -gt 3 ]]; then
    echo "Numero de entradas errado"
    exit
fi

#Loop para filtrar
for file in "${SIN}"/*.txt; do
    NOME=$(basename "${file}" .txt)
    CONT=0

    CONT=$((CONT + $(grep -o -i -w -F -f "${file}" "${SOURCE}"/*.csv | wc -l)))

    echo "${NOME}:${CONT}"
done