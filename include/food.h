#pragma once

#include <utility>

#include "../include/snake.h"

class Food {
public:
    std::pair<int, int> position;
    
    Food();

    void generate_new_food(Snake& snake);
};
