#ifndef _CONTAINER_CLASS_H_
#define _CONTAINER_CLASS_H_

#include <iostream>
#include <vector>
//#include <utility> // pair
#include <algorithm> //sort
#include <set>



class Container {
public:
    Container(std::vector<int> items, std::vector<int> cont_sizes): _items(items), _cont_sizes(cont_sizes) {}
    double sort_items(double jando);
    void perebor(int item, double jadno, std::vector<int> item_container, std::vector<int> item_cont, int &best_size);
private:
    std::vector<int> _items;
    std::vector<int> _cont_sizes;
};


double Container::sort_items(double jadno) {

    std::vector<int> item_container(_items.size());

    std::sort(_items.begin(), _items.end()); // sort item_sizes

    std::vector<int> cont_sizes(_cont_sizes);

    int size = _cont_sizes.size();

    perebor(0, jadno, item_container, cont_sizes, size);

    for (int item = 0; item < _items.size(); item++) {
        bool in_container = false;
        for (int container = 0; container < _cont_sizes.size(); container++)
            if (_items[item] <= _cont_sizes[container]) {
                item_container[item] = container;
                _cont_sizes[container] -= _items[item];
                in_container = true;
                break;
            }
        if (!in_container)
            printf(
                    "\nImpossible to put item %d(size %d) in any container, change container sizes\n",
                    item + 1, _items[item]
            );
    }

    std::set<int> my_set;
    for (int i = 0; i < _items.size(); i++)
        my_set.insert(item_container[i]);

    return size / my_set.size();
}


void Container::perebor(int item, double jadno, std::vector<int> item_container, std::vector<int> cont_sizes, int &best_size) {

    //printf("Perebor: %d\n", item);
    if (item == int(_items.size() * jadno)) {

        for (int item_ = item; item_< _items.size(); item_++) {
            bool in_container = false;
            for (int container = 0; container < _cont_sizes.size(); container++)
                if (_items[item_] <= cont_sizes[container]) {
                    item_container[item_] = container;
                    cont_sizes[container] -= _items[item_];
                    in_container = true;
                    break;
                }
            if (!in_container)
                printf(
                        "\nImpossible to put item %d(size %d) in any container, change container sizes\n",
                        item + 1, _items[item_]
                );
        }

        std::set<int> my_set;
        for (int i = 0; i < _items.size(); i++)
            my_set.insert(item_container[i]);

        if (my_set.size() < best_size)
            best_size = my_set.size();

        return;
    }

    bool in_container = false;
    for (int container = 0; container < _cont_sizes.size(); container++) {
        if (_items[item] <= cont_sizes[container]) {
            item_container[item] = container;
            cont_sizes[container] -= _items[item];
            in_container = true;
            perebor(item + 1, jadno, item_container, cont_sizes, best_size);
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