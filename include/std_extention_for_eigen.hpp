/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-28 23:43:01
 * @LastEditors: like
 * @LastEditTime: 2023-04-29 07:27:42
 */
#pragma once
#include <Eigen/Dense>
#include <algorithm>
#include <vector>

#define PRINT_VAL(mat) std::cout << #mat" = { " << mat <<" }\n"

namespace std
{
    template<class Scala, int Rows, int Cols>
    inline constexpr auto begin(Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        return m.data();
    }
    template<class Scala, int Rows, int Cols>
    inline constexpr auto begin(const Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        return m.data();
    }
    template<class Scala, int Rows, int Cols>
    inline constexpr auto end(Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        return m.data() + std::size(m);
    }
    template<class Scala, int Rows, int Cols>
    inline constexpr auto end(const Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        return m.data() + std::size(m);
    }
    template<class Scala, int Rows, int Cols>
    inline constexpr auto norm(const Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        return m.norm();
    }
    template<class T>
    inline constexpr auto norm(const std::vector<T>& m)
    {
        return std::sqrt(std::inner_product(std::begin(m), std::end(m), std::begin(m), T{0}));
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) 
    {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, "\n"));
        return out;
    }
}
namespace std_extention_for_math_work
{    
    template<class T>
    inline constexpr std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        assert(std::size(lhs) == std::size(rhs));
        std::vector<T> result = lhs;
        std::transform(std::begin(rhs), std::end(rhs), std::begin(result), std::begin(result), std::plus<typename T>());
        return result;
    }
    template<class T>
    inline constexpr std::vector<T> operator*(const std::vector<T>& lhs, T n)
    {
        std::vector<T> result(lhs);
        std::for_each(std::begin(result), std::end(result), [n](T& d){ d = std::multiplies<typename T>()(d, n);});
        return result;
    }
    template<class T>
    inline constexpr void normalize(std::vector<T>& m)
    {
        const T n = 1 / std::norm(m);
        std::for_each(std::begin(m), std::end(m), [n](T& d){ d = std::multiplies<typename T>()(d, n);});
    }
    template<class Scala, int Rows, int Cols>
    inline void normalize(Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        m.normalize();
    }
}