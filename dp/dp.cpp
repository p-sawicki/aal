#include "dp.h"

Tower get_highest_tower(std::vector<Brick> &bricks) {
    std::sort(bricks.begin(), bricks.end());
    auto towers = std::list<Tower>();

    while (!bricks.empty()) {
        double cutoff = 0;
        auto it = bricks.begin();
        auto apexes = std::vector<Brick>();

        while (it != bricks.end()) {
            Brick brick = *it;
            bool is_apex = true;

            for (Brick apex : apexes) {
                if (brick.width > apex.width && brick.height > apex.height) {
                    is_apex = false;
                    break;
                }
            }
            if (is_apex) {
                apexes.push_back(brick);
                cutoff = std::max(cutoff, brick.height);
                bricks.erase(it);
            } else
                ++it;
            
            if (it != bricks.end() && it->width > cutoff)
                break;
        }

        for (const Brick &apex : apexes) {
            Tower *best_tower_for_apex = nullptr;
            for (auto tower = towers.begin(); tower != towers.end(); ++tower) {
                if (apex.width > tower->bricks.back().width && apex.height > tower->bricks.back().height) {
                    best_tower_for_apex = &*tower;
                    break;
                }
            }
            Tower new_tower = Tower(apex, best_tower_for_apex);
            towers.insert(std::lower_bound(towers.begin(), towers.end(), new_tower, 
                [](const Tower& a, const Tower& b) {return a.depth > b.depth; }), new_tower);
        }
    }
    return towers.front();
}

Tower get_highest_tower(std::istream &stream) {
    int bricks_amount = 0;
    stream >> bricks_amount;

    auto bricks = std::vector<Brick>();
    for (int i = 0; i < bricks_amount; ++i) {
        double x, y, z;
        stream >> x >> y >> z;
        bricks.emplace_back(Brick(x, y, z));
        if (x != z)
            bricks.emplace_back(Brick(z, y, x));
        if (y != z)
            bricks.emplace_back(Brick(x, z, y));
    }

    return get_highest_tower(bricks);
}