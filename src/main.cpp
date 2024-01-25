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
    std::cout<<arr.reduce([](auto count,auto){return count+1;},1000)<<std::endl;;
    std::cout<<arr.map([](int value){return value*2;})
        .filter([](int value){return value>5;})
        .reduce([](int val1,int val2){return val1+val2;});
    arr.map([](int element){return Array<int>{element};}).debug_print(std::cout);
    return 0;
}