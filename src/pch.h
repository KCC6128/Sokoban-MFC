// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "framework.h"

using namespace std;

#define wall_character   'H'
#define box_character    'B'
#define dest_character   ' '
#define worker_character 'W'
#define blank_character '0'
#define arrive_character 'A'

enum Direction { UP, DOWN, LEFT, RIGHT };
#include "Coordinate.h"

#endif //PCH_H
