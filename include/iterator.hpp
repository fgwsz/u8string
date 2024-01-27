#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__
extern "C"{
#include<stddef.h> // size_t ptrdiff_t
#include<stdint.h> // intmax_t
}
#include<type_traits> // std::is_const
#include<cstddef> // std::nullptr_t
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
    using container_t=_Container;
    constexpr Iterator(iterator const&)noexcept=default;
    constexpr iterator& operator=(iterator const&)noexcept=default;
    constexpr Iterator(container_t* container=nullptr,index_t index=0)noexcept;
    constexpr reference operator*()const noexcept;
    constexpr pointer operator->()const noexcept;
    constexpr operator bool()const noexcept;
    constexpr iterator& operator++()noexcept;
    constexpr iterator operator++(int)noexcept;
    constexpr iterator& operator--()noexcept;
    constexpr iterator operator--(int)noexcept;
    constexpr iterator operator+(ptrdiff_t offset)const noexcept;
    constexpr iterator operator-(ptrdiff_t offset)const noexcept;
    constexpr ptrdiff_t operator-(iterator iter)const noexcept;
    constexpr iterator& operator+=(ptrdiff_t offset)noexcept;
    constexpr iterator& operator-=(ptrdiff_t offset)noexcept;
    constexpr bool operator==(iterator const& rhs)const noexcept;
    constexpr bool operator!=(iterator const& rhs)const noexcept;
    constexpr bool operator< (iterator const& rhs)const noexcept;
    constexpr bool operator<=(iterator const& rhs)const noexcept;
    constexpr bool operator> (iterator const& rhs)const noexcept;
    constexpr bool operator>=(iterator const& rhs)const noexcept;
    constexpr bool operator==(std::nullptr_t const& rhs)const noexcept;
    constexpr bool operator!=(std::nullptr_t const& rhs)const noexcept;
    constexpr container_t* container()const noexcept;
    constexpr index_t index()const noexcept;
    constexpr bool is_const_iterator()const noexcept;
    constexpr bool is_reverse_iterator()const noexcept;
private:
    container_t* container_;
    index_t index_;
};
template<typename _Container,typename _Type,bool _is_reverse>
constexpr Iterator<_Container,_Type,_is_reverse>::
Iterator(container_t* container,index_t index)noexcept{
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
Iterator<_Container,_Type,_is_reverse>::operator+(ptrdiff_t offset)const noexcept{
    iterator ret=*this;
    return ret+=offset;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator
Iterator<_Container,_Type,_is_reverse>::operator-(ptrdiff_t offset)const noexcept{
    iterator ret=*this;
    return ret-=offset;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr ptrdiff_t
Iterator<_Container,_Type,_is_reverse>::operator-(iterator iter)const noexcept{
    return static_cast<ptrdiff_t>(this->index_-iter.index_);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator&
Iterator<_Container,_Type,_is_reverse>::operator+=(ptrdiff_t offset)noexcept{
    this->index_+=static_cast<index_t>(
        _is_reverse
        ?-offset
        :offset
    );
    return *this;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::iterator&
Iterator<_Container,_Type,_is_reverse>::operator-=(ptrdiff_t offset)noexcept{
    return this->operator+=(-offset);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator==(iterator const& rhs)const noexcept{
    return this->container_==rhs.container_&&
        this->index_==rhs.index_;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator!=(iterator const& rhs)const noexcept{
    return !((*this)==rhs);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator==(std::nullptr_t const& rhs)const noexcept{
    return this->operator bool()==false;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator!=(std::nullptr_t const& rhs)const noexcept{
    return !((*this)==rhs);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator<(iterator const& rhs)const noexcept{
    if(this->container_!=rhs.container_){
        return false;
    }
    if(!_is_reverse){
        return this->index_<rhs.index_;
    }else{
        return this->index_>rhs.index_;
    }
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator<=(iterator const& rhs)const noexcept{
    if(this->container_!=rhs.container_){
        return false;
    }
    return !((*this)>rhs);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator>(iterator const& rhs)const noexcept{
    if(this->container_!=rhs.container_){
        return false;
    }
    return rhs<(*this);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::operator>=(iterator const& rhs)const noexcept{
    if(this->container_!=rhs.container_){
        return false;
    }
    return !((*this)<rhs);
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::container_t*
Iterator<_Container,_Type,_is_reverse>::container()const noexcept{
    return this->container_;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr typename Iterator<_Container,_Type,_is_reverse>::index_t
Iterator<_Container,_Type,_is_reverse>::index()const noexcept{
    return this->index_;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::is_const_iterator()const noexcept{
    return std::is_const_v<_Type>;
}
template<typename _Container,typename _Type,bool _is_reverse>
constexpr bool
Iterator<_Container,_Type,_is_reverse>::is_reverse_iterator()const noexcept{
    return _is_reverse;
}
#endif//__ITERATOR_HPP__