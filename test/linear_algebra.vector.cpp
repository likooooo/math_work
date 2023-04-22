/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-22 10:59:25
 * @LastEditors: like
 * @LastEditTime: 2023-04-22 11:15:25
 */
#include <iostream>
#include <Eigen/Dense>
#include <linear_algebra/vector.hpp>

using namespace Eigen;
using namespace linear_alg::vector;
int main()
{
    VectorXd v(3);
    v << 1, 2, 3;
    std::cout << v << std::endl;
    std::cout << "my norm : " << norm(v) << "\n";
    std::cout << "eigen norm : " << v.norm();
}