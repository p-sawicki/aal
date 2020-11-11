#include "gen.h"
#include "dp.h"
#include "graph.h"
#include "bf.h"

const std::string ALGORITHM_OPTION = "--algorithm";
const std::string ALGORITHM_DP = "dp";
const std::string ALGORITHM_GRAPH = "graph";
const std::string ALGORITHM_BF = "bf";
const std::string REPEATS_OPTION = "--repeat";
const std::string MIN_OPTION = "--min";
const std::string MAX_OPTION = "--max";
const std::string STEP_OPTION = "--step";

enum Algorithm {DP, GRAPH, BF};

void error(const std::string &msg) {
    std::cerr << msg;
    exit(1);
}

int main(int argc, char **argv) {
    const std::string OPTION_ERROR = "Usage:\n" + std::string(argv[0]) + " [--algorithm [dp|graph|bf]] [--repeat N] [--min N] [--max N] [--step N]\n";

    Algorithm algorithm = DP;
    unsigned int repeats = 1, min = 100, max = 20000, step = 100;

    for (int i = 1; i + 1 < argc; i += 2) {
        int j = i + 1;
        if (argv[i] == ALGORITHM_OPTION) {
            if (argv[j] == ALGORITHM_GRAPH)
                algorithm = GRAPH;
            else if (argv[j] == ALGORITHM_BF)
                algorithm = BF;
            else if (argv[j] != ALGORITHM_DP)
                error(OPTION_ERROR);
        } else if (argv[i] == REPEATS_OPTION) 
            repeats = atoi(argv[j]);
        else if (argv[i] == MIN_OPTION)
            min = atoi(argv[j]);
        else if (argv[i] == MAX_OPTION)
            max = atoi(argv[j]);
        else if (argv[i] == STEP_OPTION)
            step = atoi(argv[j]);
        else 
            error(OPTION_ERROR);
    }

    std::cout << "N,Average time (seconds)\n";
    for (unsigned int bricks = min; bricks <= max; bricks += step) {
        double average_duration = 0;
        for (unsigned int i = 0; i < repeats; ++i) {
            auto stream = std::stringstream();
            generate(bricks, 1, bricks, stream);

            auto start = std::chrono::steady_clock::now();
            switch (algorithm) {
                case DP:
                    get_highest_tower(stream);
                    break;
                case GRAPH:
                    graph_get_highest_tower(stream);
                    break;
                case BF:
                    bf_get_highest_tower(stream);
                    break;
            }
            auto end = std::chrono::steady_clock::now();
            average_duration += std::chrono::duration<double>(end - start).count() / repeats;
        }
        std::cout << bricks << "," << average_duration << "\n";
    }
}