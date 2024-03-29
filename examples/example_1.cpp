#include <iostream>

#include "set.hpp"

int main(){


    set<int> ab;
    for(int i = 0; i < 10; ++i){
        ab.insert(i);
    }


    set<int> bc(ab);
    auto it = ab.begin();

    set<int> ac(ab.begin(), ab.end());

    for (auto item: ab){
        std::cout << item << std::endl;
    }

    std::cout << "----------------------------------\n";

    auto rit = bc.rbegin();

    for(; rit != bc.rend(); ++rit){
        std::cout << *rit << std::endl;
    }
    std::cout << "----------------------------------\n";

    return 0;
}
