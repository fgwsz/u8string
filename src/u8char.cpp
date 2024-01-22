#include"u8char.h"
// 通过输入utf8编码字符的首字节，得到该utf8字符的字节个数
// 如果first_byte取值不符合utf8编码规则，则返回0
static constexpr U8Char::size_t get_byte_count(U8Char::byte_t first_byte)noexcept{
    constexpr U8Char::byte_t utf8_1byte_min=0b00000000;
    constexpr U8Char::byte_t utf8_1byte_max=0b01111111;
    constexpr U8Char::byte_t utf8_2bytes_first_byte_min=0b11000000;
    constexpr U8Char::byte_t utf8_2bytes_first_byte_max=0b11011111;
    constexpr U8Char::byte_t utf8_3bytes_first_byte_min=0b11100000;
    constexpr U8Char::byte_t utf8_3bytes_first_byte_max=0b11101111;
    constexpr U8Char::byte_t utf8_4bytes_first_byte_min=0b11110000;
    constexpr U8Char::byte_t utf8_4bytes_first_byte_max=0b11110111;
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
// 检查utf8编码多字节字符的除首字节之外的剩余单字节是否符合utf8编码规则
// 如果符合返回true，反之返回false
static constexpr bool check_other_byte(U8Char::byte_t other_byte)noexcept{
    constexpr U8Char::byte_t utf8_bytes_other_byte_min=0b10000000;
    constexpr U8Char::byte_t utf8_bytes_other_byte_max=0b10111111;
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
    if(::get_byte_count(first_byte)==0){
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
    U8Char::byte_t first_byte=static_cast<U8Char::byte_t>(c_str[0]);
    U8Char::size_t byte_count=::get_byte_count(first_byte);
    if(byte_count==0){ // 首字节不符合utf8编码规则
        return *this;
    }
    if(byte_count>1){ // 检查剩余字节是否符合utf8编码规则
        U8Char::byte_t other_byte=0;
        for(U8Char::size_t index=1;index<byte_count;++index){
            if(!::check_other_byte(
                static_cast<U8Char::byte_t>(c_str[index])
            )){
                return *this;
            }
        }
    }
    // 对字节数组进行字节赋值
    for(U8Char::size_t index=0;index<byte_count;++index){
        this->data_.byte_array_[index]=static_cast<U8Char::byte_t>(c_str[index]);
    }
    // 将字节数组未赋值的剩余元素置0
    for(U8Char::size_t index=byte_count;index<4;++index){
        this->data_.byte_array_[index]=0;
    }
    return *this;
}
constexpr U8Char::size_t U8Char::byte_count()const noexcept{
    return ::get_byte_count((*this)[0]);
}
constexpr U8Char::byte_t U8Char::operator[](U8Char::size_t index)const noexcept{
    return this->data_.byte_array_[index];
}
constexpr bool operator==(U8Char const& lhs,U8Char const& rhs)noexcept{
    return lhs.data_.code_point_==rhs.data_.code_point_; 
}
constexpr bool operator!=(U8Char const& lhs,U8Char const& rhs)noexcept{
    return !(lhs==rhs);
}
constexpr bool operator<(U8Char const& lhs,U8Char const& rhs)noexcept{
    // operator==()有优化，优先判断
    if(lhs==rhs){
        return false;
    }
    U8Char::size_t lhs_byte_count=lhs.byte_count();
    U8Char::size_t rhs_byte_count=rhs.byte_count();
    // 通过字节数判断大小
    if(lhs_byte_count!=rhs_byte_count){
        return lhs_byte_count<rhs_byte_count;
    }
    // 字节数相同的，逐个字节比较
    for(U8Char::size_t index=0;index<lhs_byte_count;++index){
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