//
// Created by tiago on 29/06/2024.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Btree/btree.h"
#include "CriarIndice.h"

int getTamanhoRegistro (FILE *arq)
{
    int tamanhoNome = 1;
    char c = fscanf (arq, "%c" , &c);;
    while (c != '\n')
    {
        fscanf (arq, "%c" , &c);
        tamanhoNome++;
    }
    return tamanhoNome;
}

int getTamanhoMatricula (FILE *arq)
{
    int tamanhoMatricula = 1;
    char c = fscanf (arq, "%c" , &c);;
    while (c != ' ')
    {
        fscanf (arq, "%c" , &c);
        tamanhoMatricula++;
    }
    return tamanhoMatricula;
}

Btree *CriarIndice(char *nomeArq){
    int ordem, matricula, indice = 1, tamanhoRegistro, flag = 1, tamanhoMatricula;
    char *caminho;
    FILE *arq;
    Btree *arvore;
    chave key;
    caminho = (char*)malloc(sizeof(char) * (13 + strlen(nomeArq)));
    if (!caminho)
    {
        printf ("Erro na alocação de memória.\n");
        return NULL;
    }
    strcpy (caminho, "../Entradas/");
    strcat (caminho, nomeArq);
    arq = fopen(caminho, "r");
    if(!arq){
        printf("Arquivo nao existe\n");
        return NULL;
    }
    tamanhoMatricula = getTamanhoMatricula(arq);
    rewind(arq);
    tamanhoRegistro = getTamanhoRegistro(arq);
    printf ("\nDigite a ordem da arvore(Obs. Somente numeros pares e maior ou igual a 6):");
    scanf ("%d", &ordem);
    if (ordem%2 || ordem < 5 || ordem > 300){
        printf ("Numero invalido\n");
        return NULL;
    }
    arvore = criarArvore(ordem);
    if(!arvore)
        return NULL;
    rewind(arq);
    while (!feof(arq) && flag) {
        if (fscanf (arq, "%d", &matricula) != 1)
        {
            flag = 0;
        } else {
            fseek(arq, tamanhoRegistro - tamanhoMatricula, SEEK_CUR);
            key.valor = matricula;
            key.indice = indice;
            if (!insereChave(arvore, key)) {
                printf("Não foi possivel inserir chave de valor %d\n", key.valor);
                return NULL;
            }
            indice++;
        }
    }
    return arvore;
}