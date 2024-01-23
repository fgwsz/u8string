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
}
TEST_UNIT(test_world){
    TEST_CASE(1+1==2);
    TEST_CASE(1+1!=2);
    TEST_CASE(1-1!=0);
    TEST_CASE(1+2==3);
}
int main(){
    TEST_RUN();
    return 0;
}