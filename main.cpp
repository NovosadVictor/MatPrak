#include <iostream>
#include <fstream>
#include <sstream>
#include "container_class.hpp"

#define N 10
#define S 5



int main(int argc, char **argv) {
    if (argc != 2) {
        printf("\nPlease, write filename\n");
        return -1;
    }
    std::ifstream file(argv[1]);

    std::vector<int> items(N);
    std::vector<int> cont_sizes (S);

    std::string s;
    std::stringstream ss1;
    std::stringstream ss2;

    std::getline(file, s);
    ss1 << s;
    for (int i = 0; i < N; i++)
        ss1 >> items[i];

    std::getline(file, s);
    ss2 << s;
    for (int i = 0; i < S; i++)
        ss2 >> cont_sizes[i];

    Container container(items, cont_sizes);
    std::map<int, int> result(container.sort_items());

    for (std::map<int, int>::iterator it = result.begin(); it != result.end(); it++)
        printf("\nitem %d is on %d container\n", it->first, it->second);

    file.close();
    return 0;
}