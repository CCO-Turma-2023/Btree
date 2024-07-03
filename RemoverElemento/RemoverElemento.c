//
// Created by tiago on 30/06/2024.
//
#include <stdio.h>
#include "Btree/btree.h"
#include "RemoverElemento.h"

void RemoverRegistro(Btree *arv){
    int qtd, elem, escolha;
    if(arv) {
        printf("Digite a quantidade de valores a serem removidos:");
        scanf("%d", &qtd);
        for (int i = 0; i < qtd; i++) {
            printf("Digite o elemento:");
            scanf("%d", &elem);
            if (removeChave(arv, elem))
                printf("Removido\n");
        }
    }else{
        printf("Arvore invalida\n");
    }
}