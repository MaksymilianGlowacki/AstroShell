//
// Created by Maksymilian Głowacki on 13/11/2022.
//
#include "Methods.h"

#ifndef ASTROSHELL_GETPERIOD_H
#define ASTROSHELL_GETPERIOD_H

namespace astroshell
{
    double getPeriod(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices);
}

#endif //ASTROSHELL_GETPERIOD_H
