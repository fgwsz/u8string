#ifndef __TEST_ARRAY_HPP__
#define __TEST_ARRAY_HPP__
#include<iostream>
#include"array.hpp"
void test_array_ctor(){
    using type=int;
    Array<int> arr_1;
    arr_1.debug_print(::std::cout);
    Array<int> arr_2({0,1,2,3,4,5,6,7,8,9,10,11});
    arr_2.debug_print(::std::cout);
    int arr[]={11,10,9,8,7,6,5,4,3,2,1,0};
    Array<int> arr_3(arr);
    arr_3.debug_print(::std::cout);
    Array<int> arr_4(arr_3);
    arr_4.debug_print(::std::cout);
    Array<int> arr_5(Array<int>{1,2,4,6,8,16,32,64,128,256,512,1024,2048});
    arr_5.debug_print(::std::cout);
}
void test_array_insert(){

}
#endif//__TEST_ARRAY_HPP__