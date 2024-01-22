#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__
extern "C"{
#include<stddef.h> // size_t
#include<stdint.h> // intmax_t
}
// _Type : T->Iter / T const->ConstIter
// _is_reverse : false->Iter / true->ReverseIter
template<typename _Container,typename _Type,bool _is_reverse=false>
class Iterator{
public:
    using value_type=_Type;
    using pointer=value_type*;
    using reference=value_type&;
    using iterator=Iterator<_Container,_Type,_is_reverse>;
    using index_t=double;
    using integer=intmax_t;
    constexpr Iterator(iterator const&)noexcept=default;
    constexpr iterator& operator=(iterator const&)noexcept=default;
    constexpr Iterator(_Container* container=nullptr,index_t index=0)noexcept;
    constexpr reference operator*()const noexcept;
    constexpr pointer operator->()const noexcept;
    constexpr operator bool()const noexcept;
    constexpr iterator& operator++()noexcept;
    constexpr iterator operator++(int)noexcept;
    constexpr iterator& operator--()noexcept;
    constexpr iterator operator--(int)noexcept;
    constexpr iterator operator+(integer offset)const noexcept;
    constexpr iterator operator-(integer offset)const noexcept;
    constexpr iterator& operator+=(integer offset)noexcept;
    constexpr iterator& operator-=(integer offset)noexcept;
private:
    _Container* container_;
    index_t index_;
};
template<typename _Container,typename _Type,bool _is_reverse>
constexpr Iterator<_Container,_Type,_is_reverse>::
Iterator(_Container* container,index_t index)noexcept{
    this->container_=container;
    this->index_=index;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::reference
Iterator<_Container,_Type,_is_reverse>::operator*()const noexcept{
    return (*(this->container_))[static_cast<size_t>(this->index_)];
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::pointer
Iterator<_Container,_Type,_is_reverse>::operator->()const noexcept{
    return &(this->operator*());
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr Iterator<_Container,_Type,_is_reverse>::operator bool()const noexcept{
    return container_!=nullptr&&
        index_>=0&&
        index_<this->container_->size();
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator& 
Iterator<_Container,_Type,_is_reverse>::operator++()noexcept{
    return this->operator+=(1);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator
Iterator<_Container,_Type,_is_reverse>::operator++(int)noexcept{
    iterator ret=*this;
    ++(*this);
    return ret;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator&
Iterator<_Container,_Type,_is_reverse>::operator--()noexcept{
    return this->operator-=(1);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator
Iterator<_Container,_Type,_is_reverse>::operator--(int)noexcept{
    iterator ret=*this;
    --(*this);
    return ret;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator
Iterator<_Container,_Type,_is_reverse>::operator+(integer offset)const noexcept{
    iterator ret=*this;
    return ret+=offset;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator
Iterator<_Container,_Type,_is_reverse>::operator-(integer offset)const noexcept{
    iterator ret=*this;
    return ret-=offset;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator&
Iterator<_Container,_Type,_is_reverse>::operator+=(integer offset)noexcept{
    this->index_+=static_cast<index_t>(
        _is_reverse
        ?-offset
        :offset
    );
    return *this;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator&
Iterator<_Container,_Type,_is_reverse>::operator-=(integer offset)noexcept{
    this->index_-=static_cast<index_t>(
        _is_reverse
        ?-offset
        :offset
    );
    return *this;
}
#endif//__ITERATOR_HPP__