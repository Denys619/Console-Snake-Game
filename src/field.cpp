#include "../include/field.h"
#include "../include/snake.h"
#include "../include/food.h"

#include <cstdlib>

Field::Field(int height, int width): height(height), width(width) {

    grid = new char*[height];
    grid[0] = new char[height * width];
    for(int i = 1; i < height; ++i) {
        grid[i] = grid[0] + width * i;
    }

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            
            if(i == 0 || j == 0 || i == height - 1 || j == width - 1) grid[i][j] = '#';
            else grid[i][j] = ' ';
        }
    }
}

Field::~Field() {
    delete[] grid[0];
    delete[] grid;
}

//-----------------------------------------------------------------------------------------

void Field::import_snake(Snake& snake) {
   
    grid[snake.body_position[0].first][snake.body_position[0].second] = 'O';
    for(int i = 1; i < snake.body_position.size(); ++i) {
        grid[snake.body_position[i].first][snake.body_position[i].second] = 'o';

    }
}

//-----------------------------------------------------------------------------------------

void Field::import_food(Food& food) {
    grid[food.position.first][food.position.second] = '*';
}

//-----------------------------------------------------------------------------------------

void Field::print_grid() {
    std::cout << "\033[H";

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
    std::cout.flush();
}

//-----------------------------------------------------------------------------------------

bool Field::is_border(int row, int col) {
    return (row == 0 || col == 0 || row == height - 1 || col == width - 1);
}
