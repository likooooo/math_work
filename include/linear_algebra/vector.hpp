/*
 * @Description: 
 * @Version: 1.0
 * @Autor: like
 * @Date: 2023-04-22 10:43:47
 * @LastEditors: like
 * @LastEditTime: 2023-04-22 11:13:26
 */
#include <numeric>
#include <cmath>

namespace linear_alg::vector
{
    template<class T>
    inline auto norm(const T& vec)
    {
        using TNum = typename T::value_type;
        const TNum sum = std::accumulate(
            vec.data(), vec.data() + vec.size(), 0,
            [](TNum sum, const TNum d){
                return sum += std::pow(d, 2);
            }
        );
        return std::sqrt(sum);
    } 
}
