#ifndef DISTRIBUTED_SENSORS_UTILS_H
#define DISTRIBUTED_SENSORS_UTILS_H

#include <random>

namespace utils
{

int generate_random_int(int min_range, int max_range)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_int(min_range, max_range);
    return random_int(rng);
}

} // namespace utils

#endif