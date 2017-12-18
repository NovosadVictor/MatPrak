#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "container_class.hpp"

#define S 18


int main(int argc, char **argv) {

    std::ofstream file("result.txt");

    int N;
    printf("\nWrite number of items\n");
    std::cin >> N;

    std::vector<int> items(N);
    std::vector<int> cont_sizes (S);

    for (int i = 0; i < N; i++)
        items[i] = rand() % 3 + 10000;

    for (int i = 0; i < S - 14; i++)
        cont_sizes[i] = rand() % 100 + (int(((N - 10) / 8.0)) * 10003);
    for (int i = S - 14; i < S - 10; i++)
        cont_sizes[i] = rand() % 100 + (int(((N - 10) / 8.0) + 0.5) * 10003);
    for (int i = 0; i < 9; i++)
        cont_sizes[S - 10 + i] = rand() % 5 + 10002;
    cont_sizes[S - 1] = 10000000;

    std::vector<double> procents(6);

    procents[0] = 1;
    procents[1] = 1.0 - 5.0 / N;
    procents[2] = 1.0 - 6.0 / N;
    procents[3] = 1.0 - 7.0 / N;
    procents[4] = 1.0 - 8.0 / N;
    procents[5] = 1.0 - 9.0 / N;

    double jadniy;
    for (int i = 0; i < procents.size() - 2; i++) {
        printf("Beginning of %lf algorithm\n", procents[i]);

        time_t start = clock();

        Container container(items, cont_sizes);
        double result = container.sort_items(procents[i]);

        time_t end = clock();

        printf("Result: %lf\n", result);
        file << "Result of " << procents[i] << " algorithm\t" << result << "\n";

        printf("\nExecuting time: %lf\n", ((double) (end - start) / CLOCKS_PER_SEC));
        file << "Executing time\t\t\t" << ((double) (end - start) / CLOCKS_PER_SEC) << "\n";
        if (i == 0) {
            jadniy = ((double) (end - start) / CLOCKS_PER_SEC);
            file << "\n\n\n";
        }
        else {
   //         printf("Time of current vs jadniy time = %lf\n", ((double) (end - start) / CLOCKS_PER_SEC) / jadniy);
    //        file << "Time of current vs jadniy time\t" << ((double) (end - start) / CLOCKS_PER_SEC) / jadniy << "\n\n\n\n";
        }
    }

    file.close();

    return 0;
}