#include "../include/random.h"

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int random(int first, int second) {

    std::uniform_int_distribution<int> dist(first, second);
    return dist(gen);
}
