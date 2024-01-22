#include<iostream>
#include"u8char.h"
#include"u8char.cpp"
#include"array.hpp"
int main(){
    Array<U8Char> arr{"你","好","世","界"};
    for(auto const& element:arr){
        std::cout<<element<<std::endl;
    }
    return 0;
}