/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-22 10:11:59
 * @LastEditors: like
 * @LastEditTime: 2023-04-22 11:05:18
 */
#include <iostream>
#include <Eigen/Dense>
 
using namespace Eigen;
 
int main()
{
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
}