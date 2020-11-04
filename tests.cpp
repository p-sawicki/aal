#include "dp.h"
#include <assert.h>

void test_highest_tower1() {
    auto bricks = std::vector<Brick> {
        {1,2,3}, {3,1,2}, {3,2,1}, {1,4,5}, {1,5,4}, {4,5,1}
    };
    Tower t = get_highest_tower(bricks);

    assert(t.depth == 6);
    assert(t.bricks.size() == 2);
}

void test_highest_tower2() {
    auto bricks1 = std::vector<Brick> {
        {1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}, {5, 5, 5}, {6, 6, 6}
    };
    auto bricks2 = std::vector<Brick> {
        {3, 3, 3}, {6, 6, 6}, {1, 1, 1}, {4, 4, 4}, {2, 2, 2}, {5, 5, 5}
    };
    Tower t1 = get_highest_tower(bricks1);
    Tower t2 = get_highest_tower(bricks2);

    assert(t1.depth == t2.depth);
    assert(t1.bricks.size() == t2.bricks.size());
    assert(t1.depth == 21);
    assert(t1.bricks.size() == 6);
}

int main() {
    test_highest_tower1();
    test_highest_tower2();
}