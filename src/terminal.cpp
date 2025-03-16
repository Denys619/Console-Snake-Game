#include <termios.h>
#include <iostream>

#include "../include/terminal.h"

struct termios orig_termios;

void setup_termios() {
    std::cout << "\033[2J\033[H";

    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void reset_termios() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
