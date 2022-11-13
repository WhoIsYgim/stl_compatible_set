#include <iostream>

#include "set.h"

int main(){


    set<int> ab;
    for(int i = 0; i < 10; ++i){
        ab.insert(i);
    }

    for (auto item: ab){
        std::cout << item << std::endl;
    }

    auto rit = ab.rend();

    std::cout << "----------------------------------\n";

//    auto lb = ab.lower_bound(7);
//    if(lb == ab.end()){
//        std::cout << "end\n";
//    } else {
//        std::cout << *lb << std::endl;
//    }


//    for(int i = 0; i < 10; ++i){
//        ab.erase(i);
//    }


    return 0;
}
