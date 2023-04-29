/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-22 10:59:25
 * @LastEditors: like
 * @LastEditTime: 2023-04-29 07:32:28
 */
#include <iostream>
#include <Eigen/Dense>
#include <linear_algebra/vector.hpp>

using namespace Eigen;
using namespace linear_alg::vector;

void norm_test();
void projection_test();

int main()
{
    norm_test();
    projection_test();
}

void norm_test()
{
    VectorXd vec(3);
    vec << 1, 2, 3;
    PRINT_VAL(vec);
    PRINT_VAL(norm(vec));
    PRINT_VAL(vec.norm());
    {
        std::vector<double> vec{1, 2, 3};
        PRINT_VAL(norm(vec));
    }
}
void projection_test()
{
    Vector2d x = {1.6, 2.28}, x0 = {0, 0}, u = {0.8944, 0.4472};
    PRINT_VAL(projection(x, x0, u));
    PRINT_VAL(projection_eigen_only(x, x0, u));
    {
        /* test for stl container */
        std::vector<double> x = {1.6, 2.28}, x0 = {0, 0}, u = {0.8944, 0.4472};
        PRINT_VAL(projection(x, x0, u));
    }
}