#pragma once

#include "field.h"
#include "food.h"
#include "direction.h"

#include <iostream>
#include <vector>

class Snake {
    int length;
    std::vector<std::pair<int, int>> body_position;
public:
    Direction direction;
    Direction next_direction;
    Snake();

    static void* listen_keyboard(void* arg);
    void start_listening_keyboard(pthread_t& keyboard_thread);
    void stop_listening_keyboard(pthread_t& keyboard_thread);

    void snake_position_update (Field& field);
    bool head_on_border(Field& field);
    bool head_on_body();
    bool head_on_food(Food& food);

    void grow();

    friend class Field;
    friend class Food;
};
