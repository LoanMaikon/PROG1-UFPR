#!/bin/bash

#set -x

#Testa a quantidade de parametros
if [[ $# -lt 3 || $# -gt 5 ]]; then
    echo "Numero de entradas errado"
    exit
fi

SOURCE=$1
DEST=$2
KEY1=$3

#Testa se os parametros KEY1 e KEY2 devem existir
if [ $# -gt 3 ]; then
    KEY2=$4
fi

if [ $# = 5 ]; then
    KEY3=$5
fi

#Testa se a pasta ja existe
if [ -d ${DEST} ]; then
    rm "${DEST}"/*
    rmdir "${DEST}"
fi
mkdir ${DEST}

#Loop para filtrar
for file in "${SOURCE}"/*.csv; do
    NOME=$(basename "${file}")
    touch "${DEST}/${NOME}"
    grep -i -w "${KEY1}" "${file}" | grep -i -w "${KEY2}" | grep -i -w "${KEY3}" > "${DEST}/${NOME}"
done