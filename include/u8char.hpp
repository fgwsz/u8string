#ifndef __U8CHAR_HPP__
#define __U8CHAR_HPP__
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
    constexpr typename U8Char::size_t byte_count()const noexcept;
    // 得到*this中下标为index的字节，不对index取值进行越界检查
    // index取值范围为[0,byte_count())
    constexpr typename U8Char::byte_t operator[](typename U8Char::size_t index)const noexcept;

    friend constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept;
    // 判断*this是否为空('\0')
    constexpr bool empty()noexcept;
private:
    union Data{
        byte_t byte_array_[4];
        uint32_t code_point_;
    } data_;
    // 通过输入utf8编码字符的首字节，得到该utf8字符的字节个数
    // 如果first_byte取值不符合utf8编码规则，则返回0
    static constexpr typename U8Char::size_t get_byte_count(typename U8Char::byte_t first_byte)noexcept;
    // 检查utf8编码多字节字符的除首字节之外的剩余单字节是否符合utf8编码规则
    // 如果符合返回true，反之返回false
    static constexpr bool check_other_byte(typename U8Char::byte_t other_byte)noexcept;
};
constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator< (U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator> (U8Char const& lhs,U8Char const& rhs)noexcept;
constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept;
template<typename OutputStream>
OutputStream& operator<<(OutputStream& os,U8Char ch)noexcept;
/*impl*/
constexpr typename U8Char::size_t U8Char::get_byte_count(typename U8Char::byte_t first_byte)noexcept{
    constexpr typename U8Char::byte_t utf8_1byte_min=0b00000000;
    constexpr typename U8Char::byte_t utf8_1byte_max=0b01111111;
    constexpr typename U8Char::byte_t utf8_2bytes_first_byte_min=0b11000000;
    constexpr typename U8Char::byte_t utf8_2bytes_first_byte_max=0b11011111;
    constexpr typename U8Char::byte_t utf8_3bytes_first_byte_min=0b11100000;
    constexpr typename U8Char::byte_t utf8_3bytes_first_byte_max=0b11101111;
    constexpr typename U8Char::byte_t utf8_4bytes_first_byte_min=0b11110000;
    constexpr typename U8Char::byte_t utf8_4bytes_first_byte_max=0b11110111;
    if(first_byte>=utf8_1byte_min&&
       first_byte<=utf8_1byte_max){
        return 1;
    }
    if(first_byte>=utf8_2bytes_first_byte_min&&
       first_byte<=utf8_2bytes_first_byte_max){
        return 2;
    }
    if(first_byte>=utf8_3bytes_first_byte_min&&
       first_byte<=utf8_3bytes_first_byte_max){
        return 3;
    }
    if(first_byte>=utf8_4bytes_first_byte_min&&
       first_byte<=utf8_4bytes_first_byte_max){
        return 4;
    }
    return 0; // first_byte非utf8编码规则下有效字节
}
constexpr bool U8Char::check_other_byte(typename U8Char::byte_t other_byte)noexcept{
    constexpr typename U8Char::byte_t utf8_bytes_other_byte_min=0b10000000;
    constexpr typename U8Char::byte_t utf8_bytes_other_byte_max=0b10111111;
    return other_byte>=utf8_bytes_other_byte_min&&
           other_byte<=utf8_bytes_other_byte_max;
}
constexpr U8Char::U8Char()noexcept{
    this->data_.code_point_=0;
}
constexpr U8Char::U8Char(U8Char const& rhs)noexcept
    :U8Char(){
    *this=rhs;
}
constexpr U8Char& U8Char::operator=(U8Char const& rhs)noexcept{
    this->data_.code_point_=rhs.data_.code_point_;
    return *this;
}
constexpr U8Char::U8Char(char ch)noexcept
    :U8Char(){
    *this=ch;
}
constexpr U8Char& U8Char::operator=(char ch)noexcept{
    U8Char::byte_t first_byte=static_cast<U8Char::byte_t>(ch);
    if(U8Char::get_byte_count(first_byte)==0){
        return *this;
    }
    this->data_.byte_array_[0]=first_byte;
    for(U8Char::size_t index=1;index<4;++index){
        this->data_.byte_array_[index]=0;
    }
    return *this;
}
constexpr U8Char::U8Char(char const* c_str)noexcept
    :U8Char(){
    *this=c_str;
}
constexpr U8Char& U8Char::operator=(char const* c_str)noexcept{
    if(!c_str){
        return *this;
    }
    typename U8Char::byte_t first_byte=static_cast<U8Char::byte_t>(c_str[0]);
    typename U8Char::size_t byte_count=U8Char::get_byte_count(first_byte);
    if(byte_count==0){ // 首字节不符合utf8编码规则
        return *this;
    }
    if(byte_count>1){ // 检查剩余字节是否符合utf8编码规则
        typename U8Char::byte_t other_byte=0;
        for(typename U8Char::size_t index=1;index<byte_count;++index){
            if(!U8Char::check_other_byte(
                static_cast<U8Char::byte_t>(c_str[index])
            )){
                return *this;
            }
        }
    }
    // 对字节数组进行字节赋值
    for(typename U8Char::size_t index=0;index<byte_count;++index){
        this->data_.byte_array_[index]=static_cast<U8Char::byte_t>(c_str[index]);
    }
    // 将字节数组未赋值的剩余元素置0
    for(typename U8Char::size_t index=byte_count;index<4;++index){
        this->data_.byte_array_[index]=0;
    }
    return *this;
}
constexpr typename U8Char::size_t U8Char::byte_count()const noexcept{
    return U8Char::get_byte_count((*this)[0]);
}
constexpr typename U8Char::byte_t U8Char::operator[](typename U8Char::size_t index)const noexcept{
    return this->data_.byte_array_[index];
}
constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept{
    return lhs.data_.code_point_==rhs.data_.code_point_; 
}
constexpr bool U8Char::empty()noexcept{
    return (*this)=='\0';
}
constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept{
    return !(lhs==rhs);
}
constexpr bool operator<(U8Char const& lhs,U8Char const& rhs)noexcept{
    // operator==()有优化，优先判断
    if(lhs==rhs){
        return false;
    }
    typename U8Char::size_t lhs_byte_count=lhs.byte_count();
    typename U8Char::size_t rhs_byte_count=rhs.byte_count();
    // 通过字节数判断大小
    if(lhs_byte_count!=rhs_byte_count){
        return lhs_byte_count<rhs_byte_count;
    }
    // 字节数相同的，逐个字节比较
    for(typename U8Char::size_t index=0;index<lhs_byte_count;++index){
        if(lhs[index]!=rhs[index]){
            return lhs[index]<rhs[index];
        }
    }
    return false;// lhs==rhs
}
constexpr bool operator<=(U8Char const& lhs,U8Char const& rhs)noexcept{
    return !(lhs>rhs);
}
constexpr bool operator>(U8Char const& lhs,U8Char const& rhs)noexcept{
    return rhs<lhs;
}
constexpr bool operator>=(U8Char const& lhs,U8Char const& rhs)noexcept{
    return !(lhs<rhs);
}
template<typename OutputStream>
OutputStream& operator<<(OutputStream& os,U8Char ch)noexcept{
    for(typename U8Char::size_t index=0;index<ch.byte_count();++index){
        os<<static_cast<char>(ch[index]);
    }
    return os;
}
#endif//__U8CHAR_HPP__
