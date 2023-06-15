#include "Methods.h"

#ifndef ASTROSHELL_GETPERIOD_H
#define ASTROSHELL_GETPERIOD_H

namespace astroshell
{
    double getPeriod(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices);
}

#endif //ASTROSHELL_GETPERIOD_H
