#ifndef __TEST_ARRAY_HPP__
#define __TEST_ARRAY_HPP__
#include"array.hpp"
#include"test.hpp"
// TEST API:
// [o] constexpr Array()noexcept;
// [o] constexpr Array(Array<_Type> const& array)noexcept;
// [o] constexpr Array(Array<_Type>&& array)noexcept;
// [o] template<size_t _size>
//     constexpr Array(_Type const(&array)[_size])noexcept;
// [o] constexpr Array(::std::initializer_list<_Type> const& list)noexcept;
// [o] constexpr Array(size_t count,_Type const& value={})noexcept;
// [o] constexpr ~Array()noexcept;
// [o] constexpr Array<_Type>& operator=(Array<_Type> const& array)noexcept;
// [o] constexpr Array<_Type>& operator=(Array<_Type>&& array)noexcept;
// [o] template<size_t _size>
//     constexpr Array<_Type>& operator=(_Type const(&array)[_size])noexcept;
// [o] constexpr Array<_Type>& operator=(::std::initializer_list<_Type> const& list)noexcept;
// [o] constexpr bool insert(size_t index,_Type const& value)noexcept;
// [o] constexpr bool insert(size_t index,_Type const& value,size_t count)noexcept;
// [o] constexpr bool insert(size_t index,Array<_Type> const& array)noexcept;
// [o] constexpr void push_back(_Type const& value)noexcept;
// [o] constexpr bool erase(size_t index)noexcept;
// [o] constexpr bool erase(size_t index,size_t count)noexcept;
// [o] constexpr void pop_back()noexcept;
// [o] constexpr void clear()noexcept;
// [o] constexpr bool get_element(size_t index,_Type& value)const noexcept;
// [o] constexpr bool set_element(size_t index,_Type const& value)noexcept;
// [o] constexpr _Type& operator[](size_t index)noexcept;
// [o] constexpr _Type const& operator[](size_t index)const noexcept;
// [o] constexpr size_t capacity()const noexcept;
// [o] constexpr void reserve_capacity(size_t capacity)noexcept;
// [o] constexpr void shrink_to_fit()noexcept;
// [o] constexpr size_t default_capacity()const noexcept;
// [o] constexpr size_t size()const noexcept;
// [o] constexpr size_t max_size()const noexcept;
// [o] constexpr bool empty()const noexcept;
// [o] constexpr void resize(size_t size,_Type const& value={})noexcept;
// [o] constexpr void swap(Array<_Type>& array)noexcept;
// [o] constexpr bool operator==(Array<_Type> const& array)const noexcept;
// [o] constexpr bool operator!=(Array<_Type> const& array)const noexcept;
// [o] constexpr Array<_Type>& operator+=(Array<_Type> const& array)noexcept;
// [o] constexpr Array<_Type> operator+(Array<_Type> const& array)const noexcept;
// [o] constexpr Array<_Type> sub_array(size_t index,size_t count)const noexcept;
// [x] constexpr iterator begin()noexcept;
// [x] constexpr iterator end()noexcept;
// [x] constexpr const_iterator begin()const noexcept;
// [x] constexpr const_iterator end()const noexcept;
// [x] constexpr const_iterator cbegin()const noexcept;
// [x] constexpr const_iterator cend()const noexcept;
// [x] constexpr reverse_iterator rbegin()noexcept;
// [x] constexpr reverse_iterator rend()noexcept;
// [x] constexpr const_reverse_iterator rbegin()const noexcept;
// [x] constexpr const_reverse_iterator rend()const noexcept;
// [x] constexpr const_reverse_iterator crbegin()const noexcept;
// [x] constexpr const_reverse_iterator crend()const noexcept;
// [x] template<typename _Func>
//     constexpr auto map(_Func&& func)const noexcept
//         ->Array<std::remove_cvref_t<decltype(std::forward<_Func>(func)(_Type{}))>>;
// [x] template<typename _Func>
//     constexpr _Type reduce(_Func&& func)const noexcept;
// [x] template<typename _Func,typename _Ret=_Type>
//     constexpr _Ret reduce(_Func&& func,_Ret&& init)const noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type> filter(_Func&& func)const noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_iterator(_Func&& func)noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_iterator(_Func&& func)const noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_reverse_iterator(_Func&& func)noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_reverse_iterator(_Func&& func)const noexcept;

// [o] constexpr Array()noexcept;
TEST_UNIT(test_array_default_ctor){
    using type=double;
    Array<type> arr_1;
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()==arr_1.default_capacity());
}
// [o] constexpr Array(Array<_Type> const& array)noexcept;
TEST_UNIT(test_array_copy_ctor){
    using type=double;

    Array<type> val_1; 
    Array<type> arr_1(val_1);
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    Array<type> val_2{1,2,3,4,5,6,7,8,9,10,11};
    Array<type> arr_2(val_2);
    TEST_CASE(arr_2==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_2.size()==11);
    TEST_CASE(arr_2.capacity()>=11);
}
// [o] constexpr Array(Array<_Type>&& array)noexcept;
TEST_UNIT(test_array_move_ctor){
    using type=double;

    Array<type> arr_1(std::move(Array<type>{}));
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    Array<type> arr_2(std::move(Array<type>{1,2,3,4,5,6,7,8,9,10,11}));
    TEST_CASE(arr_2==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_2.size()==11);
    TEST_CASE(arr_2.capacity()>=11);
}
// [o] template<size_t _size>
//     constexpr Array(_Type const(&array)[_size])noexcept;
TEST_UNIT(test_array_ctor_by_c_array){
    using type=double;

    type arr[]={1,2,3,4,5,6,7,8,9,10,11};
    Array<type> arr_1(arr);
    TEST_CASE(arr_1==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_1.size()==11);
    TEST_CASE(arr_1.capacity()>=11);
}
// [o] constexpr Array(::std::initializer_list<_Type> const& list)noexcept;
TEST_UNIT(test_array_ctor_by_cxx_initialize_list){
    using type=double;

    std::initializer_list<type> arr{1,2,3,4,5,6,7,8,9,10,11};
    Array<type> arr_1(arr);
    TEST_CASE(arr_1==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_1.size()==11);
    TEST_CASE(arr_1.capacity()>=11);
}
// [o] constexpr Array(size_t count,_Type const& value={})noexcept;
TEST_UNIT(test_array_ctor_by_n_value){
    using type=double;

    Array<type> arr_1(0,7);
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    Array<type> arr_2(11,7);
    TEST_CASE(arr_2==Array<type>{7/*1*/,7/*2*/,7/*3*/,7/*4*/,7/*5*/,7/*6*/,7/*7*/,7/*8*/,7/*9*/,7/*10*/,7/*11*/});
    TEST_CASE(arr_2.size()==11);
    TEST_CASE(arr_2.capacity()>=11);
}
// [o] constexpr ~Array()noexcept;
TEST_UNIT(test_array_dtor){
    using type=double;

    Array<type> arr_1(0,7);
    arr_1.~Array();
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()==0);

    Array<type> arr_2(11,7);
    arr_1.~Array();
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()==0);
}
// [o] constexpr Array<_Type>& operator=(Array<_Type> const& array)noexcept;
TEST_UNIT(test_array_operator_assign_by_copy){
    using type=double;

    Array<type> val_1; 
    Array<type> arr_1;
    arr_1=val_1;
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    Array<type> val_2{1,2,3,4,5,6,7,8,9,10,11};
    Array<type> arr_2;
    arr_2=val_2;
    TEST_CASE(arr_2==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_2.size()==11);
    TEST_CASE(arr_2.capacity()>=11);
}
// [o] constexpr Array<_Type>& operator=(Array<_Type>&& array)noexcept;
TEST_UNIT(test_array_operator_assign_by_move){
    using type=double;

    Array<type> arr_1;
    arr_1=std::move(Array<type>{});
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    Array<type> arr_2;
    arr_2=std::move(Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_2==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_2.size()==11);
    TEST_CASE(arr_2.capacity()>=11);
}
// [o] template<size_t _size>
//     constexpr Array<_Type>& operator=(_Type const(&array)[_size])noexcept;
TEST_UNIT(test_array_operator_assign_by_c_array){
    using type=double;

    type arr[]={1,2,3,4,5,6,7,8,9,10,11};
    Array<type> arr_1;
    arr_1=arr;
    TEST_CASE(arr_1==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_1.size()==11);
    TEST_CASE(arr_1.capacity()>=11);
}
// [o] constexpr Array<_Type>& operator=(::std::initializer_list<_Type> const& list)noexcept;
TEST_UNIT(test_array_operator_assign_by_cxx_initialize_list){
    using type=double;

    std::initializer_list<type> arr{1,2,3,4,5,6,7,8,9,10,11};
    Array<type> arr_1;
    arr_1=arr;
    TEST_CASE(arr_1==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr_1.size()==11);
    TEST_CASE(arr_1.capacity()>=11);
}
// [o] constexpr bool insert(size_t index,_Type const& value)noexcept;
TEST_UNIT(test_array_insert_1_element){
    using type=double;

    Array<type> arr;
    arr.insert(0,1);
    TEST_CASE(arr==Array<type>{1});
    TEST_CASE(arr.size()==1);
    TEST_CASE(arr.capacity()>=1);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(10,11);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(0,-1);
    TEST_CASE(arr==Array<type>{-1,1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,6,7,8,9,10,11};
    arr.insert(4,5);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(100,-1);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);
}
// [o] constexpr bool insert(size_t index,_Type const& value,size_t count)noexcept;
TEST_UNIT(test_array_insert_n_element){
    using type=double;

    Array<type> arr;
    arr.insert(0,7,11);
    TEST_CASE(arr==Array<type>(11,7));
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(10,0,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10,0,0,0});
    TEST_CASE(arr.size()==13);
    TEST_CASE(arr.capacity()>=13);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(0,-1,3);
    TEST_CASE(arr==Array<type>{-1,-1,-1,1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==13);
    TEST_CASE(arr.capacity()>=13);

    arr={1,2,3,4,6,7,8,9,10,11};
    arr.insert(4,5,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,5,5,6,7,8,9,10,11});
    TEST_CASE(arr.size()==13);
    TEST_CASE(arr.capacity()>=13);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(100,-1,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(0,-1,0);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);
}
// [o] constexpr bool insert(size_t index,Array<_Type> const& array)noexcept;
TEST_UNIT(test_array_insert_array){
    using type=double;

    Array<type> arr;
    arr.insert(0,Array<type>(11,7));
    TEST_CASE(arr==Array<type>(11,7));
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(10,Array<type>(3,0));
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10,0,0,0});
    TEST_CASE(arr.size()==13);
    TEST_CASE(arr.capacity()>=13);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(0,Array<type>(3,-1));
    TEST_CASE(arr==Array<type>{-1,-1,-1,1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==13);
    TEST_CASE(arr.capacity()>=13);

    arr={1,2,3,4,6,7,8,9,10,11};
    arr.insert(4,Array<type>(3,5));
    TEST_CASE(arr==Array<type>{1,2,3,4,5,5,5,6,7,8,9,10,11});
    TEST_CASE(arr.size()==13);
    TEST_CASE(arr.capacity()>=13);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(100,Array<type>(3,-1));
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.insert(0,Array<type>(0,-1));
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={};
    arr.insert(0,arr);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={1,2,3,4,5};
    arr.insert(0,arr);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,1,2,3,4,5});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5};
    arr.insert(5,arr);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,1,2,3,4,5});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5};
    arr.insert(2,arr);
    TEST_CASE(arr==Array<type>{1,2,1,2,3,4,5,3,4,5});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5};
    arr.insert(100,arr);
    TEST_CASE(arr==Array<type>{1,2,3,4,5});
    TEST_CASE(arr.size()==5);
    TEST_CASE(arr.capacity()>=5);
}
// [o] constexpr void push_back(_Type const& value)noexcept;
TEST_UNIT(test_array_push_back){
    using type=double;

    Array<type> arr;
    arr.push_back(1);
    TEST_CASE(arr==Array<type>{1});
    TEST_CASE(arr.size()==1);
    TEST_CASE(arr.capacity()>=1);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.push_back(11);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10,11});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);
}
// [o] constexpr bool erase(size_t index)noexcept;
TEST_UNIT(test_array_erase_1_element){
    using type=double;

    Array<type> arr;
    arr.erase(0);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    arr.erase(0);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10,0};
    arr.erase(10);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,0,5,6,7,8,9,10};
    arr.erase(4);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.erase(100);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);
}
// [o] constexpr bool erase(size_t index,size_t count)noexcept;
TEST_UNIT(test_array_erase_n_element){
    using type=double;

    Array<type> arr;
    arr.erase(0,3);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={0,0,0,1,2,3,4,5,6,7,8,9,10};
    arr.erase(0,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10,0,0,0};
    arr.erase(10,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,0,0,0,5,6,7,8,9,10};
    arr.erase(4,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.erase(100,3);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.erase(4,100);
    TEST_CASE(arr==Array<type>{1,2,3,4});
    TEST_CASE(arr.size()==4);
    TEST_CASE(arr.capacity()>=4);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.erase(0,100);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={};
    arr.erase(0,100);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);
}
// [o] constexpr void pop_back()noexcept;
TEST_UNIT(test_array_pop_back){
    using type=double;

    Array<type> arr;
    arr.pop_back();
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={1,2,3,4,5,6,7,8,9,10,0};
    arr.pop_back();
    TEST_CASE(arr==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(arr.size()==10);
    TEST_CASE(arr.capacity()>=10);
}
// [o] constexpr void clear()noexcept;
TEST_UNIT(test_array_clear){
    using type=double;

    Array<type> arr;
    arr.clear();
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={1,2,3,4,5,6,7,8,9,10,11};
    arr.clear();
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);
}
// [o] constexpr bool get_element(size_t index,_Type& value)const noexcept;
TEST_UNIT(test_array_get_element){
    using type=double;

    Array<type> arr;
    type element;
    TEST_CASE(arr.get_element(0,element)==false);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    for(size_t index=0;index<11;++index){
        TEST_CASE(arr.get_element(index,element));
        TEST_CASE(element==index);
    }

    TEST_CASE(arr.get_element(100,element)==false);
}
// [o] constexpr bool set_element(size_t index,_Type const& value)noexcept;
TEST_UNIT(test_array_set_element){
    using type=double;

    Array<type> arr;
    TEST_CASE(arr.set_element(0,-1));
    TEST_CASE(arr==Array<type>{-1});
    TEST_CASE(arr.size()==1);
    TEST_CASE(arr.capacity()>=1);

    arr={1,2,3,4,5,6,7,8,9,10};
    for(size_t index=0;index<15;++index){
        TEST_CASE(arr.set_element(index,-1));
    }
    TEST_CASE(arr==Array<type>(15,-1));
    TEST_CASE(arr.size()==15);
    TEST_CASE(arr.capacity()>=15);

    TEST_CASE(arr.set_element(100,-1)==false);
}
// [o] constexpr _Type& operator[](size_t index)noexcept;
TEST_UNIT(test_array_operator_at){
    using type=double;

    Array<type> arr;
    arr[0]=-1;
    TEST_CASE(arr==Array<type>{-1});
    TEST_CASE(arr.size()==1);
    TEST_CASE(arr.capacity()>=1);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    for(size_t index=0;index<15;++index){
        arr[index]=-1;
    }
    TEST_CASE(arr==Array<type>(15,-1));
    TEST_CASE(arr.size()==15);
    TEST_CASE(arr.capacity()>=15);
}
// [o] constexpr _Type const& operator[](size_t index)const noexcept;
TEST_UNIT(test_array_operator_at_const){
    using type=double;

    Array<type> const arr={0,1,2,3,4,5,6,7,8,9,10};
    for(size_t index=0;index<11;++index){
        TEST_CASE(arr[index]==index);
    }
}
// [o] constexpr size_t capacity()const noexcept;
TEST_UNIT(test_array_capacity){
    using type=double;

    Array<type> arr;
    TEST_CASE(arr.capacity()==arr.default_capacity());

    size_t capacity=arr.default_capacity()*2;
    arr.reserve_capacity(capacity);
    TEST_CASE(arr.capacity()==capacity);

    arr.shrink_to_fit();
    TEST_CASE(arr.capacity()==0);
}
// [o] constexpr void reserve_capacity(size_t capacity)noexcept;
TEST_UNIT(test_array_reserve_capacity){
    using type=double;

    Array<type> arr;
    size_t capacity=arr.default_capacity()*2;
    arr.reserve_capacity(capacity);
    TEST_CASE(arr.capacity()==capacity);

    arr.reserve_capacity(0);
    TEST_CASE(arr.capacity()==capacity);
}
// [o] constexpr void shrink_to_fit()noexcept;
TEST_UNIT(test_array_shrink_to_fit){
    using type=double;

    Array<type> arr={1,2,3,4,5};
    arr.shrink_to_fit();
    TEST_CASE(arr.capacity()==5);

    arr={};
    arr.shrink_to_fit();
    TEST_CASE(arr.capacity()==0);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.shrink_to_fit();
    TEST_CASE(arr.capacity()==10);
}
// [o] constexpr size_t default_capacity()const noexcept;
TEST_UNIT(test_array_default_capcaity){
    using type=double;

    Array<type> arr;
    TEST_CASE(arr.default_capacity()==arr.capacity());
}
// [o] constexpr size_t size()const noexcept;
TEST_UNIT(test_array_size){
    using type=double;

    Array<type> arr={1,2,3,4,5};
    TEST_CASE(arr.size()==5);

    arr={};
    TEST_CASE(arr.size()==0);
}
// [o] constexpr size_t max_size()const noexcept;
TEST_UNIT(test_array_max_size){
    using type=double;

    Array<type> arr;
    TEST_CASE(arr.max_size()==static_cast<decltype(arr.size())>(-1));
}
// [o] constexpr bool empty()const noexcept;
TEST_UNIT(test_array_empty){
    using type=double;

    Array<type> arr={1,2,3,4,5};
    TEST_CASE(arr.empty()==false);

    arr={};
    TEST_CASE(arr.empty()==true);
}
// [o] constexpr void resize(size_t size,_Type const& value={})noexcept;
TEST_UNIT(test_array_resize){
    using type=double;

    Array<type> arr={1,2,3,4,5};
    arr.resize(11,-1);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,-1,-1,-1,-1,-1,-1});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5};
    arr.resize(11);
    TEST_CASE(arr==Array<type>{1,2,3,4,5,0,0,0,0,0,0});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.resize(5,-1);
    TEST_CASE(arr==Array<type>{1,2,3,4,5});
    TEST_CASE(arr.size()==5);
    TEST_CASE(arr.capacity()>=5);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.resize(5);
    TEST_CASE(arr==Array<type>{1,2,3,4,5});
    TEST_CASE(arr.size()==5);
    TEST_CASE(arr.capacity()>=5);

    arr={};
    arr.resize(11,-1);
    TEST_CASE(arr==Array<type>{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={};
    arr.resize(11);
    TEST_CASE(arr==Array<type>{0,0,0,0,0,0,0,0,0,0,0});
    TEST_CASE(arr.size()==11);
    TEST_CASE(arr.capacity()>=11);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.resize(0,-1);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);

    arr={1,2,3,4,5,6,7,8,9,10};
    arr.resize(0);
    TEST_CASE(arr==Array<type>{});
    TEST_CASE(arr.size()==0);
    TEST_CASE(arr.capacity()>=0);
}
// [o] constexpr void swap(Array<_Type>& array)noexcept;
TEST_UNIT(test_array_swap){
    using type=double;

    Array<type> arr_0={};
    Array<type> arr_1={1,2,3,4,5};
    arr_0.swap(arr_1);
    TEST_CASE(arr_0==Array<type>{1,2,3,4,5});
    TEST_CASE(arr_0.size()==5);
    TEST_CASE(arr_0.capacity()>=5);
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    arr_0={1,2,3,4,5};
    arr_1={};
    arr_0.swap(arr_1);
    TEST_CASE(arr_0==Array<type>{});
    TEST_CASE(arr_0.size()==0);
    TEST_CASE(arr_0.capacity()>=0);
    TEST_CASE(arr_1==Array<type>{1,2,3,4,5});
    TEST_CASE(arr_1.size()==5);
    TEST_CASE(arr_1.capacity()>=5);

    arr_0={1,2,3,4,5};
    arr_1={6,7};
    arr_0.swap(arr_1);
    TEST_CASE(arr_0==Array<type>{6,7});
    TEST_CASE(arr_0.size()==2);
    TEST_CASE(arr_0.capacity()>=2);
    TEST_CASE(arr_1==Array<type>{1,2,3,4,5});
    TEST_CASE(arr_1.size()==5);
    TEST_CASE(arr_1.capacity()>=5);

    arr_0={};
    arr_1={};
    arr_0.swap(arr_1);
    TEST_CASE(arr_0==Array<type>{});
    TEST_CASE(arr_0.size()==0);
    TEST_CASE(arr_0.capacity()>=0);
    TEST_CASE(arr_1==Array<type>{});
    TEST_CASE(arr_1.size()==0);
    TEST_CASE(arr_1.capacity()>=0);

    arr_0={};
    arr_0.swap(arr_0);
    TEST_CASE(arr_0==Array<type>{});
    TEST_CASE(arr_0.size()==0);

    arr_0={1,2,3,4,5};
    arr_0.swap(arr_0);
    TEST_CASE(arr_0==Array<type>{1,2,3,4,5});
    TEST_CASE(arr_0.size()==5);
    TEST_CASE(arr_0.capacity()>=5);
}
// [o] constexpr bool operator==(Array<_Type> const& array)const noexcept;
TEST_UNIT(test_array_operator_eq){
    using type=double;

    Array<type> arr_0={};
    Array<type> arr_1={1,2,3,4,5};
    TEST_CASE(!(arr_0==arr_1));

    arr_0={1,2,3,4,5};
    arr_1={1,2,3,4,5};
    TEST_CASE(arr_0==arr_1);

    arr_0={};
    arr_1={};
    TEST_CASE(arr_0==arr_1);
}
// [o] constexpr bool operator!=(Array<_Type> const& array)const noexcept;
TEST_UNIT(test_array_operator_not_eq){
    using type=double;

    Array<type> arr_0={};
    Array<type> arr_1={1,2,3,4,5};
    TEST_CASE(arr_0!=arr_1);

    arr_0={1,2,3,4,5};
    arr_1={1,2,3,4,5};
    TEST_CASE(!(arr_0!=arr_1));

    arr_0={};
    arr_1={};
    TEST_CASE(!(arr_0!=arr_1));
}
// [o] constexpr Array<_Type>& operator+=(Array<_Type> const& array)noexcept;
TEST_UNIT(test_array_operator_append){
    using type=double;

    Array<type> arr_0={};
    arr_0+={1,2,3,4,5};
    TEST_CASE(arr_0==Array<type>{1,2,3,4,5});
    TEST_CASE(arr_0.size()==5);
    TEST_CASE(arr_0.capacity()>=5);

    arr_0={};
    arr_0+={};
    TEST_CASE(arr_0==Array<type>{});
    TEST_CASE(arr_0.size()==0);
    TEST_CASE(arr_0.capacity()>=0);

    arr_0={1,2,3,4,5};
    arr_0+={};
    TEST_CASE(arr_0==Array<type>{1,2,3,4,5});
    TEST_CASE(arr_0.size()==5);
    TEST_CASE(arr_0.capacity()>=5);

    arr_0={1,2,3,4,5};
    arr_0+={6,7};
    TEST_CASE(arr_0==Array<type>{1,2,3,4,5,6,7});
    TEST_CASE(arr_0.size()==7);
    TEST_CASE(arr_0.capacity()>=7);
}
// [o] constexpr Array<_Type> operator+(Array<_Type> const& array)const noexcept;
TEST_UNIT(test_array_operator_plus){
    using type=double;

    Array<type> ret;
    Array<type> arr_0={};
    ret=arr_0+Array<type>{1,2,3,4,5};
    TEST_CASE(ret==Array<type>{1,2,3,4,5});
    TEST_CASE(ret.size()==5);
    TEST_CASE(ret.capacity()>=5);

    arr_0={};
    ret=arr_0+Array<type>{};
    TEST_CASE(ret==Array<type>{});
    TEST_CASE(ret.size()==0);
    TEST_CASE(ret.capacity()>=0);

    arr_0={1,2,3,4,5};
    ret=arr_0+Array<type>{};
    TEST_CASE(ret==Array<type>{1,2,3,4,5});
    TEST_CASE(ret.size()==5);
    TEST_CASE(ret.capacity()>=5);

    arr_0={1,2,3,4,5};
    ret=arr_0+Array<type>{6,7};
    TEST_CASE(ret==Array<type>{1,2,3,4,5,6,7});
    TEST_CASE(ret.size()==7);
    TEST_CASE(ret.capacity()>=7);
}
// [o] constexpr Array<_Type> sub_array(size_t index,size_t count)const noexcept;
TEST_UNIT(test_array_sub_array){
    using type=double;

    Array<type> ret;
    Array<type> arr={0,1,2,3,4,5,6,7,8,9,10};
    ret=arr.sub_array(1,6);
    TEST_CASE(ret==Array<type>{1,2,3,4,5,6});
    TEST_CASE(ret.size()==6);
    TEST_CASE(ret.capacity()>=6);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    ret=arr.sub_array(1,0);
    TEST_CASE(ret==Array<type>{});
    TEST_CASE(ret.size()==0);
    TEST_CASE(ret.capacity()>=0);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    ret=arr.sub_array(1,100);
    TEST_CASE(ret==Array<type>{1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(ret.size()==10);
    TEST_CASE(ret.capacity()>=10);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    ret=arr.sub_array(0,100);
    TEST_CASE(ret==Array<type>{0,1,2,3,4,5,6,7,8,9,10});
    TEST_CASE(ret.size()==11);
    TEST_CASE(ret.capacity()>=11);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    ret=arr.sub_array(100,100);
    TEST_CASE(ret==Array<type>{});
    TEST_CASE(ret.size()==0);
    TEST_CASE(ret.capacity()>=0);

    arr={0,1,2,3,4,5,6,7,8,9,10};
    ret=arr.sub_array(100,0);
    TEST_CASE(ret==Array<type>{});
    TEST_CASE(ret.size()==0);
    TEST_CASE(ret.capacity()>=0);

    arr={};
    ret=arr.sub_array(0,0);
    TEST_CASE(ret==Array<type>{});
    TEST_CASE(ret.size()==0);
    TEST_CASE(ret.capacity()>=0);
}
// [x] constexpr iterator begin()noexcept;
// [x] constexpr iterator end()noexcept;
// [x] constexpr const_iterator begin()const noexcept;
// [x] constexpr const_iterator end()const noexcept;
// [x] constexpr const_iterator cbegin()const noexcept;
// [x] constexpr const_iterator cend()const noexcept;
// [x] constexpr reverse_iterator rbegin()noexcept;
// [x] constexpr reverse_iterator rend()noexcept;
// [x] constexpr const_reverse_iterator rbegin()const noexcept;
// [x] constexpr const_reverse_iterator rend()const noexcept;
// [x] constexpr const_reverse_iterator crbegin()const noexcept;
// [x] constexpr const_reverse_iterator crend()const noexcept;
// [x] template<typename _Func>
//     constexpr auto map(_Func&& func)const noexcept
//         ->Array<std::remove_cvref_t<decltype(std::forward<_Func>(func)(_Type{}))>>;
// [x] template<typename _Func>
//     constexpr _Type reduce(_Func&& func)const noexcept;
// [x] template<typename _Func,typename _Ret=_Type>
//     constexpr _Ret reduce(_Func&& func,_Ret&& init)const noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type> filter(_Func&& func)const noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_iterator(_Func&& func)noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_iterator(_Func&& func)const noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_reverse_iterator(_Func&& func)noexcept;
// [x] template<typename _Func>
//     constexpr Array<_Type>& foreach_reverse_iterator(_Func&& func)const noexcept;
#endif//__TEST_ARRAY_HPP__