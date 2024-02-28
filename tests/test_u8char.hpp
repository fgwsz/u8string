#ifndef __TEST_U8CHAR_HPP__
#define __TEST_U8CHAR_HPP__
#include"u8char.h"
#include"test.hpp"
// TEST API:
// [o] constexpr U8Char()noexcept;
// [o] constexpr U8Char(U8Char const& rhs)noexcept;
// [o] constexpr U8Char& operator=(U8Char const& rhs)noexcept;
// [o] constexpr U8Char(char ch)noexcept;
// [o] constexpr U8Char& operator=(char ch)noexcept;
// [o] constexpr U8Char(char const* c_str)noexcept;
// [o] constexpr U8Char& operator=(char const* c_str)noexcept;
// [o] constexpr size_t byte_count()const noexcept;
// [o] constexpr byte_t operator[](size_t index)const noexcept;
// [o] constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept;
// [o] constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept;
// [o] constexpr bool operator< (U8Char const& lhs,U8Char const& rhs)noexcept;
// [o] constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept;
// [o] constexpr bool operator> (U8Char const& lhs,U8Char const& rhs)noexcept;
// [o] constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept;

// [o] constexpr U8Char()noexcept;
TEST_UNIT(test_u8char_default_ctor){
    U8Char ch;
    TEST_CASE(ch=='\0');
    TEST_CASE(ch.byte_count()==1);
}
// [o] constexpr U8Char(U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_copy_ctor){
    U8Char ch_1;
    U8Char ch_2(ch_1);
    TEST_CASE(ch_2=='\0');
    TEST_CASE(ch_2.byte_count()==1);

    U8Char ch_3("你");
    U8Char ch_4(ch_3);
    TEST_CASE(ch_4=="你");
    TEST_CASE(ch_4.byte_count()==3);
}
// [o] constexpr U8Char& operator=(U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_assign){
    U8Char ch_1;
    U8Char ch_2;
    ch_2=ch_1;
    TEST_CASE(ch_2=='\0');
    TEST_CASE(ch_2.byte_count()==1);

    U8Char ch_3("你");
    U8Char ch_4;
    ch_4=ch_3;
    TEST_CASE(ch_4=="你");
    TEST_CASE(ch_4.byte_count()==3);
}
// [o] constexpr U8Char(char ch)noexcept;
TEST_UNIT(test_u8char_ctor_by_char){
    U8Char ch('A');
    TEST_CASE(ch=='A');
    TEST_CASE(ch.byte_count()==1);
}
// [o] constexpr U8Char& operator=(char ch)noexcept;
TEST_UNIT(test_u8char_operator_assign_by_char){
    U8Char ch;
    ch='A';
    TEST_CASE(ch=='A');
    TEST_CASE(ch.byte_count()==1);
}
// [o] constexpr U8Char(char const* c_str)noexcept;
TEST_UNIT(test_u8char_ctor_by_c_str){
    U8Char ch_1("");
    TEST_CASE(ch_1=="");
    TEST_CASE(ch_1.byte_count()==1);

    U8Char ch_2("你");
    TEST_CASE(ch_2=="你");
    TEST_CASE(ch_2.byte_count()==3);

    U8Char ch_3(static_cast<char const*>(nullptr));
    TEST_CASE(ch_3=="");
    TEST_CASE(ch_3.byte_count()==1);
}
// [o] constexpr U8Char& operator=(char const* c_str)noexcept;
TEST_UNIT(test_u8char_operator_assign_by_c_str){
    U8Char ch_1;
    ch_1="";
    TEST_CASE(ch_1=="");
    TEST_CASE(ch_1.byte_count()==1);

    U8Char ch_2;
    ch_2="你";
    TEST_CASE(ch_2=="你");
    TEST_CASE(ch_2.byte_count()==3);

    U8Char ch_3;
    ch_3=static_cast<char const*>(nullptr);
    TEST_CASE(ch_3=="");
    TEST_CASE(ch_3.byte_count()==1);
}
// [o] constexpr size_t byte_count()const noexcept;
TEST_UNIT(test_u8char_byte_count){
    U8Char ch_1("");
    TEST_CASE(ch_1.byte_count()==1);

    U8Char ch_2("你");
    TEST_CASE(ch_2.byte_count()==3);
}
// [o] constexpr byte_t operator[](size_t index)const noexcept;
TEST_UNIT(test_u8char_operator_at){
    char const c_arr_1[]="";
    U8Char ch_1(c_arr_1);
    TEST_CASE(ch_1.byte_count()==1);
    for(U8Char::size_t index=0;index<ch_1.byte_count();++index){
        TEST_CASE(ch_1[index]==static_cast<U8Char::byte_t>(c_arr_1[index]));
    }

    char const c_arr_2[]="你";
    U8Char ch_2(c_arr_2);
    for(U8Char::size_t index=0;index<ch_2.byte_count();++index){
        TEST_CASE(ch_2[index]==static_cast<U8Char::byte_t>(c_arr_2[index]));
    }
}
// [o] constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_eq){
    U8Char ch_1;
    ch_1="";
    TEST_CASE(ch_1=="");

    U8Char ch_2;
    ch_2="你";
    TEST_CASE(ch_2=="你");
}
// [o] constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_not_eq){
    U8Char ch_1;
    ch_1="";
    TEST_CASE(!(ch_1!=""));

    U8Char ch_2;
    ch_2="你";
    TEST_CASE(!(ch_2!="你"));
}
// [o] constexpr bool operator< (U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_less){
    U8Char ch_1;
    ch_1='A';
    TEST_CASE(ch_1<'B');
    TEST_CASE(ch_1<"你");
}
// [o] constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_less_than){
    U8Char ch_1;
    ch_1='A';
    TEST_CASE(ch_1<='A');
    TEST_CASE(ch_1<='B');
    TEST_CASE(ch_1<="你");
}
// [o] constexpr bool operator> (U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_greater){
    U8Char ch_1;
    ch_1='B';
    TEST_CASE(ch_1>'A');
    TEST_CASE("你">ch_1);
}
// [o] constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_greater_than){
    U8Char ch_1;
    ch_1='B';
    TEST_CASE(ch_1>='A');
    TEST_CASE(ch_1>='B');
    TEST_CASE("你">=ch_1);
}
#endif//__TEST_U8CHAR_HPP__
