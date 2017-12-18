#ifndef _CONTAINER_CLASS_H_
#define _CONTAINER_CLASS_H_

#include <iostream>
#include <vector>
#include <algorithm> //sort
#include <set>



class Container {
public:
    Container(std::vector<int> items, std::vector<int> cont_sizes): _items(items), _cont_sizes(cont_sizes) {}
    double sort_items(double jando);
    void perebor(int item, std::vector<int> item_container, std::vector<int> item_cont, int &best_size, int last_cont);
private:
    std::vector<int> _items;
    std::vector<int> _cont_sizes;
};


double Container::sort_items(double jadno) {

    std::vector<int> item_container(_items.size());

    std::sort(_items.begin(), _items.end()); // sort item_sizes
    std::reverse(_items.begin(), _items.end());

    std::vector<int> cont_sizes_backup(_cont_sizes);

    int size = _cont_sizes.size();
    int last_cont;

    for (int item = 0; item < int(_items.size() * jadno); item++) {
        bool in_container = false;
        for (int container = 0; container < _cont_sizes.size(); container++)
            if (_items[item] <= _cont_sizes[container]) {
                item_container[item] = container;
                _cont_sizes[container] -= _items[item];
                in_container = true;
                if (item == int(_items.size() * jadno) - 1)
                    last_cont = container;

                break;
            }
        if (!in_container)
            printf(
                    "\nImpossible to put item %d(size %d) in any container, change container sizes\n",
                    item + 1, _items[item]
            );
    }

    std::vector<int> cont_sizes(_cont_sizes);
    printf("Done\n");


    for (int i = 0; i <= last_cont; i++)
        if (_items[int(_items.size() * jadno) - 1] <= _cont_sizes[i]) {
            last_cont = i;
            break;
        }

    printf("%d last cont\n", last_cont);
    perebor(int(_items.size() * jadno) - 1, item_container, cont_sizes, size, last_cont);

    std::set<int> my_set_1;
    for (int i = 0; i < _items.size(); i++)
        my_set_1.insert(item_container[i]);

    printf("\n1 size: %lu\n", my_set_1.size());


    for (int item = 0; item < _items.size(); item++) {
        bool in_container = false;
        for (int container = 0; container < _cont_sizes.size(); container++)
            if (_items[item] <= cont_sizes_backup[container]) {
                item_container[item] = container;
                cont_sizes_backup[container] -= _items[item];
                in_container = true;
                break;
            }
        if (!in_container)
            printf(
                    "\nImpossible to put item %d(size %d) in any container, change container sizes\n",
                    item + 1, _items[item]
            );
    }

    std::set<int> my_set_2;
    for (int i = 0; i < _items.size(); i++)
        my_set_2.insert(item_container[i]);

    printf("\n2 size: %lu\n", my_set_2.size());


    return double(my_set_1.size()) / my_set_2.size();
}


void Container::perebor(int item, std::vector<int> item_container, std::vector<int> cont_sizes, int &best_size, int last_cont) {

    //printf("Perebor: %d\n", item);
    if (item == _items.size()) {

        std::set<int> my_set;
        for (int i = 0; i < _items.size(); i++)
            my_set.insert(item_container[i]);

        if (my_set.size() < best_size)
            best_size = my_set.size();

        return;
    }

    bool in_container = false;
    for (int container = last_cont; container < cont_sizes.size(); container++) {
        if (_items[item] <= cont_sizes[container]) {

            item_container[item] = container;
            cont_sizes[container] -= _items[item];
            in_container = true;
            perebor(item + 1, item_container, cont_sizes, best_size, last_cont);
            if (item != 0)
                cont_sizes[item_container[item]] += _items[item];
        }
    }
    if (!in_container)
        printf(
                "\nImpossible to put item %d(size %d) in any container, change container sizes\n",
                item + 1, _items[item]
        );
}

#endif