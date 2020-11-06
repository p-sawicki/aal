#include "gen.h"

int main(int argc, char **argv) {
    int amount = 100;
    double min = 1, max = 100;
    if (argc > 1)
        amount = atoi(argv[1]);
    if (argc > 2)
        min = std::stod(argv[2]);
    if (argc > 3)
        max = std::stod(argv[3]);
    generate(amount, min, max);
}