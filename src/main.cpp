#include<iostream>
#include"u8char.h"
#include"u8char.cpp"
#include"array.hpp"
#include"test.hpp"
TEST_DEF(test_hello){
    TEST_REQ(1+1==2);
}
TEST_DEF(test_array){
    Array<U8Char> arr{"你","好","世","界"};
    TEST_REQ(arr==Array<U8Char>{"hello world"});
}
int main(){
    TEST_RUN();
    return 0;
}