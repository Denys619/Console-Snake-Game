#pragma once

#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>

void setup_termios();
void reset_termios();
