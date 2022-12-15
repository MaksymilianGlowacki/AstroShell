//
// Created by Maksymilian Głowacki on 22/10/2022.
//
#include <vector>
#include <eigen/Eigen/Eigen>
#include <numeric>
#include <algorithm>
#include <astroshell/phase/phase.h>

#ifndef ASTROSHELL_SLM_H
#define ASTROSHELL_SLM_H

namespace astroshell
{
    void getSLM(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices,
                Eigen::Array<double, -1, 2> &frequencies);
    double maxFreq(Eigen::Array<double, -1, 2> &frequencies, Eigen::Array<long, -1, 1> &freq_indices);

}

#endif //ASTROSHELL_SLM_H
