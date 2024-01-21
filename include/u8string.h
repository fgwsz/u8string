#ifndef __U8STRING_H__
#define __U8STRING_H__
#include"u8char.h"
#include"array.hpp"
class U8String{
public:
    U8String();
    
    U8String(U8String const& rhs);
    U8String& operator=(U8String const& rhs);

    U8String(char ch);
    U8String& operator=(char ch);

    U8String(char const* c_str);
    U8String& operator=(char const* c_str);

    U8String(U8Char ch);
    U8String& operator=(U8Char ch);

    using size_t=uintmax_t;
    
    size_t length()const;
    bool empty()const;
    U8Char operator[](size_t index)const;
private:
    _Array<U8Char> data_;
};
bool operator==(U8String const& lhs,U8String const& rhs);
bool operator!=(U8String const& lhs,U8String const& rhs);
bool operator< (U8String const& lhs,U8String const& rhs);
bool operator<=(U8String const& lhs,U8String const& rhs);
bool operator> (U8String const& lhs,U8String const& rhs);
bool operator>=(U8String const& lhs,U8String const& rhs);
#endif//__U8STRING_H__