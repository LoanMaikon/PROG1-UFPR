#!/bin/bash

#set -x

#Testa a quantidade de parametros
if [ $# != 2 ]; then
    echo "Numero de entradas errado"
    exit
fi

XML=$1
CSV=$2
TAGS="//PMID|//ArticleTitle|//Abstract|//MeshHeadingList"
NULL='/dev/null'

#Testa se a pasta ja existe
if [ -d ${CSV} ]; then
    rm "${CSV}"/*
    rmdir "${CSV}"
fi
mkdir ${CSV}

#Criando arquivo base com o xgrep aplicado
cd ${CSV}
for file in "${XML}"/*.xml.gz; do
    NOME=$(basename "${file}" .xml.gz)

    #tratamento inicial em cada arquivo .csv
    zcat ${file} | /home/soft/xgrep/bin/xgrep -t -x "${TAGS}" | sed -E 's/ {3,}//g' | tr '\n' ' ' > ${NOME}.csv #Juntar linhas
    sed -i 's/<\/MeshHeadingList>/<\/MeshHeadingList>\n/g' ${NOME}.csv > ${NULL} #Quebrar linhas
done

#Manipulando o arquivo csv já criado com cada linha contendo 1 artigo
for file in "${CSV}"/*.csv; do
    sed -i 's/<\/PMID>/>/g' ${file} > ${NULL} #Substitui </PMID> por >
    sed -i 's/<\/ArticleTitle>/>/g' ${file} > ${NULL} #Substitui </ArticleTitle> por >
    sed -i 's/<\/Abstract>/>/g' ${file} > ${NULL} #Substitui </Abstract> por >
    sed -i 's/<\/MeshHeading>/, /g' ${file} > ${NULL} #Troca "</MeshHeading>"" por ", "
    sed -i 's/<[^>]*>//g' ${file} > ${NULL} #Tira as tags
    sed -i 's/..$//g' ${file} > ${NULL} #Tira os dois últimos caracteres de cada linha
    sed -i 's/> />/g' ${file} > ${NULL} #Tira o espaço entre cada divisória >
    sed -i 's/./1/' ${file} > ${NULL} #Substitui o primeiro caractere por 1
    sed -i '1s/.*/version+pmid<title<abstract<keywords/' ${file} > ${NULL} #Coloca as buscas na primeira linha
    sed -i 's/>/</g' ${file} > ${NULL} #troca ">" por "<"
done