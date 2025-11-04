#include "random.h"
#include "config.h"

#include <random>

long long random::generate_random(long long min, long long max)
{
    static std::mt19937 gen(IS_RANDOM_USE_SEED ? RANDOM_SEED : std::time(nullptr));
    std::uniform_int_distribution<long long> dist(min, max); // range (min, max)
    return dist(gen);
}

long long random::generate_random(long long max)
{
    return generate_random(0, max);
}

long long random::generate_binary()
{
    return generate_random(0, 1);
}
