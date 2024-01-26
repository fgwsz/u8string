#ifndef __TEST_ARRAY_HPP__
#define __TEST_ARRAY_HPP__
#include"array.hpp"
#include"test.hpp"
// TEST API:
// [o] constexpr Array()noexcept;
// [o] constexpr Array(Array<_Type> const& array)noexcept;
// [x] constexpr Array(Array<_Type>&& array)noexcept;
// [o] template<size_t _size>
//     constexpr Array(_Type const(&array)[_size])noexcept;
// [o] constexpr Array(::std::initializer_list<_Type> const& list)noexcept;
// [o] constexpr Array(size_t count,_Type const& value={})noexcept;
// [o] constexpr ~Array()noexcept;
// [x] constexpr Array<_Type>& operator=(Array<_Type> const& array)noexcept;
// [x] constexpr Array<_Type>& operator=(Array<_Type>&& array)noexcept;
// [x] template<size_t _size>
//     constexpr Array<_Type>& operator=(_Type const(&array)[_size])noexcept;
// [x] constexpr Array<_Type>& operator=(::std::initializer_list<_Type> const& list)noexcept;
// [x] constexpr bool insert(size_t index,_Type const& value)noexcept;
// [x] constexpr bool insert(size_t index,_Type const& value,size_t count)noexcept;
// [x] constexpr bool insert(size_t index,Array<_Type> const& array)noexcept;
// [x] constexpr void push_back(_Type const& value)noexcept;
// [x] constexpr bool erase(size_t index)noexcept;
// [x] constexpr bool erase(size_t index,size_t count)noexcept;
// [x] constexpr void pop_back()noexcept;
// [x] constexpr void clear()noexcept;
// [x] constexpr bool get_element(size_t index,_Type& value)const noexcept;
// [x] constexpr bool set_element(size_t index,_Type const& value)noexcept;
// [x] constexpr _Type& operator[](size_t index)noexcept;
// [x] constexpr _Type const& operator[](size_t index)const noexcept;
// [x] constexpr size_t capacity()const noexcept;
// [x] constexpr void reserve_capacity(size_t capacity)noexcept;
// [x] constexpr void shrink_to_fit()noexcept;
// [x] constexpr size_t default_capacity()const noexcept;
// [x] constexpr size_t size()const noexcept;
// [x] constexpr size_t max_size()const noexcept;
// [x] constexpr bool empty()const noexcept;
// [x] constexpr void resize(size_t size,_Type const& value={})noexcept;
// [x] constexpr void swap(Array<_Type>& array)noexcept;
// [x] constexpr bool operator==(Array<_Type> const& array)const noexcept;
// [x] constexpr bool operator!=(Array<_Type> const& array)const noexcept;
// [x] constexpr Array<_Type>& operator+=(Array<_Type> const& array)noexcept;
// [x] constexpr Array<_Type> operator+(Array<_Type> const& array)const noexcept;
// [x] constexpr Array<_Type> subarr(size_t index,size_t count)const noexcept;
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
#endif//__TEST_ARRAY_HPP__