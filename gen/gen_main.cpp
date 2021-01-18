/*
 * Wrapper konieczny do zbudowania osobnej aplikacji
 * Autorzy: Piotr Sawicki, Paweł Wieczorek
 */

#include "gen.h"

const std::string AMOUNT_OPTION = "--amount";
const std::string MIN_OPTION = "--min";
const std::string MAX_OPTION = "--max";

int main(int argc, char **argv) {
    int amount = 100;
    double min = 0.1, max = 100;
    for (int i = 1; i + 1 < argc; i += 2) {
        int j = i + 1;
        if (argv[i] == AMOUNT_OPTION)
            amount = atoi(argv[j]);
        else if (argv[i] == MIN_OPTION)
            min = std::stod(argv[j]);
        else if (argv[i] == MAX_OPTION)
            max = std::stod(argv[j]);
        else {
            std::cerr << "Usage:\n " << argv[0] << " [--amount N] [--min R] [--max R]\n";
            exit(1);
        }
    }
    generate(amount, min, max);
}