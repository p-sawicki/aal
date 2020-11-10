#ifndef DP_H
#define DP_H

#include "brick.h"

Tower get_highest_tower(std::istream &stream = std::cin);
Tower get_highest_tower(std::vector<Brick> &bricks);

#endif //DP_H