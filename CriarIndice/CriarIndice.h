//
// Created by tiago on 29/06/2024.
//

#ifndef B_TREE_MASTER_CRIARINDICE_H
#define B_TREE_MASTER_CRIARINDICE_H
typedef struct Btree Btree;
Btree *CriarIndice(char *nomeArq);
int getTamanhoRegistro (FILE *arq);
int getTamanhoMatricula (FILE *arq);
#endif //B_TREE_MASTER_CRIARINDICE_H
