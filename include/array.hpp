#pragma once
extern "C"{
#include<stddef.h> // size_t
#include<stdlib.h> // malloc free realloc
#include<string.h> // memmove
} // extern "C"
#include<utility> // std::move
#include<new> // placement new
#include<initializer_list> // std::initializer_list
template<typename _Type>
class Array final{
public:
    constexpr Array()noexcept;
    constexpr Array(Array<_Type> const& array)noexcept;
    constexpr Array(Array<_Type>&& array)noexcept;
    template<size_t _size>
    constexpr Array(_Type const(&array)[_size])noexcept;
    constexpr Array(::std::initializer_list<_Type> const& list)noexcept;

    constexpr ~Array()noexcept;

    constexpr Array<_Type>& operator=(Array<_Type> const& array)noexcept;
    constexpr Array<_Type>& operator=(Array<_Type>&& array)noexcept;
    template<size_t _size>
    constexpr Array<_Type>& operator=(_Type const(&array)[_size])noexcept;
    constexpr Array<_Type>& operator=(::std::initializer_list<_Type> const& list)noexcept;

    constexpr bool insert(size_t index,_Type const& value)noexcept;
    constexpr bool insert(size_t index,_Type const& value,size_t count)noexcept;
    constexpr bool insert(size_t index,Array<_Type> const& array)noexcept;
    constexpr void push_back(_Type const& value)noexcept;

    constexpr bool erase(size_t index)noexcept;
    constexpr bool erase(size_t index,size_t count)noexcept;
    constexpr void pop_back()noexcept;
    constexpr void clear()noexcept;

    constexpr bool get_element(size_t index,_Type& value)const noexcept;
    constexpr bool set_element(size_t index,_Type const& value)noexcept;
    constexpr _Type& operator[](size_t index)noexcept;
    constexpr _Type const& operator[](size_t index)const noexcept;

    constexpr size_t capacity()const noexcept;
    constexpr void reserve_capacity(size_t capacity)noexcept;
    constexpr void shrink_to_fit()noexcept;

    constexpr size_t size()const noexcept;
    constexpr size_t max_size()const noexcept;
    constexpr bool empty()const noexcept;
    constexpr void resize(size_t size)noexcept;

    constexpr void swap(Array<_Type>& array)noexcept;
    constexpr bool operator==(Array<_Type> const& array)const noexcept;
    constexpr bool operator!=(Array<_Type> const& array)const noexcept;
    constexpr Array<_Type>& operator+=(Array<_Type> const& array)noexcept;
    constexpr Array<_Type> operator+(Array<_Type> const& array)const noexcept;

    constexpr Array<_Type> subarr(size_t index,size_t count)const noexcept;

    template<typename OutputStream>
    constexpr OutputStream& debug_print(OutputStream& os)const noexcept;
private:
    struct Element{
        _Type* pointer_;
    };
    Element* data_;
    size_t capacity_;
    size_t size_;
    static constexpr size_t const default_capacity_=10;
    constexpr void auto_expand_capacity()noexcept;
}; // class Array
template<typename _Type,typename OutputStream>
constexpr OutputStream& operator<<(OutputStream& os,Array<_Type>const& array)noexcept;

template<typename _Type>
constexpr Array<_Type>::Array()noexcept{
    this->data_=(Element*)::malloc(sizeof(Element)*Array::default_capacity_);
    this->capacity_=Array::default_capacity_;
    this->size_=0;
}
template<typename _Type>
constexpr Array<_Type>::Array(Array<_Type> const& array)noexcept
    :Array(){
    (*this)=array;
}
template<typename _Type>
constexpr Array<_Type>::Array(Array<_Type>&& array)noexcept
    :Array(){
    (*this)=::std::move(array);
}
template<typename _Type>
constexpr Array<_Type>::Array(::std::initializer_list<_Type> const& list)noexcept
    :Array<_Type>(){
    (*this)=list;
}
template<typename _Type>
template<size_t _size>
constexpr Array<_Type>::Array(_Type const(&array)[_size])noexcept
    :Array<_Type>(){
    (*this)=array;
}
template<typename _Type>
constexpr Array<_Type>::~Array()noexcept{
    if(this->data_){
        this->clear();
        ::free(this->data_);
    }
}
template<typename _Type>
constexpr Array<_Type>& Array<_Type>::operator=(Array<_Type> const& array)noexcept{
    if(this!=&array){
        if(this->size_>array.size_){
            this->resize(array.size_);
        }
        for(size_t index=0;index<array.size_;++index){
            this->set_element(index,array[index]);
        }
    }
    return *this;
}
template<typename _Type>
constexpr Array<_Type>& Array<_Type>::operator=(Array<_Type>&& array)noexcept{
    if(this!=&array){
        if(this->data_){
            this->clear();
            ::free(this->data_);
        }
        this->data_=array.data_;
        this->size_=array.size_;
        this->capacity_=array.capacity_;
        array.data_=nullptr;
    }
    return *this;
}
template<typename _Type>
constexpr Array<_Type>& Array<_Type>::operator=(::std::initializer_list<_Type> const& list)noexcept{
    if(this->size_>list.size()){
        this->resize(list.size());
    }
    for(size_t index=0;index<list.size();++index){
        this->set_element(index,*(list.begin()+index));
    }
    return *this;
}
template<typename _Type>
template<size_t _size>
constexpr Array<_Type>& Array<_Type>::operator=(_Type const(&array)[_size])noexcept{
    if(this->size_>_size){
        this->resize(_size);
    }
    for(size_t index=0;index<_size;++index){
        this->set_element(index,array[index]);
    }
    return *this;
}
template<typename _Type>
constexpr bool Array<_Type>::insert(size_t index,_Type const& value)noexcept{
    if(index>this->size_){
        return false;
    }
    this->auto_expand_capacity();
    ::memmove(this->data_+index+1,this->data_+index,(this->size_-index)*sizeof(Element));
    (this->data_[index]).pointer_=(_Type*)::malloc(sizeof(_Type));
    new((this->data_[index]).pointer_)_Type(value);
    ++(this->size_);
    return true;
}
template<typename _Type>
constexpr bool Array<_Type>::insert(size_t index,_Type const& value,size_t count)noexcept{
    if(index>this->size_){
        return false;
    }
    this->reserve_capacity(this->size_+count);
    ::memmove(this->data_+index+count,this->data_+index,(this->size_-index)*sizeof(Element));
    for(size_t n=0;n<count;++n){
        (this->data_[index+n]).pointer_=(_Type*)::malloc(sizeof(_Type));
        new((this->data_[index+n]).pointer_)_Type(value);
    }
    this->size_+=count;
    return true;
}
template<typename _Type>
constexpr bool Array<_Type>::insert(size_t index,Array<_Type> const& array)noexcept{
    if(index>this->size_){
        return false;
    }
    this->reserve_capacity(this->size_+array.size_);
    if(this!=&array){
        ::memmove(this->data_+index+array.size_,this->data_+index,(this->size_-index)*sizeof(Element));
        for(size_t n=0;n<array.size_;++n){
            (this->data_[index+n]).pointer_=(_Type*)::malloc(sizeof(_Type));
            new((this->data_[index+n]).pointer_)_Type(array[n]);
        }
    }else{
        Array<_Type>array_value=array;
        ::memmove(this->data_+index+array_value.size_,this->data_+index,(this->size_-index)*sizeof(Element));
        for(size_t n=0;n<array_value.size_;++n){
            (this->data_[index+n]).pointer_=(_Type*)::malloc(sizeof(_Type));
            new((this->data_[index+n]).pointer_)_Type(array_value[n]);
        }
    }
    this->size_+=array.size_;
    return true;
}
template<typename _Type>
constexpr void Array<_Type>::push_back(_Type const& value)noexcept{
    this->insert(this->size_,value);
}
template<typename _Type>
constexpr bool Array<_Type>::erase(size_t index)noexcept{
    if(index>=this->size_){
        return false;
    }
    ((this->data_[index]).pointer_)->~_Type();
    ::free((this->data_[index]).pointer_);
    ::memmove(this->data_+index,this->data_+index+1,(this->size_-index-1)*sizeof(Element));
    --(this->size_);
    return true;
}
template<typename _Type>
constexpr bool Array<_Type>::erase(size_t index,size_t count)noexcept{
    if(index>=this->size_){
        return false;
    }
    size_t real_count=count>(this->size_-index)?(this->size_-index):count;
    for(size_t n=0;n<count;++n){
        ((this->data_[index+n]).pointer_)->~_Type();
        ::free((this->data_[index+n]).pointer_);
    }
    ::memmove(this->data_+index,this->data_+index+real_count,(this->size_-index-real_count)*sizeof(Element));
    this->size_-=real_count;
    return true;
}
template<typename _Type>
constexpr void Array<_Type>::pop_back()noexcept{
    if(!this->empty()){
        this->erase(this->size_-1);
    }
}
template<typename _Type>
constexpr void Array<_Type>::clear()noexcept{
    this->resize(0);
}
template<typename _Type>
constexpr bool Array<_Type>::get_element(size_t index,_Type& value)const noexcept{
    if(index>=this->size_){
        return false;
    }
    value=*((this->data_[index]).pointer_);
    return true;
}
template<typename _Type>
constexpr bool Array<_Type>::set_element(size_t index,_Type const& value)noexcept{
    if(index>this->size_){
        return false;
    }
    if(index==this->size_){
        return this->insert(index,value);
    }
    *((this->data_[index]).pointer_)=value;
    return true;
}
template<typename _Type>
constexpr _Type& Array<_Type>::operator[](size_t index)noexcept{
    return *((this->data_[index]).pointer_);
}
template<typename _Type>
constexpr _Type const& Array<_Type>::operator[](size_t index)const noexcept{
    return *((this->data_[index]).pointer_);
}
template<typename _Type>
constexpr size_t Array<_Type>::capacity()const noexcept{
    return this->capacity_;
}
template<typename _Type>
constexpr void Array<_Type>::reserve_capacity(size_t capacity)noexcept{
    if(capacity>this->capacity_){
        this->data_=::realloc(this->data_,capacity*sizeof(Element));
        this->capacity_=capacity;
    }
}
template<typename _Type>
constexpr void Array<_Type>::shrink_to_fit()noexcept{
    if(this->capacity_>this->size_){
        this->data_=::realloc(this->data_,capacity*sizeof(Element));
        this->capacity_=this->size_;
    }
}
template<typename _Type>
constexpr bool Array<_Type>::empty()const noexcept{
    return this->size_==0;
}
template<typename _Type>
constexpr size_t Array<_Type>::size()const noexcept{
    return this->size_;
}
template<typename _Type>
constexpr size_t Array<_Type>::max_size()const noexcept{
    return ((size_t)-1);
}
template<typename _Type>
constexpr void Array<_Type>::resize(size_t size)noexcept{
    if(size>this->size_){
        this->reserve_capacity(size);
        this->insert(_Type{},size-this->size_);
    }else if(size<this->size_){
        this->erase(size,this->size_-size);
    }
    this->size_=size;
}
template<typename _Type>
constexpr void Array<_Type>::swap(Array<_Type>& array)noexcept{
    if(this!=&array){
        Element* temp_data=this->data_;
        size_t temp_size=this->size_;
        size_t temp_capacity=this->capacity_;
        this->data_=array.data_;
        this->size_=array.size_;
        this->capacity_=array.capacity_;
        array.data_=temp_data;
        array.size_=temp_size;
        array.capacity_=temp_capacity;
    }
}
template<typename _Type>
constexpr bool Array<_Type>::operator==(Array<_Type> const& array)const noexcept{
    if(this==&array){
        return true;
    }
    if(this->size_!=array.size_){
        return false;
    }
    for(size_t index=0;index<array.size_;++index){
        if((*this)[index]!=array[index]){
            return false;
        }
    }
    return true;
}
template<typename _Type>
constexpr bool Array<_Type>::operator!=(Array<_Type> const& array)const noexcept{
    return !((*this)==array);
}
template<typename _Type>
constexpr Array<_Type>& Array<_Type>::operator+=(Array<_Type> const& array)noexcept{
    this->insert(this->size_,array);
    return *this;
}
template<typename _Type>
constexpr Array<_Type> Array<_Type>::operator+(Array<_Type> const& array)const noexcept{
    Array<_Type> ret(*this);
    return ret+=array;
}
template<typename _Type>
constexpr Array<_Type> Array<_Type>::subarr(size_t index,size_t count)const noexcept{
    Array<_Type> ret;
    if(this->empty()||count==0||index>=this->size_){
        return ret;
    }
    size_t ret_size=(index+count)>this->size_?(this->size_-index):count;
    ret.reserve_capacity(ret_size);
    for(size_t i=index;index<ret_size;++index){
        ret.push_back((*this)[index]);
    }
    return ret;
}
template<typename _Type>
template<typename OutputStream>
constexpr OutputStream& Array<_Type>::debug_print(OutputStream& os)const noexcept{
    os<<"+++++ARRAY BEGIN+++++\n"
        <<"data_:"<<this->data_<<'\n'
        <<"size_:"<<this->size_<<'\n'
        <<"capacity_:"<<this->capacity_<<'\n'
        <<"elemnts:\n";
    for(size_t index=0;index<this->size_;++index){
        os<<"-----ELEMENT "<<index<<" BEGIN-----\n"
            <<"pointer_:"<<(this->data_[index]).pointer_<<'\n'
            <<"value:"<<*((this->data_[index]).pointer_)<<'\n'
            <<"-----ELEMENT "<<index<<" END-----\n";
    }
    return os<<"+++++ARRAY END+++++\n";
}
template<typename _Type>
constexpr void Array<_Type>::auto_expand_capacity()noexcept{
    if(this->size_<this->capacity_){
        return;
    }
    this->reserve_capacity(this->capacity_*2);
}
template<typename _Type,typename OutputStream>
constexpr OutputStream& operator<<(OutputStream& os,Array<_Type>const& array)noexcept{
    os<<'[';
    for(size_t index=0;index<array.size();++index){
        os<<array[index]<<(index+1!=array.size()?",":"");
    }
    return os<<']';
}
template<typename _Type>
class ArrayIterator{
public:
    ArrayIterator(Array<_Type>& self,size_t index);
    ArrayIterator(Array<_Type>const& self,size_t index);
    _Type& operator*();
    _Type const& operator*()const;
    _Type* operator->();
    _Type const* operator->()const;
    ArrayIterator<_Type>& operator++();
    ArrayIterator<_Type> operator++(int);
    _Type& operator*(){
        return (*(this->self_))[this->index_];
    }
    _Type const& operator*()const{
        return (*(this->self_))[this->index_];
    }
    _Type* operator->(){
        return &(this->operator*());
    }
    _Type const* operator->()const{
        return &(this->operator*());
    }
    ArrayIterator<_Type>& operator++(){
        
    }
private:
    Array<_Type>* self_;
    size_t index_;
};