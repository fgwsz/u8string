#ifndef __ARRAY_H__
#define __ARRAY_H__
extern "C"{
    #include<stddef.h> // size_t
}
template<typename _Type>
class Array{
public:
    Array();
    virtual ~Array();
    
    Array(Array const& rhs);
    Array& operator=(Array const& rhs);

    Array& insert(size_t index,_Type const& value,size_t count=1);
    Array& insert(size_t index,Array<_Type> const& array);

    Array& erase(size_t index,size_t count=1);

    Array& clear();

    _Type& operator[](size_t index);
    _Type const& operator[](size_t index)const;

    size_t capacity()const;
    size_t length()const;
private:
    void* impl_;
};
template<typename _Type>
Array<_Type>::Array(){

}
#endif//__ARRAY_H__