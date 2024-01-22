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
    constexpr reference operator*()const noexcept;
    constexpr pointer operator->()const noexcept;
    constexpr operator bool()const noexcept;
    constexpr iterator& operator++()const noexcept;
    constexpr iterator operator++(int)const noexcept;
    constexpr iterator& operator--()const noexcept;
    constexpr iterator operator--(int)const noexcept;
    constexpr iterator operator+(integer offset)const noexcept;
    constexpr iterator operator-(integer offset)const noexcept;
    constexpr iterator& operator+=(integer offset)const noexcept;
    constexpr iterator& operator-=(integer offset)const noexcept;
/* impl */
    friend typename _Container;
private:
    constexpr Iterator(_Container* container,index_t index)noexcept{
        this->container_=container;
        this->index_=index;
    }
public:
    constexpr reference operator*()const noexcept{
        return (*(this->container_))[static_cast<size_t>(this->index_)];
    }
    constexpr pointer operator->()const noexcept{
        return &(this->operator*());
    }
    constexpr operator bool()const noexcept{
        return container_!=nullptr&&
            index_>=0&&
            index_<this->container_->size();
    }
    constexpr iterator& operator++()const noexcept{
        return this->operator+=(1);
    }
    constexpr iterator operator++(int)const noexcept{
        iterator ret=*this;
        ++(*this);
        return ret;
    }
    constexpr iterator& operator--()const noexcept{
        return this->operator-=(1);
    }
    constexpr iterator operator--(int)const noexcept{
        iterator ret=*this;
        --(*this);
        return ret;
    }
    constexpr iterator operator+(integer offset)const noexcept{
        iterator ret=*this;
        return ret+=offset;
    }
    constexpr iterator operator-(integer offset)const noexcept{
        iterator ret=*this;
        return ret-=offset;
    }
    constexpr iterator& operator+=(integer offset)const noexcept{
        this->index_+=
            _is_reverse
            ?-offset
            :offset;
        return *this;
    }
    constexpr iterator& operator-=(integer offset)const noexcept{
        this->index_-=
            _is_reverse
            ?-offset
            :offset;
        return *this;
    }
private:
    _Container* container_;
    index_t index_;
};
#endif//__ITERATOR_HPP__