#include "gtest/gtest.h"
#include "dfs.h"

TEST(check_dfs, test_1)
{
    GrB_Index vertex = 5;

    GrB_Matrix g;
    GrB_Matrix_new(&g, GrB_BOOL, vertex, vertex);
    GrB_Matrix_setElement_BOOL(g, true, 4, 3);

    GrB_Vector s;
    GrB_Vector_new(&s,  GrB_UINT64, vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        GrB_Vector_setElement_INT64(s, i, i);
    }
    dfs(&s, g, 4);
    vector<long long> result_value(vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        long long value;
        GrB_Vector_extractElement_INT64(&value, s, i);
        result_value[i] = value;
    }

    EXPECT_EQ(4, result_value[0]);
    EXPECT_EQ(3, result_value[1]);
    EXPECT_EQ(0, result_value[2]);
    EXPECT_EQ(1, result_value[3]);
    EXPECT_EQ(2, result_value[4]);
}

TEST(check_dfs, test_2)
{
    GrB_Index vertex = 5;

    GrB_Matrix g;
    GrB_Matrix_new(&g, GrB_BOOL, vertex, vertex);
    GrB_Matrix_setElement_BOOL(g, true, 4, 3);
    GrB_Matrix_setElement_BOOL(g, true, 4, 2);
    GrB_Matrix_setElement_BOOL(g, true, 2, 1);
    GrB_Matrix_setElement_BOOL(g, true, 2, 0);

    GrB_Vector s;
    GrB_Vector_new(&s,  GrB_UINT64, vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        GrB_Vector_setElement_UINT64(s, i, i);
    }
    dfs(&s, g, 4);
    vector<unsigned long long> result_value;
    for (GrB_Index i = 0; i < vertex; i++) {
        unsigned long long value;
        GrB_Vector_extractElement_UINT64(&value, s, i);
        result_value.push_back(value);
    }

    EXPECT_EQ(4, result_value[0]);
    EXPECT_EQ(2, result_value[1]);
    EXPECT_EQ(0, result_value[2]);
    EXPECT_EQ(1, result_value[3]);
    EXPECT_EQ(3, result_value[4]);
}

TEST(check_dfs, test_3)
{
    GrB_Index vertex = 3;
    GrB_Index started = 0;

    GrB_Matrix g;
    GrB_Matrix_new(&g, GrB_BOOL, vertex, vertex);
    GrB_Matrix_setElement_BOOL(g, true, 0, 1);
    GrB_Matrix_setElement_BOOL(g, true, 1, 2);
    GrB_Vector s;
    GrB_Vector_new(&s,  GrB_UINT64, vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        GrB_Vector_setElement_INT64(s, i, i);
    }
    dfs(&s, g, started);
    vector<long long> result_value(vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        long long value;
        GrB_Vector_extractElement_INT64(&value, s, i);
        result_value[i] = value;
    }

    EXPECT_EQ(0, result_value[0]);
    EXPECT_EQ(1, result_value[1]);
    EXPECT_EQ(2, result_value[2]);
}

TEST(check_dfs, test_4)
{
    GrB_Index vertex = 8;
    GrB_Index started = 0;

    GrB_Matrix g;
    GrB_Matrix_new(&g, GrB_BOOL, vertex, vertex);
    GrB_Matrix_setElement_BOOL(g, true, 0, 1);
    GrB_Matrix_setElement_BOOL(g, true, 1, 2);
    GrB_Matrix_setElement_BOOL(g, true, 1, 4);
    GrB_Matrix_setElement_BOOL(g, true, 2, 7);
    GrB_Matrix_setElement_BOOL(g, true, 2, 5);
    GrB_Matrix_setElement_BOOL(g, true, 4, 3);
    GrB_Matrix_setElement_BOOL(g, true, 5, 6);

    GrB_Vector s;
    GrB_Vector_new(&s,  GrB_UINT64, vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        GrB_Vector_setElement_INT64(s, i, i);
    }
    dfs(&s, g, started);
    vector<long long> result_value(vertex);
    for (GrB_Index i = 0; i < vertex; i++) {
        long long value;
        GrB_Vector_extractElement_INT64(&value, s, i);
        result_value[i] = value;
    }

    EXPECT_EQ(0, result_value[0]);
    EXPECT_EQ(1, result_value[1]);
    EXPECT_EQ(2, result_value[2]);
    EXPECT_EQ(5, result_value[3]);
    EXPECT_EQ(6, result_value[4]);
    EXPECT_EQ(7, result_value[5]);
    EXPECT_EQ(4, result_value[6]);
    EXPECT_EQ(3, result_value[7]);
}

int main(int argc, char ** argv)
{
    GrB_init(GrB_BLOCKING);
    testing::InitGoogleTest(&argc, argv);
    GrB_finalize();
    return RUN_ALL_TESTS();
}

