//
// Created by Maksymilian Głowacki on 22/10/2022.
//

#include "Methods.h"

void astroshell::getSLM(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices,
                        Eigen::Array<double, -1, 2> &frequencies)
{
    std::vector<unsigned long> indices2(indices.size());
    indices2[0] = indices.size() - 1;
    std::iota(indices2.begin() + 1, indices2.end(), 0);

    for(long i = 0; i < frequencies.col(0).size(); ++i)
    {
        astroshell::phase(phot, indices, frequencies(i, 0));
        frequencies(i, 1) = (phot(indices, 2)
                - phot(indices, 2)(indices2)).square().sum();
    }
}

double astroshell::maxFreq(Eigen::Array<double, -1, 2> &frequencies, Eigen::Array<long, -1, 1> &freq_indices)
{
    auto min_res = frequencies(freq_indices[0], 1);
    int counter = 0;
    for(const long freq_index : freq_indices)
    {
        if(frequencies(freq_index, 1) > 1.1 * min_res)
        {
            break;
        }
        else
        {
            ++counter;
        }
    }
    auto min_vals = frequencies(freq_indices(Eigen::seq(0, counter - 1)), 0);
    std::sort(min_vals.begin(), min_vals.end(), std::greater{});
    return min_vals[0];
}
