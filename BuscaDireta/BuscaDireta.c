//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CriarIndice/CriarIndice.h"
#include "BuscaDireta.h"
#include "BuscaBtree/BuscaBtree.h"

void BuscaDireta(char *nomeArq, int n){
    int matricula,valor, qtd, tamanhoRegistro, idade, periodo, cod, tamanhoMatricula, flag = 1;
    char *registro, *caminho;
    double tempo, tempoTotal = 0, menor = 9999, maior = 0;
    clock_t inicio, fim;
    FILE *arq;
    caminho = (char*)malloc(sizeof(char) * (13 + strlen(nomeArq)));
    if (!caminho)
    {
        printf ("Erro na alocação de memória.\n");
        return;
    }
    strcpy (caminho, "../Entradas/");
    strcat (caminho, nomeArq);
    arq = fopen(caminho, "r");
    if (!arq){
        printf("Arquivo nao existe\n");
        return;
    }
    srand(time(NULL));
    tamanhoRegistro = getTamanhoRegistro(arq);
    rewind(arq);
    tamanhoMatricula = getTamanhoMatricula(arq);
    registro = (char*)malloc(sizeof(char)*(tamanhoRegistro - tamanhoMatricula));
    if (!registro)
    {
        printf ("Erro ao alocar memória.\n");
        return;
    }
    printf("Selecione o modo de busca.\n1 - Aleatorio\n2 - Escolher o registro.\n");
    scanf("%d", &cod);
    switch (cod) {
        case 1:
            printf("Digite a quantidade de buscas:");
            scanf("%d", &qtd);
            printf("Busca direta no arquivo:\n");
            for (int i = 0; i < qtd; i++) {
                valor = 2023000000 + rand() % n;
                flag = 1;
                printf("%d - ", valor);
                fseek (arq, 0, SEEK_SET);
                inicio = clock();
                while (!feof(arq) && matricula != valor && flag) {
                    if (fscanf(arq, "%d", &matricula) != 1)
                    {
                        flag = 0;
                    } else {
                        fgets(registro, tamanhoRegistro-tamanhoMatricula, arq);
                    }
                }
                if (feof(arq))
                    printf("Nao encontrado - ");
                else {
                    printf("%d %s", matricula, registro);
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
                    rewind(arq);
                    flag = 1;
                    printf("%d - ", valor);
                    inicio = clock();
                    while (!feof(arq) && matricula != valor && flag) {
                        if (fscanf(arq, "%d", &matricula) != 1){
                            flag = 0;
                        } else {
                            fgets(registro, tamanhoRegistro-tamanhoMatricula+1, arq);
                        }
                    }
                    if (feof(arq))
                        printf("Nao encontrado - ");
                    else {
                        printf("%d %s", matricula, registro);
                    }
                    fim = clock();
                    tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
                    printf(" -- Tempo gasto: %lf\n", tempo);
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
