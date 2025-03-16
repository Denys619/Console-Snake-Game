#include "../include/snake.h"
#include "../include/food.h"
#include "../include/direction.h"

Snake::Snake(): length(4), direction(LEFT), next_direction(LEFT) {
    
    for(int i = 0; i < length; ++i) {
        body_position.push_back({7, 15 + i});
    }
}

void* Snake::listen_keyboard(void* arg) {

    Snake* snake = static_cast<Snake*>(arg);

    while (true) {
        char key = getchar();
        
        if (key == 'w' && snake->direction != DOWN) snake->next_direction = UP;
        else if (key == 'a' && snake->direction != RIGHT) snake->next_direction = LEFT;
        else if (key == 's' && snake->direction != UP) snake->next_direction = DOWN;
        else if (key == 'd' && snake->direction !=  LEFT) snake->next_direction = RIGHT;
    }
    pthread_exit(nullptr);
}

void Snake::start_listening_keyboard(pthread_t& keyboard_thread) {
    pthread_create(&keyboard_thread, nullptr, Snake::listen_keyboard, this);
}

void Snake::stop_listening_keyboard(pthread_t& keyboard_thread) {
    pthread_cancel(keyboard_thread);
    pthread_join(keyboard_thread, nullptr);
}

void Snake::snake_position_update(Field& field){
    direction = next_direction;
    std::pair<int, int>& head_position = body_position[0];

    field.grid[head_position.first][head_position.second] = ' ';
    for(int i = 1; i < body_position.size(); ++i) {
        if(!field.is_border(body_position[i].first, body_position[i].second)) {
            field.grid[body_position[i].first][body_position[i].second] = ' ';          
        }
    }

    std::pair<int, int> prev_body_element_position = head_position;

    switch (direction) {
        case UP: --head_position.first; break;
        case DOWN: ++head_position.first; break;
        case LEFT: --head_position.second; break;
        case RIGHT: ++head_position.second; break;            
    }

    std::pair<int, int> temp_position;
    for(int i = 1; i < body_position.size(); ++i) {
        temp_position = body_position[i];
        body_position[i] = prev_body_element_position;
        prev_body_element_position = temp_position;
    }

    field.grid[head_position.first][head_position.second] = 'O';
    for(int i = 1; i < body_position.size(); ++i) {
        field.grid[body_position[i].first][body_position[i].second] = 'o';
    }
}

bool Snake::head_on_border(Field& field) {
    std::pair<int, int>& head_position = body_position[0];

    if (head_position.first == 0 || 
            head_position.second == 0 || 
            head_position.first == field.height - 1 || 
            head_position.second == field.width - 1) return true;
    return false;
}

bool Snake::head_on_body() {
    std::pair<int, int>& head_position = body_position[0];

    for(int i = 1; i < body_position.size(); ++i) {
        if (head_position.first == body_position[i].first && head_position.second == body_position[i].second) return true;
    }

    return false;
}

bool Snake::head_on_food(Food& food) {
    std::pair<int, int>& head_position = body_position[0];

    if (head_position.first == food.position.first && head_position.second == food.position.second) return true;
    return false;
}

void Snake::grow() {
    std::pair<int, int> tail = body_position.back();

    switch (direction) {
        case UP: ++tail.first; break;
        case DOWN: --tail.first; break;
        case LEFT: ++tail.second; break;
        case RIGHT: --tail.second; break; 
    }

    body_position.push_back(tail);
}
