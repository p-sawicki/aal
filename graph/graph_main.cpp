#include "graph.h"

int main() {
    auto start = std::chrono::system_clock::now();
    Tower tower = graph_get_highest_tower();
    auto end = std::chrono::system_clock::now();

    std::cout << "Tower depth: " << tower.depth << "\nBricks\nWidth\t\t\tHeight\t\t\tDepth\n";
    for (Brick brick : tower.bricks)
        std::cout << brick.width << "\t\t\t" << brick.height << "\t\t\t" << brick.depth << "\n";
    std::cout << "Time (seconds): " << std::chrono::duration<double>(end - start).count() << "\n";
}