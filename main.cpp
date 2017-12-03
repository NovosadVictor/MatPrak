#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "container_class.hpp"

#define N 30
#define S 15


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("\nPlease, write filename\n");
        return -1;
    }

    double jadno = 1.0;
    if (argc == 3)
        jadno = atof(argv[2]);

    std::ifstream file(argv[1]);

    std::vector<int> items(N);
    std::vector<int> cont_sizes (S);

 /*   std::string s;
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
        */
    for (int i = 0; i < N; i++)
        items[i] = rand() % 15 + 1;
    for (int i = 0; i < S; i++)
        cont_sizes[i] = rand() % 50 + 50;

    printf("Jadniy algorithm: %lf\n", jadno);

    time_t start = clock();

    Container container(items, cont_sizes);
    double result = container.sort_items(jadno);

    time_t end = clock();

    printf("Result: %lf\n", result);

    printf("\nExecuting time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    file.close();
    return 0;
}