//include <iostream>
#include <GraphBLAS.h>
#define LAGRAPH_FREE_ALL { GrB_Vector_free (&v) ; GrB_Vector_free (&q) ; }
//using namespace std;

GrB_Info bfs // push-only BFS
        (
                GrB_Vector *s, // v(i) is the BFS level of node i in the graph
                GrB_Matrix A, // input graph, treated as if boolean in semiring
                GrB_Index source // starting node of the BFS
        )
        //output is the permuted vectors such that σi is the ith vertex
        // in the pre-order traversal sequence.
{
    GrB_Info info ;
    GrB_Vector q = NULL ; // nodes visited at each level
    GrB_Vector v = NULL ; // result vector
    if (s == NULL) return GrB_NO_VALUE;
    GrB_Index n, nvals ;
    GrB_Matrix_nrows (&n, A) ;
// create an empty vector v, and make it dense
    GrB_Vector_new (&v, (n > INT32_MAX) ? GrB_INT64 : GrB_INT32, n) ;
    GrB_Vector_assign(v, NULL, NULL, 0, GrB_ALL, n, NULL) ;
// create a boolean vector q, and set q(source) to true
    GrB_Vector_new (&q, GrB_BOOL, n) ;
    GrB_Vector_setElement_INT32(q, true, source) ;
// BFS traversal and label the nodes
    for (int64_t level = 1 ; level <= n ; level++)
    {
// v<q> = level
        GrB_Vector_assign_BOOL(v, q, NULL, level, GrB_ALL, n, GrB_DESC_S) ;
// break if q is empty
        GrB_Vector_nvals (&nvals, q) ;
        if (nvals == 0) break ;
// q’<!v> = q’*A
        GrB_vxm (q, v, NULL, GxB_ANY_PAIR_BOOL, q, A, GrB_DESC_RC) ;
    }
// free workspace and return result
    (*s) = v ; // return result
    v = NULL ; // set to NULL so LAGRAPH_FREE_ALL doesn’t free it
    LAGRAPH_FREE_ALL;
    return (GrB_SUCCESS) ;
}

int main() {
    GrB_init(GrB_BLOCKING);
    int vertex = 5;
    GrB_Matrix g;
    GrB_Matrix_new(&g, GrB_BOOL, vertex, vertex);
    GrB_Matrix_setElement_BOOL(g, true, 4, 3);
    GrB_Matrix_setElement_BOOL(g, true, 4, 5);
    GrB_Matrix_setElement_BOOL(g, true, 5, 1);
    GrB_Matrix_setElement_BOOL(g, true, 5, 2);
    GrB_Vector s;
    GrB_Vector_new(&s,  GrB_INT32, vertex) ;
    bfs(&s, g, 4);

    GrB_finalize();
    return 0;
}
