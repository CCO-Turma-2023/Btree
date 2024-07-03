cmake_minimum_required(VERSION 3.27)
project(B_Tree_master C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(B_Tree_master
        Btree/btree.c
        Btree/btree.h
        main.c
        Menu/Menu.h
        Menu/Menu.c
        CriarIndice/CriarIndice.c
        CriarIndice/CriarIndice.h
        ProcurarElementos/ProcurarElemento.h
        ProcurarElementos/ProcurarElemento.c
        "RemoverElemento/RemoverElemento.h"
        "RemoverElemento/RemoverElemento.c"
        BuscaBtree/BuscaBtree.h
        BuscaBtree/BuscaBtree.c
        BuscaDireta/BuscaDireta.h
        BuscaDireta/BuscaDireta.c)
