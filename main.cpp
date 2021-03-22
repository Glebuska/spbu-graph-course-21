#include "dfs.h"
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<bool> used;
vector<vector<int>>g;

void dfs1 (int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to])
            dfs1(to);
    }
}

int main() {
    GrB_init(GrB_BLOCKING);

    for (const string& i: {"500", "1000", "2000", "5000", "10000"}) {

        for (const string& j: {"100", "50", "10", "5"}) {

            ifstream input("data/" + i + "_" + j + ".txt");
            ofstream output( i + "_" + j + "_" + "result" + ".txt");
            GrB_Index vertex_count, start_vertex, edges_count;
            input >> vertex_count >> start_vertex >> edges_count;

            if(!input.is_open()){
                cout << "Can not open file";
                return 1;
            }
            g.resize(vertex_count);
            used.resize(vertex_count, false);
            //linear matrix
            GrB_Matrix g1;
            GrB_Matrix_new(&g1, GrB_BOOL, vertex_count, vertex_count);

            for(GrB_Index k = 0; k < vertex_count; k++){
                GrB_Index out, to;
                input >> out >> to;
                g[out].push_back(to);
                GrB_Matrix_setElement_BOOL(g1, true, out, to);
            }


            input.close();

            GrB_Vector s;
            GrB_Vector_new(&s,  GrB_UINT64, vertex_count);
            for (GrB_Index k = 0; k < vertex_count; k++) {
                GrB_Vector_setElement_INT64(s, k, k);
            }

            auto t_1 = chrono::high_resolution_clock::now();
            dfs(&s, g1, start_vertex);
            auto t_2 = chrono::high_resolution_clock::now();


            GrB_Vector_free(&s);
            GrB_finalize();

            auto t_3 = high_resolution_clock::now();
            dfs1(start_vertex);
            auto t_4 = high_resolution_clock::now();

            auto d_1 = duration_cast<microseconds>(t_2 - t_1);
            auto d_2 = duration_cast<microseconds>(t_4 - t_3);
            output << i << ' ' << j << ' ' << d_1.count() << ' ' << d_2.count() << endl;
        }
    }

    GrB_finalize();
    return 0;
}
