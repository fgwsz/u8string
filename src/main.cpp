#include<iostream>
#include"u8char.h"
#include"u8char.cpp"
#include"array.hpp"
#include"test.hpp"
TEST_UNIT(test_hello){
    TEST_CASE(1+1==2);
}
TEST_UNIT(test_array){
    Array<U8Char> arr{"你","好","世","界"};
    TEST_CASE(arr==Array<U8Char>{"hello world"});
    arr.debug_print(std::cout);
}
TEST_UNIT(test_world){
    TEST_CASE(1+1==2);
    TEST_CASE(1+1!=2);
    TEST_CASE(1-1!=0);
    TEST_CASE(1+2==3);
}
int main(){
    TEST_RUN();
    Array<int> arr{1,2,3,4,5};
    std::cout<<arr.reduce([](auto count,auto){return count+1;},0)<<std::endl;;
    std::cout<<arr.map([](int value){return value*2;})
        .filter([](int value){return value>5;})
        .reduce([](int val1,int val2){return val1+val2;})
        <<std::endl;
    arr.resize(10);
    std::cout<<arr<<std::endl;
    arr.resize(1);
    std::cout<<arr<<std::endl;
    arr={1,0,2,0,3,0,4,0};
    arr.foreach_reverse_iterator([](auto iter){
        if(*iter==0){
            iter.container()->erase(iter.index());
        }
    });
    arr={1,2,3,2,4,2};
    std::cout<<arr<<std::endl;
    arr.foreach_iterator([](auto iter){
        if(*iter==2){
            *iter=100;
        }
    });
    std::cout<<arr<<std::endl;
    return 0;
}