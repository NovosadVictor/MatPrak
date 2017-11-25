#ifndef _CONTAINER_CLASS_H_
#define _CONTAINER_CLASS_H_

#include <vector>
#include <utility> // pair
#include <algorithm> //sort
#include <map>



class Container {
public:
    Container(std::vector<int> items, std::vector<int> cont_sizes): _items(items), _cont_sizes(cont_sizes) {}
    std::map<int, int> sort_items();
private:
    std::vector<int> _items;
    std::vector<int> _cont_sizes;
};


std::map<int, int> Container::sort_items() {

    std::map<int, int> item_container; // our map (item : container)

    std::sort(_items.begin(), _items.end()); // sort item_sizes

    for (int item = 0; item < _items.size(); item++) {
        bool in_container = false;
        for (int container = 0; container < _cont_sizes.size(); container++)
            if (_items[item] <= _cont_sizes[container]) {
                item_container.insert(std::make_pair<int, int>(item + 1, container + 1));
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

    return item_container;
}

#endif