/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-22 10:43:47
 * @LastEditors: like
 * @LastEditTime: 2023-04-29 12:14:15
 */
#include <numeric>
#include <cmath>
#include <type_traits>
#include <limits>
#include <std_extention_for_eigen.hpp>

namespace linear_alg::vector
{
    namespace details
    {
        template<class T>
        inline auto norm_l1(const T& vec)
        {
            return std::accumulate(
                std::begin(vec), std::end(vec), 0,  
                [](typename T::value_type sum, const typename T::value_type d){
                    return sum += std::abs(d);
                }
            );
        }   
        template<class T>
        inline auto norm_l2(const T& vec)
        {
            return std::sqrt(
                std::accumulate(
                    std::begin(vec), std::end(vec), T::value_type{0},  
                    [](typename T::value_type sum, const typename T::value_type d){
                        return sum += std::pow(d, 2);
                    }
                )
            );
        } 
        template<class T>
        inline auto norm_linf(const T& vec)
        {
            return std::max(std::begin(vec), std::end(vec));
        } 
    }
    enum class NormsType : int
    {
        L1 = 0,
        L2,
        LInf = (std::numeric_limits<int>::max)()
    };  
    template<class T, NormsType N = NormsType::L2>
    constexpr inline typename auto norm(const T& vec)
    {
        using namespace details;
        if constexpr(N == NormsType::L1) return norm_l1(vec);
        else if constexpr(N == NormsType::L2)return norm_l2(vec);
        else if constexpr(N == NormsType::LInf)return norm_linf(vec);
        else static_assert(false, "unsupport type");
    }    
    template<class T>
    constexpr inline auto inner_product(const T& vecLhs, const T& vecRhs)
    {
        assert(std::size(vecLhs) == std::size(vecRhs));
        return std::inner_product(std::begin(vecLhs), std::end(vecLhs), std::begin(vecRhs), typename T::value_type{0});
    } 
    template<class T>
    constexpr inline auto angle_cos(const T& vecLhs, const T& vecRhs)
    {
        if constexpr(std::integral_constant_v<typename T::value_type>)
            return static_cast<double>(inner_product(vecLhs, vecRhs)) / (norm(vecLhs) * norm(vecRhs));
        else
            return (inner_product(vecLhs, vecRhs)) / (norm(vecLhs) * norm(vecRhs));
    }
    template<class T>
    inline void normalize(T& vec)
    {
        std_extention_for_math_work::normalize(vec);
    }
    template<class T>
    constexpr inline T projection(const T& x, const T& x0, const T& u /* x0 + t*u describe a subspace cross x0 with direction is t*/)
    {
        using namespace std_extention_for_math_work;
        
        T normalized_u(u);
        normalize(normalized_u);
        const auto t = inner_product(x, normalized_u);
        return x0 + u * t;
    }
        template<class T>
    constexpr inline T projection(const T& x, const T& u /* x0 + t*u describe a subspace cross x0 with direction is t*/)
    {
        using namespace std_extention_for_math_work;
        
        T normalized_u(u);
        normalize(normalized_u);
        const auto t = inner_product(x, normalized_u);
        return u * t;
    }
    template<class T>
    constexpr inline T projection_eigen_only(const T& x, const T& x0, const T& u)
    {
        auto u1 = u.transpose();
        return x0 + (u1 * ( x - x0) * u) / (u1 *u);
    }
    template<class T>
    constexpr inline T projection_eigen_only(const T& x, const T& u)
    {
        auto u1 = u.transpose();
        return (u1 * x * u) / (u1 *u);
    }
    template<class T>
    constexpr inline std::vector<T> gram_schmidt_procedure(std::vector<T> an)
    {
        using namespace std_extention_for_math_work;

        assert(std::end(an) == std::find_if(std::begin(an) + 1, std::end(an), [n = std::size(an[0])](const auto& ai){return ai.size() != n;}));
        const size_t dim = std::size(an[0]);
        const auto end_of_an = std::remove_if(std::begin(an), std::end(an), [](const auto& a){return is_zeros(a);});   
        assert(std::distance(std::begin(an), end_of_an) >= dim);

        std::vector<T> qn;
        qn.reserve(dim);
        {
            auto q0 = an[0];
            normalize(q0);
            qn.push_back(q0);
        }
        std::for_each(std::begin(an) + 1, end_of_an,
            [&](const auto& ai){
                typename T sum = projection(ai, qn[0]);
                typename T q = ai - std::accumulate(
                    std::begin(qn) + 1, std::end(qn), sum,
                    [&ai](auto& sum, const auto& qi){
                        return sum += projection(ai, qi);
                    }
                );
                if(!is_zeros(q))
                {
                    normalize(q);
                    qn.push_back(std::move(q));
                }
            }
        );
        return qn;
    }
}
