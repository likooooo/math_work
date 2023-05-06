/*
 * @Description: https://inst.eecs.berkeley.edu/~ee127/sp21/livebook/l_mats_basics.html
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-05-01 13:19:14
 * @LastEditors: like
 * @LastEditTime: 2023-05-05 21:10:25
 */
#pragma once
#include "vector.hpp"

namespace linear_alg::matrix
{
    namespace details
    {
        template<class Scala>
        using vec_matrix = std::vector<std::vector<typename Scala>>;
        template<class Scala>
        constexpr inline auto init_matrix(const int dim0, const int dim1)
        {
            vec_matrix<typename Scala> vec;
            vec.reserve(dim1);
            std::for_each(std::begin(vec), std::end(vec), [dim0](auto& c){c.reserve(dim0);});
            return vec;
        }
        template<class Scala, int Row = -1, int Col = -1>
        constexpr inline auto init_matrix(const int dim0 = -1, const int dim1 = -1)
        {
            using TMatrix = Eigen::Matrix<typename Scala, Row, Col>; 
            TMatrix m;
            if constexpr(0 < Row && 0 < Col)/* do noting */;
            else if constexpr(0 < Row || 0 < Col) m = TMatrix(dim0);
            else m = TMatrix(dim0, dim1);
            return m;
        }
    }

    template<class TLhs, class TRhs> 
    constexpr inline auto inner_product(const TLhs& lhs, const TRhs& rhs)
    {
        return lhs * rhs;
    }
    template<class Scala> 
    constexpr inline auto inner_product(const details::vec_matrix<typename Scala>& lhs, const details::vec_matrix<typename Scala>& rhs)
    { 
        const int lhs_dim0 = std::size(lhs), lhs_dim1 = std::size(lhs[0]),
            rhs_dim0 = std::size(rhs), rhs_dim1 = std::size(rhs[0]);
        assert(lhs_dim0 == rhs_dim0);

        auto result = details::init_matrix(rhs_dim1, lhs_dim1);

        vector::inner_product()

        return lhs * rhs;
    }
    
}
