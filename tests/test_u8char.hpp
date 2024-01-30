#ifndef __TEST_U8CHAR_HPP__
#define __TEST_U8CHAR_HPP__
#include"u8char.h"
#include"test.hpp"
// TEST API:
// [x] constexpr U8Char()noexcept;
// [x] constexpr U8Char(U8Char const& rhs)noexcept;
// [x] constexpr U8Char& operator=(U8Char const& rhs)noexcept;
// [x] constexpr U8Char(char ch)noexcept;
// [x] constexpr U8Char& operator=(char ch)noexcept;
// [x] constexpr U8Char(char const* c_str)noexcept;
// [x] constexpr U8Char& operator=(char const* c_str)noexcept;
// [x] constexpr size_t byte_count()const noexcept;
// [x] constexpr byte_t operator[](size_t index)const noexcept;
// [x] constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept;
// [x] constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept;
// [x] constexpr bool operator< (U8Char const& lhs,U8Char const& rhs)noexcept;
// [x] constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept;
// [x] constexpr bool operator> (U8Char const& lhs,U8Char const& rhs)noexcept;
// [x] constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept;

// [x] constexpr U8Char()noexcept;
TEST_UNIT(test_u8char_default_ctor){

}
// [x] constexpr U8Char(U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_copy_ctor){

}
// [x] constexpr U8Char& operator=(U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_assign){

}
// [x] constexpr U8Char(char ch)noexcept;
TEST_UNIT(test_u8char_ctor_by_char){

}
// [x] constexpr U8Char& operator=(char ch)noexcept;
TEST_UNIT(test_u8char_operator_assign_by_char){

}
// [x] constexpr U8Char(char const* c_str)noexcept;
TEST_UNIT(test_u8char_ctor_by_c_str){

}
// [x] constexpr U8Char& operator=(char const* c_str)noexcept;
TEST_UNIT(test_u8char_operator_assign_by_c_str){

}
// [x] constexpr size_t byte_count()const noexcept;
TEST_UNIT(test_u8char_byte_count){

}
// [x] constexpr byte_t operator[](size_t index)const noexcept;
TEST_UNIT(test_u8char_operator_at){

}
// [x] constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_eq){

}
// [x] constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_not_eq){

}
// [x] constexpr bool operator< (U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_less){

}
// [x] constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_less_than){

}
// [x] constexpr bool operator> (U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_greater){

}
// [x] constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept;
TEST_UNIT(test_u8char_operator_greater_than){

}
#endif//__TEST_U8CHAR_HPP__