//
// Created by Gleb Mirzazyanov on 21.03.2021.
//
#include <iostream>
#include <set>
extern "C" {
#include <GraphBLAS.h>
}

#ifndef GRAPHBLAS_DFS_H
#define GRAPHBLAS_DFS_H
using namespace std;

GrB_Index build_permute
        (
                FILE* f,
                // both s and e should be permuted
                GrB_Vector* e, //
                const GrB_Index tau,
                const GrB_Index beta,
                GrB_Matrix* P // output matrix
        );

GrB_Info dfs
        (
                GrB_Vector* s, // v(i) is the BFS level of node i in the graph
                GrB_Matrix A, // input graph, treated as if boolean in semiring
                const GrB_Index started // starting node of the BFS
        );
#endif //GRAPHBLAS_DFS_H
