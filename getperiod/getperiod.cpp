#include "getperiod.h"

double astroshell::getPeriod(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices)
{
    Eigen::Array<double, -1, 2> frequencies(70000, 2);
    auto a = Eigen::ArrayXd::LinSpaced(10000, 0.00001, 0.1);
    auto b = Eigen::ArrayXd::LinSpaced(30000, 0.001, 30);
    auto c = Eigen::ArrayXd::LinSpaced(30000, 1, 3000);
    frequencies.col(0) << a, b, c;

    Eigen::Array<long, -1, 1> freq_indices(70000, 1);
    freq_indices = Eigen::Array<long, -1, 1>::LinSpaced(70000, 0, 69999);

    astroshell::getSLM(phot, indices, frequencies);
    std::sort(freq_indices.begin(), freq_indices.end(),
              [&frequencies](long a, long b){return frequencies(a, 1) < frequencies(b, 1);});

    return 1.0 / astroshell::maxFreq(frequencies, freq_indices);
}
