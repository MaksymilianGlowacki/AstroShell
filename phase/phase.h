//
// Created by Maksymilian Głowacki on 21/10/2022.
//
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <eigen/Eigen/Eigen>

#ifndef ASTROSHELL_FUNCTIONS_H
#define ASTROSHELL_FUNCTIONS_H

namespace astroshell
{
    void phase(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices, double frequency);
}
#endif //ASTROSHELL_FUNCTIONS_H
