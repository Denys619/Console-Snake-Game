#include "../include/field.h"
#include "../include/snake.h"
#include "../include/food.h"
#include "../include/terminal.h"
#include "../include/config.h"

#include <chrono>
#include <cstdlib>
#include <thread>
#include <unistd.h>


int main() {
    Field field(height, width);
    Snake snake;
    Food food;
    pthread_t keyboard_thread;
    
    field.import_snake(snake);
    field.import_food(food);
    snake.start_listening_keyboard(keyboard_thread);
    
    setup_termios();
    
    while(true) {
        field.print_grid();
        snake.snake_position_update(field);

        if (snake.head_on_border(field) || snake.head_on_body()) break;
        else if (snake.head_on_food(food)) {
            food.generate_new_food(snake);
            field.import_food(food);
            snake.grow();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    reset_termios();
    snake.stop_listening_keyboard(keyboard_thread);
}
