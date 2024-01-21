#ifndef __U8CHAR_H__
#define __U8CHAR_H__
extern "C"{
    #include<stdint.h> // uint8_t,uint32_t
}
class U8Char{
public:
    // 初始化*this值为'\0'
    constexpr U8Char()noexcept;

    constexpr U8Char(U8Char const& rhs)noexcept;
    constexpr U8Char& operator=(U8Char const& rhs)noexcept;

    // 构造失败时*this值置为'\0'
    constexpr U8Char(char ch)noexcept;
    // 赋值失败不改变原来的值
    constexpr U8Char& operator=(char ch)noexcept;

    // 构造失败时*this值置为'\0'
    constexpr U8Char(char const* c_str)noexcept;
    // 赋值失败不改变原来*this的值
    constexpr U8Char& operator=(char const* c_str)noexcept;

    using size_t=uint8_t;
    using byte_t=uint8_t;

    // 返回当前utf8编码字符*this所占用的字节数
    constexpr size_t byte_count()const noexcept;
    // 得到*this中下标为index的字节，不对index取值进行越界检查
    // index取值范围为[0,byte_count())
    constexpr byte_t operator[](size_t index)const noexcept;

    friend constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept;
private:
    union Data{
        byte_t byte_array_[4];
        uint32_t code_point_;
    } data_;
};
constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator< (U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator> (U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept;
#endif//__U8CHAR_H__