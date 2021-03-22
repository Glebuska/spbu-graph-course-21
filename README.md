# Linear Algebraic Depth-first search

## Build
To build this project install [GraphBlas](https://graphblas.github.io/). CMake is require. 
```
cd build
cmake ..
make
```

## Run
To run code write:
```
./graphBlas

```
Note: it's need matrix initialisation. Write info about matrix using next format:
```
{vertex_count} {start_vertex} {count_edges}
{out_vertex} {destination_vertex}
```

## Test
To test code install [GoogleTest](https://github.com/google/googletest) framework and write:
```
./graphBlasTest

```