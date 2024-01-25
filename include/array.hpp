#pragma once
extern "C"{
#include<stddef.h> // size_t
#include<limits.h> // SIZE_MAX
#include<stdlib.h> // malloc free realloc
#include<string.h> // memmove
} // extern "C"
#include<utility> // std::move std::forward
#include<new> // placement new
#include<initializer_list> // std::initializer_list
#include<type_traits> // std::remove_cvref_t
#include"iterator.hpp"
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
    constexpr void resize(size_t size,_Type const& value={})noexcept;

    constexpr void swap(Array<_Type>& array)noexcept;
    constexpr bool operator==(Array<_Type> const& array)const noexcept;
    constexpr bool operator!=(Array<_Type> const& array)const noexcept;
    constexpr Array<_Type>& operator+=(Array<_Type> const& array)noexcept;
    constexpr Array<_Type> operator+(Array<_Type> const& array)const noexcept;

    constexpr Array<_Type> subarr(size_t index,size_t count)const noexcept;

    template<typename OutputStream>
    constexpr OutputStream& debug_print(OutputStream& os)const noexcept;

    using iterator=Iterator<Array<_Type>,_Type,false>;
    using const_iterator=Iterator<Array<_Type>const,_Type const,false>;
    using reverse_iterator=Iterator<Array<_Type>,_Type,true>;
    using const_reverse_iterator=Iterator<Array<_Type>const,_Type const,true>;

    constexpr iterator begin()noexcept;
    constexpr iterator end()noexcept;
    constexpr const_iterator begin()const noexcept;
    constexpr const_iterator end()const noexcept;
    constexpr const_iterator cbegin()const noexcept;
    constexpr const_iterator cend()const noexcept;
    constexpr reverse_iterator rbegin()noexcept;
    constexpr reverse_iterator rend()noexcept;
    constexpr const_reverse_iterator rbegin()const noexcept;
    constexpr const_reverse_iterator rend()const noexcept;
    constexpr const_reverse_iterator crbegin()const noexcept;
    constexpr const_reverse_iterator crend()const noexcept;

    // _Func:(_Type value)->_U(value_type not cvref)
    // {E1,E2,...,En} --map(func)--> {func(E1),func(E2),...,func(En)}
    template<typename _Func>
    constexpr auto map(_Func&& func)const noexcept
        ->Array<std::remove_cvref_t<decltype(std::forward<_Func>(func)(_Type{}))>>;
    // _Func:(_Ret value,_Type value)->_Ret
    // {E1,E2,...,En} --reduce(func<like op(x,y)->z>,init)--> init op E1 op E2 ... op En
    template<typename _Func,typename _Ret=_Type>
    constexpr _Ret reduce(_Func&& func,_Ret&& init={})const noexcept;
    // _Func:(_Type value)->bool
    // {E1,E2,...,En} --filter(func)-->[func(E)==true?]--> {Ex,Ey,...,Ez}
    template<typename _Func>
    constexpr Array<_Type> filter(_Func&& func)const noexcept;
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
    this->data_=static_cast<Element*>(::malloc(sizeof(Element)*Array::default_capacity_));
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
    (this->data_[index]).pointer_=static_cast<_Type*>(::malloc(sizeof(_Type)));
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
        (this->data_[index+n]).pointer_=static_cast<_Type*>(::malloc(sizeof(_Type)));
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
            (this->data_[index+n]).pointer_=static_cast<_Type*>(::malloc(sizeof(_Type)));
            new((this->data_[index+n]).pointer_)_Type(array[n]);
        }
    }else{
        Array<_Type>array_value=array;
        ::memmove(this->data_+index+array_value.size_,this->data_+index,(this->size_-index)*sizeof(Element));
        for(size_t n=0;n<array_value.size_;++n){
            (this->data_[index+n]).pointer_=static_cast<_Type*>(::malloc(sizeof(_Type)));
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
        this->data_=static_cast<Element*>(::realloc(this->data_,capacity*sizeof(Element)));
        this->capacity_=capacity;
    }
}
template<typename _Type>
constexpr void Array<_Type>::shrink_to_fit()noexcept{
    if(this->capacity_>this->size_){
        this->data_=static_cast<Element*>(::realloc(this->data_,capacity*sizeof(Element)));
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
    return SIZE_MAX;
}
template<typename _Type>
constexpr void Array<_Type>::resize(size_t size,_Type const& value)noexcept{
    if(size>this->size_){
        this->reserve_capacity(size);
        this->insert(this->size_,value,size-this->size_);
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
    os<<"Array{\n"
        <<"\taddress:"<<this<<'\n'
        <<"\tdata:"<<this->data_<<'\n'
        <<"\tsize:"<<this->size_<<'\n'
        <<"\tcapacity:"<<this->capacity_<<'\n';
    for(size_t index=0;index<this->size_;++index){
        os<<"\tElement{\n"
            <<"\t\tindex:"<<index<<'\n'
            <<"\t\taddress:"<<&(this->data_[index])<<'\n'
            <<"\t\tpointer:"<<(this->data_[index]).pointer_<<'\n'
            <<"\t\tvalue:"<<*((this->data_[index]).pointer_)<<'\n'
            <<"\t}\n";
    }
    return os<<"}\n";
}
template<typename _Type>
constexpr typename Array<_Type>::iterator Array<_Type>::begin()noexcept{
    return iterator(this,0);
}
template<typename _Type>
constexpr typename Array<_Type>::iterator Array<_Type>::end()noexcept{
    return iterator(this,this->size_);
}
template<typename _Type>
constexpr typename Array<_Type>::const_iterator Array<_Type>::begin()const noexcept{
    return this->cbegin();
}
template<typename _Type>
constexpr typename Array<_Type>::const_iterator Array<_Type>::end()const noexcept{
    return this->cend();
}
template<typename _Type>
constexpr typename Array<_Type>::const_iterator Array<_Type>::cbegin()const noexcept{
    return const_iterator(this,0);
}
template<typename _Type>
constexpr typename Array<_Type>::const_iterator Array<_Type>::cend()const noexcept{
    return const_iterator(this,
        static_cast<typename Array<_Type>::const_iterator::index_t>(this->size_));
}
template<typename _Type>
constexpr typename Array<_Type>::reverse_iterator Array<_Type>::rbegin()noexcept{
    return reverse_iterator(this,
        static_cast<typename Array<_Type>::reserve_iterator::index_t>(this->size_)-1);
}
template<typename _Type>
constexpr typename Array<_Type>::reverse_iterator Array<_Type>::rend()noexcept{
    return reverse_iterator(this,-1);
}
template<typename _Type>
constexpr typename Array<_Type>::const_reverse_iterator Array<_Type>::rbegin()const noexcept{
    return this->crbegin();
}
template<typename _Type>
constexpr typename Array<_Type>::const_reverse_iterator Array<_Type>::rend()const noexcept{
    return this->crend();
}
template<typename _Type>
constexpr typename Array<_Type>::const_reverse_iterator Array<_Type>::crbegin()const noexcept{
    return const_reverse_iterator(this,
        static_cast<typename Array<_Type>::const_reserve_iterator::index_t>(this->size_)-1);
}
template<typename _Type>
constexpr typename Array<_Type>::const_reverse_iterator Array<_Type>::crend()const noexcept{
    return const_reverse_iterator(this,-1);
}
template<typename _Type>
constexpr void Array<_Type>::auto_expand_capacity()noexcept{
    if(this->size_<this->capacity_){
        return;
    }
    this->reserve_capacity(this->capacity_*2);
}
template<typename _Type>
template<typename _Func>
constexpr auto Array<_Type>::map(_Func&& func)const noexcept
    ->Array<std::remove_cvref_t<decltype(std::forward<_Func>(func)(_Type{}))>>{
    using type=
        std::remove_cvref_t<decltype(std::forward<_Func>(func)(_Type{}))>;
    Array<type> ret;
    for(auto const& element:(*this)){
        ret.push_back(std::forward<_Func>(func)(element));
    }
    return ret;
}
template<typename _Type>
template<typename _Func,typename _Ret>
constexpr _Ret Array<_Type>::reduce(_Func&& func,_Ret&& init)const noexcept{
    _Ret ret=std::forward<_Ret>(init);
    for(auto const& element:(*this)){
        ret=std::forward<_Func>(func)(ret,element);
    }
    return ret;
}
template<typename _Type>
template<typename _Func>
constexpr Array<_Type> Array<_Type>::filter(_Func&& func)const noexcept{
    Array<_Type> ret;
    for(auto const& element:(*this)){
        if(std::forward<_Func>(func)(element)){
            ret.push_back(element);
        }
    }
    return ret;
}
template<typename _Type,typename OutputStream>
constexpr OutputStream& operator<<(OutputStream& os,Array<_Type>const& array)noexcept{
    os<<'[';
    for(size_t index=0;index<array.size();++index){
        os<<array[index]<<(index+1!=array.size()?",":"");
    }
    return os<<']';
}