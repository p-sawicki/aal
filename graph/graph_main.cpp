#include "graph.h"

int main() {
    Tower tower = graph_get_highest_tower();

    std::cout << "Tower depth: " << tower.depth << "\nBricks\nWidth\t\t\tHeight\t\t\tDepth\n";
    for (Brick brick : tower.bricks)
        std::cout << brick.width << "\t\t\t" << brick.height << "\t\t\t" << brick.depth << "\n";
}