#include <iostream>

#include "set.h"

int main(){

    Tree<int> a;
    a.insert(1);
    set<int> ab;
    for(int i = 0; i < 10; ++i){
        ab.insert(i);
    }

    for (auto item: ab){
        std::cout << item << std::endl;
    }

    std::cout << "----------------------------------\n";

//    auto lb = ab.lower_bound(7);
//    if(lb == ab.end()){
//        std::cout << "end\n";
//    } else {
//        std::cout << *lb << std::endl;
//    }


    std::cout << ab.size() << std::endl;
    std::cout << "----------------------------------\n";
    ab.erase(-1);

    for (auto item: ab){
        std::cout << item << std::endl;
    }
    std::cout << "----------------------------------\n";
    std::cout << ab.size() << std::endl;


    return 0;
}
