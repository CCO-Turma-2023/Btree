//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "BuscaBtree.h"
#include "CriarIndice/CriarIndice.h"

void BuscaBtree(Btree *arv,char *nomeArq) {
    int valor = 1, indiceArq, matricula, qtd, qtdElementos, idade, periodo, tamanhoRegistro, cod;
    char *registro, *caminho;
    double tempo, tempoTotal = 0, menor = 9999, maior = 0;
    clock_t inicio, fim;
    caminho = (char*)malloc(sizeof(char) * (13 + strlen(nomeArq)));
    if (!caminho)
    {
        printf ("Erro na alocação de memória.\n");
        return;
    }
    strcpy (caminho, "../Entradas/");
    strcat (caminho, nomeArq);
    FILE *arq = fopen(caminho, "r");
    if (!arq) {
        printf("Arquivo nao existe\n");
        return;
    }

    rewind(arq);
    tamanhoRegistro = getTamanhoRegistro(arq);
    registro = (char *) malloc(sizeof(char) * (tamanhoRegistro));

    if (!registro) {
        printf ("Erro ao alocar memória.\n");
        return;
    }

    printf("Selecione o modo de busca.\n1 - Aleatorio\n2 - Escolher o registro.\n");
    scanf("%d", &cod);
    srand(time(NULL));
    switch (cod) {
        case 1:
            printf("Digite a quantidade de buscas:");
            scanf("%d", &qtd);
            printf("Busca pela Btree:\n");
            qtdElementos = getNumElementos(arv);
            rewind(arq);
            for (int i = 0; i < qtd; i++) {
                valor = 2023000000 + rand() % qtdElementos;
                printf("%d - ", valor);
                inicio = clock();
                indiceArq = busca(getRaiz(arv), valor);
                rewind(arq);
                if (indiceArq) {
                    fseek(arq, (indiceArq - 1) * (tamanhoRegistro+1), SEEK_SET);
                    fgets (registro, tamanhoRegistro, arq);
                    printf("%s", registro);
                } else {
                    printf("Nao encontrado - ");
                }
                fim = clock();
                tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                if (tempo > maior){
                    maior = tempo;
                } else if (tempo < menor){
                    menor = tempo;
                }
                printf(" -- Tempo gasto: %lf\n", tempo);
                tempoTotal += tempo;
            }
            printf("Tempo medio gasto foi: %lf\n", tempoTotal / qtd);
            printf ("Maior Tempo: %lf - Menor Tempo: %lf\n", maior, menor);
            break;
        case 2:
            printf ("Digite o valor que deseja procurar ou 0 para sair: ");
            scanf ("%d", &valor);
            while (valor != 0) {
                printf("Busca pela Btree:\n");
                qtdElementos = getNumElementos(arv);
                rewind(arq);
                printf("%d - ", valor);
                inicio = clock();
                indiceArq = busca(getRaiz(arv), valor);
                if (indiceArq) {
                    fseek(arq, (indiceArq - 1) * (tamanhoRegistro+1), SEEK_SET);
                    fgets (registro, tamanhoRegistro, arq);
                    printf("%s", registro);
                } else {
                    printf("Nao encontrado - ");
                }
                fim = clock();
                tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                printf(" -- Tempo gasto: %lf\n", tempo);
                tempoTotal += tempo;
                printf ("Digite o valor que deseja procurar ou 0 para sair: ");
                scanf ("%d", &valor);
            }
            break;
        default:
            printf ("Numero invalido.\n");
            break;
    }
    fclose(arq);
}