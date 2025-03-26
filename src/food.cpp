#include "../include/food.h"
#include "../include/random.h"
#include "../include/config.h"

Food::Food() {
    position = {random(1, MAX_POS_Y), random(1, MAX_POS_X)};
}

//-----------------------------------------------------------------------------------------

void Food::generate_new_food(Snake& snake) {
    position = {random(1, MAX_POS_Y), random(1, MAX_POS_X)};

    for(int i = 0; i < snake.body_position.size(); ++i) {
        if(position.first == snake.body_position[i].first && position.second == snake.body_position[i].second) {
            generate_new_food(snake);
            break;
        }
    }
}
