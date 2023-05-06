/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-28 23:43:01
 * @LastEditors: like
 * @LastEditTime: 2023-05-06 21:08:12
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

    template <class T>
    std::ostream& operator << (std::ostream& out, const std::vector<T>& v) 
    {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, "\n"));
        return out;
    }
}
namespace std_extention_for_math_work
{    
    namespace details
    {
        template<class T, class BinaryOp>
        inline constexpr std::vector<T>& vec_binary_wrapper(std::vector<T>& lhs, const std::vector<T>& rhs)
        {
            assert(std::size(lhs) == std::size(rhs));
            std::transform(std::begin(rhs), std::end(rhs), std::begin(lhs), std::begin(lhs), BinaryOp());
            return lhs;
        }

    }
    template<class T>
    inline constexpr std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        std::vector<T> result(lhs);
        details::vec_binary_wrapper<T, std::plus<T>>(result, rhs);
        return result;
    }
    template<class T>
    inline constexpr std::vector<T>& operator+=(std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        return details::vec_binary_wrapper<T, std::plus<T>>(lhs, rhs);
    }
    template<class T>
    inline constexpr std::vector<T> operator-(const std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        std::vector<T> result(lhs);
        details::vec_binary_wrapper<T, std::minus<T>>(result, rhs);
        return result;
    }
    template<class T>
    inline constexpr std::vector<T>& operator-=(std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        return details::vec_binary_wrapper<T, std::minus<T>>(lhs, rhs);
    }
    template<class T>
    inline constexpr std::vector<T> operator*(std::vector<T> lhs, T n)
    {
        std::for_each(std::begin(lhs), std::end(lhs), [n](T& d){ d = std::multiplies<T>()(d, n);});
        return lhs;
    }
    template<class T>
    inline constexpr void normalize(std::vector<T>& m)
    {
        const T n = 1 / std::norm(m);
        std::for_each(std::begin(m), std::end(m), [n](T& d){ d = std::multiplies<T>()(d, n);});
    }
    template<class Scala, int Rows, int Cols>
    inline void normalize(Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        m.normalize();
    }
    
    template<class Scala, int Rows, int Cols>
    inline bool is_zeros(const Eigen::Matrix<Scala, Rows, Cols>& m)
    {
        return m.isZero();
    }
    template<class T>
    inline constexpr bool is_zeros(const std::vector<T>& m)
    {
        const T target{};
        return std::end(m) == std::find_if(
            std::begin(m), std::end(m), [target](const auto& n){
                return std::not_equal_to<T>()(n, target);
            }
        );
    }
}