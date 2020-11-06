#include "gen.h"
#include "dp.h"
#include <chrono>
#include <thread>
#include <mutex>

const int DEFAULT_REPEATS = 16;
const int MAX_BRICKS = 20000;
double average_duration;
int repeats;
std::mutex average_duration_mutex;

void timer(int bricks) {
    auto stream = std::stringstream();
    generate(bricks, 1, bricks, stream);

    auto start = std::chrono::steady_clock::now();
    get_highest_tower(stream);
    auto end = std::chrono::steady_clock::now();

    std::lock_guard<std::mutex> guard(average_duration_mutex);
    average_duration += std::chrono::duration<double>(end - start).count() / repeats;
}

int main(int argc, char **argv) {
    repeats = argc > 1 ? atoi(argv[1]) : DEFAULT_REPEATS;

    std::cout << "N;Average duration (seconds)\n";
    for (int bricks = 13000; bricks <= 13000; bricks += 100) {
        average_duration = 0;
        auto threads = std::vector<std::thread>();
        for (int i = 0; i < repeats; ++i)
            threads.emplace_back(std::thread(timer, bricks));
        std::for_each(threads.begin(), threads.end(), [](std::thread &thread) {thread.join(); });
        std::cout << bricks << ";" << average_duration << "\n";
    }
}