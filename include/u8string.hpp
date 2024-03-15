#ifndef __U8STRING_HPP__
#define __U8STRING_HPP__
#include"u8char.hpp"
#include"array.hpp"
class U8String{
public:
    constexpr U8String()noexcept;
    constexpr U8String(char const* value)noexcept;
    constexpr U8String(U8Char const& u8char)noexcept;
    constexpr U8String(Array<U8Char> const& char_array)noexcept;
    constexpr U8String(U8String const& u8string)noexcept;

    constexpr U8String& operator=(char const* value)noexcept;
    constexpr U8String& operator=(U8Char const& u8char)noexcept;
    constexpr U8String& operator=(Array<U8Char> const& char_array)noexcept;
    constexpr U8String& operator=(U8String const& u8string)noexcept;
    constexpr U8Char& operator[](size_t index)noexcept;
    constexpr U8Char const& operator[](size_t index)const noexcept;
    constexpr U8String& operator+=(U8String const& u8string)noexcept;
    constexpr U8String operator+(U8String const& u8string)const noexcept;
    constexpr bool operator<(U8String const& u8string)const noexcept;
    constexpr bool operator>(U8String const& u8string)const noexcept;
    constexpr bool operator<=(U8String const& u8string)const noexcept;
    constexpr bool operator>=(U8String const& u8string)const noexcept;
    constexpr bool operator!=(U8String const& u8string)const noexcept;
    constexpr bool operator==(U8String const& u8string)const noexcept;

    constexpr bool insert(size_t index,U8Char const& u8char)noexcept;
    constexpr bool insert(size_t index,U8Char const& u8char,size_t count)noexcept;
    constexpr bool insert(size_t index,U8String const& u8string)noexcept;
    constexpr bool erase(size_t index)noexcept;
    constexpr bool erase(size_t index,size_t count)noexcept;
    constexpr size_t size()const noexcept;
    constexpr size_t max_size()const noexcept;
    constexpr void resize(size_t size,u8char const& place_holder={});
    constexpr U8String substring(size_t index,size_t count)const noexcept;
    constexpr void clear()noexcept;
    constexpr void swap(U8String& u8string)noexcept;
    constexpr bool empty()const noexcept;
    constexpr Array<unsigned char> to_byte_array()const noexcept;
    constexpr Array<U8Char> to_char_array()const noexcept;
private:
    Array<U8Char> data_;
}; // class U8String
template<typename OutputStream>
constexpr OutputStream& operator<<(OutputStream& os,U8String const& u8string)noexcept;
/*impl*/
#endif//__U8STRING_HPP__
