//
// Created by Gleb Mirzazyanov on 21.03.2021.
//
#include "dfs.h"

GrB_Index build_permute
        (
                GrB_Vector* e,
                const GrB_Index tau,
                GrB_Matrix* P // output matrix
        )
{
    GrB_Index nvals;
    GrB_Vector_nvals(&nvals, *e);

    GrB_Index size;
    GrB_Vector_size(&size, *e);

    GrB_Matrix_clear(*P);
    for (GrB_Index i = 0; i < tau; i++) {
        GrB_Matrix_setElement_BOOL(*P, true, i, i);
    }

    set<GrB_Index> moved_up;
    GrB_Index moved_down = 0;
    bool buf;
    for (GrB_Index i = tau; i < size; i++) {
        GrB_Vector_extractElement_BOOL(&buf, *e, i);
        if (buf) {
            GrB_Matrix_setElement_BOOL(*P, true, i, tau + moved_up.size());
            moved_up.insert(i);
            buf = false;
        }
    }
    for (GrB_Index i = tau; i < size; i++) {
        if (moved_up.count(i) == 0) {
            GrB_Matrix_setElement_BOOL(*P, true, i, tau + moved_up.size() + moved_down);
            moved_down++;
        }
    }

    return nvals;
}

GrB_Info dfs
        (
                GrB_Vector* s, // v(i) is the DFS level of node i in the graph
                GrB_Matrix A, // input graph, treated as if boolean in semiring
                const GrB_Index started // starting node of the DFS
        )
//output is the permuted vector s such that s[i] is the i-th vertex
// in the pre-order traversal sequence
{
    GrB_Index size;
    GrB_Matrix_ncols(&size, A);

    GrB_Index tau = 0;
    GrB_Index beta = 0;

    GrB_Matrix P;
    GrB_Matrix P_1;
    GrB_Matrix A_1;
    GrB_Vector n;
    GrB_Vector e;

    GrB_Matrix_new(&P, GrB_BOOL, size, size);
    GrB_Matrix_new(&P_1, GrB_BOOL, size, size);
    GrB_Matrix_new(&A_1, GrB_BOOL, size, size);
    GrB_Vector_new(&n, GrB_UINT64, size);
    GrB_Vector_new(&e, GrB_UINT64, size);


    GrB_Vector_setElement_BOOL(e, true, started);


    GrB_Index nu = build_permute(&e, tau, &P);

    GrB_transpose(P_1, nullptr, nullptr, P, nullptr);

    GrB_mxm(A, nullptr, nullptr, GxB_ANY_PAIR_BOOL, P_1, A, nullptr);
    GrB_mxm(A, nullptr, nullptr, GxB_ANY_PAIR_BOOL, A, P, nullptr);
    GrB_mxv(*s, nullptr, nullptr, GrB_MAX_SECOND_SEMIRING_UINT64, P_1, *s, nullptr);

    beta += nu;

    while (tau < size) {

        GrB_transpose(A_1, nullptr, nullptr, A, nullptr);

        GrB_Vector_clear(e);
        GrB_Vector_setElement_BOOL(e, true, tau);

        GrB_mxv(n, nullptr, nullptr, GxB_ANY_PAIR_BOOL, A_1, e, nullptr);

        tau += 1;
        if (beta < tau) {
            beta += 1;
        }

        nu = build_permute(&n, tau, &P);

        GrB_transpose(P_1, nullptr, nullptr, P, nullptr);

        GrB_mxm(A, nullptr, nullptr, GxB_ANY_PAIR_BOOL, P_1, A, nullptr);
        GrB_mxm(A, nullptr, nullptr, GxB_ANY_PAIR_BOOL, A, P, nullptr);

        GrB_mxv(*s, nullptr, nullptr, GrB_MAX_SECOND_SEMIRING_UINT64, P_1, *s, nullptr);

        beta += nu;
    }

    GrB_Matrix_free(&P);
    GrB_Matrix_free(&P_1);
    GrB_Matrix_free(&A_1);
    GrB_Vector_free(&n);
    GrB_Vector_free(&e);

    return GrB_SUCCESS;
}
