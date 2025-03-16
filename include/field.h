#pragma once

class Snake;
class Food;

class Field {
    int height;
    int width;
    char** grid;
public:
    Field(int height, int width);
    ~Field();

    void import_snake(Snake& snake);
    void import_food(Food& food);
    void print_grid();
    
    bool is_border(int row, int col);

    friend class Snake;
    friend class Food;
};
