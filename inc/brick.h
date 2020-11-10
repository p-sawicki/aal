#ifndef BRICK_H
#define BRICK_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>

struct Brick {
    double height;
    double width;
    double depth;

    Brick(const double &x, const double &y, const double &z) : depth(z) {
        width = std::min(x, y);
        height = std::max(x, y);
    }

    bool operator<(const Brick& rhs) const;
    bool operator>(const Brick& rhs) const;
};


struct Tower {
    std::vector<Brick> bricks;
    double depth;

    Tower() : depth(0) {};

    Tower(const Brick &base, Tower* tower) {
        depth = base.depth;
        if (tower != nullptr) {
            depth += tower->depth;
            bricks = tower->bricks;
        } else
        {
            bricks = std::vector<Brick>();
        }
        bricks.push_back(base);
    }
};

#endif //BRICK_H