#pragma once

#include <array>
#include <random>

static std::mt19937& mt()
{
    static thread_local std::mt19937 engine{};
    return engine;
}

static void seed()
{
    std::array<uint32_t, std::mt19937::state_size> seed_data;
    std::random_device                             rd;
    std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
    std::seed_seq seq(seed_data.begin(), seed_data.end());
    mt().seed(seq);
}

static float randomf(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(mt());
}
