#include "dfs.h"
#include <vector>
#include <string>

using namespace std;


int main() {
    GrB_init(GrB_BLOCKING);
    int n, m, start_vertex;
    GrB_Matrix g;
    cout << "Write count of vertex, starting vertex and edges. Note: graph will be a three" << endl;
    cin >> n >> start_vertex >> m;

    GrB_Matrix_new(&g, GrB_BOOL, n, n);
    cout << endl << "Write " << m << " edges:" << endl;
    for(GrB_Index i = 0; i < m; i++){
        GrB_Index out, to;
        cin >> out >> to;
        GrB_Matrix_setElement_BOOL(g, true, out, to);
    }

    GrB_Vector s;
    GrB_Vector_new(&s,  GrB_UINT64, n);
    for (GrB_Index k = 0; k < n; k++) {
        GrB_Vector_setElement_INT64(s, k, k);
    }
    dfs(&s, g, start_vertex);

    cout << "dfs result: ";
    for(int i = 0; i < n; i++){
        int value;
        GrB_Vector_extractElement_INT32(&value, s, i);
        cout << value << " ";
    }

    GrB_finalize();
    return 0;
}


