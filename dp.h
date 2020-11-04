#ifndef DP_H
#define DP_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct Brick {
    double height;
    double width;
    double depth;

    Brick(const double &x, const double &y, const double &z) : depth(z) {
        width = std::min(x, y);
        height = std::max(x, y);
    }

    bool operator<(const Brick& rhs) const {
        return width < rhs.width;
    }
};

struct Tower {
    std::vector<Brick> bricks;
    double depth;

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

Tower get_highest_tower(std::vector<Brick> &bricks);

#endif //DP_H