#include "gen.h"
#include "dp.h"
#include <chrono>

int main() {
    const int REPEATS = 1;
    const int MAX_BRICKS = 1000000;

    std::cout << "N\t\t\tAverage duration (seconds)\n";
    for (int bricks = 1000; bricks <= MAX_BRICKS; bricks *= 2) {
        double average_duration = 0;
        for (int i = 0; i < REPEATS; ++i) {
            auto stream = std::stringstream();
            generate(bricks, 1, bricks, stream);

            auto start = std::chrono::steady_clock::now();
            get_highest_tower(stream);
            auto end = std::chrono::steady_clock::now();
            average_duration += std::chrono::duration<double>(end - start).count() / REPEATS;
        }
        std::cout << bricks << "\t\t\t" << average_duration << "\n";
    }
}