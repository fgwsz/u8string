#ifndef __TEST_ITERATOR_HPP__
#define __TEST_ITERATOR_HPP__
#include"iterator.hpp"
#include"test.hpp"
#include<vector>
#include<string>
// TEST API:
// [o] consteopr Iterator(container_t* container=nullptr,indeo_t indeo=0)noeocept;
// [o] consteopr reference operator*()const noeocept;
// [o] consteopr pointer operator->()const noeocept;
// [o] consteopr operator bool()const noeocept;
// [o] consteopr iterator& operator++()noeocept;
// [o] consteopr iterator operator++(int)noeocept;
// [o] consteopr iterator& operator--()noeocept;
// [o] consteopr iterator operator--(int)noeocept;
// [o] consteopr iterator operator+(ptrdiff_t offset)const noeocept;
// [o] consteopr iterator operator-(ptrdiff_t offset)const noeocept;
// [o] consteopr ptrdiff_t operator-(iterator iter)const noeocept;
// [o] consteopr iterator& operator+=(ptrdiff_t offset)noeocept;
// [o] consteopr iterator& operator-=(ptrdiff_t offset)noeocept;
// [o] consteopr bool operator==(iterator const& rhs)const noeocept;
// [o] consteopr bool operator!=(iterator const& rhs)const noeocept;
// [o] consteopr bool operator< (iterator const& rhs)const noeocept;
// [o] consteopr bool operator<=(iterator const& rhs)const noeocept;
// [o] consteopr bool operator> (iterator const& rhs)const noeocept;
// [o] consteopr bool operator>=(iterator const& rhs)const noeocept;
// [o] consteopr bool operator==(std::nullptr_t const& rhs)const noeocept;
// [o] consteopr bool operator!=(std::nullptr_t const& rhs)const noeocept;
// [o] consteopr container_t* container()const noeocept;
// [o] consteopr indeo_t indeo()const noeocept;
// [o] consteopr bool is_const_iterator()const noeocept;
// [o] consteopr bool is_reverse_iterator()const noeocept;

// [o] constexpr Iterator(container_t* container=nullptr,index_t index=0)noexcept;
TEST_UNIT(test_iterator_ctor_by_container_and_index){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    container_t container;
    iterator_t iter(&container,0);
    TEST_CASE(iter.container()==&container);
    TEST_CASE(iter.index()==0);
}
// [o] constexpr reference operator*()const noexcept;
TEST_UNIT(test_iterator_operator_dereference){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    container_t container{1};
    iterator_t iter(&container,0);
    TEST_CASE(&(*iter)==&(container[0]));
}
// [o] constexpr pointer operator->()const noexcept;
TEST_UNIT(test_iterator_operator_field_at){
    using element_t=std::string;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    container_t container{"hello"};
    iterator_t iter(&container,0);
    iter->clear();
    TEST_CASE(container[0].empty());
}
// [o] constexpr operator bool()const noexcept;
TEST_UNIT(test_iterator_operator_bool){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    container_t container{1,2,3};

    iterator_t iter_1(&container,0);
    TEST_CASE(iter_1.operator bool()==true);

    iterator_t iter_2(&container,3);
    TEST_CASE(iter_2.operator bool()==false);

    iterator_t iter_3(nullptr,0);
    TEST_CASE(iter_3.operator bool()==false);

    iterator_t iter_4(nullptr,100);
    TEST_CASE(iter_4.operator bool()==false);

    iterator_t iter_5(&container,-1);
    TEST_CASE(iter_5.operator bool()==false);
}
// [o] constexpr iterator& operator++()noexcept;
TEST_UNIT(test_iterator_operator_pre_increment){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{1,2,3};

    iterator_t iter(&container,0);
    auto& iter_ref=(++iter);
    TEST_CASE(&iter_ref==&iter);
    TEST_CASE(*iter==2);

    reverse_iterator_t reverse_iter(&container,2);
    auto& reverse_iter_ref=(++reverse_iter);
    TEST_CASE(&reverse_iter_ref==&reverse_iter);
    TEST_CASE(*reverse_iter==2);
}
// [o] constexpr iterator operator++(int)noexcept;
TEST_UNIT(test_iterator_operator_post_increment){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{1,2,3};

    iterator_t iter(&container,0);
    auto iter_old=(iter++);
    TEST_CASE(&iter_old!=&iter);
    TEST_CASE(*iter_old==1);
    TEST_CASE(*iter==2);

    reverse_iterator_t reverse_iter(&container,2);
    auto reverse_iter_old=(reverse_iter++);
    TEST_CASE(&reverse_iter_old!=&reverse_iter);
    TEST_CASE(*reverse_iter_old==3);
    TEST_CASE(*reverse_iter==2);
}
// [o] constexpr iterator& operator--()noexcept;
TEST_UNIT(test_iterator_operator_pre_decrement){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{1,2,3};// 0,1,2

    iterator_t iter(&container,2);
    auto& iter_ref=(--iter);
    TEST_CASE(&iter_ref==&iter);
    TEST_CASE(*iter==2);

    reverse_iterator_t reverse_iter(&container,0);
    auto& reverse_iter_ref=(--reverse_iter);
    TEST_CASE(&reverse_iter_ref==&reverse_iter);
    TEST_CASE(*reverse_iter==2);
}
// [o] constexpr iterator operator--(int)noexcept;
TEST_UNIT(test_iterator_operator_post_decrement){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{1,2,3};// 0,1,2

    iterator_t iter(&container,2);
    auto iter_old=(iter--);
    TEST_CASE(&iter_old!=&iter);
    TEST_CASE(*iter_old==3);
    TEST_CASE(*iter==2);

    reverse_iterator_t reverse_iter(&container,0);
    auto reverse_iter_old=(reverse_iter--);
    TEST_CASE(&reverse_iter_old!=&reverse_iter);
    TEST_CASE(*reverse_iter_old==1);
    TEST_CASE(*reverse_iter==2);
}
// [o] constexpr iterator operator+(ptrdiff_t offset)const noexcept;
TEST_UNIT(test_iterator_operator_plus){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_ret;
    iterator_t iter(&container,0);
    iter_ret=iter+ptrdiff_t(3);
    TEST_CASE(iter_ret.index()==3);
    TEST_CASE(*iter_ret==3);

    reverse_iterator_t reverse_iter_ret;
    reverse_iterator_t reverse_iter(&container,10);
    reverse_iter_ret=reverse_iter+ptrdiff_t(3);
    TEST_CASE(reverse_iter_ret.index()==7);
    TEST_CASE(*reverse_iter_ret==7);
}
// [o] constexpr iterator operator-(ptrdiff_t offset)const noexcept;
TEST_UNIT(test_iterator_operator_sub_by_offset){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_ret;
    iterator_t iter(&container,10);
    iter_ret=iter-ptrdiff_t(3);
    TEST_CASE(iter_ret.index()==7);
    TEST_CASE(*iter_ret==7);

    reverse_iterator_t reverse_iter_ret;
    reverse_iterator_t reverse_iter(&container,0);
    reverse_iter_ret=reverse_iter-ptrdiff_t(3);
    TEST_CASE(reverse_iter_ret.index()==3);
    TEST_CASE(*reverse_iter_ret==3);
}
// [o] constexpr ptrdiff_t operator-(iterator iter)const noexcept;
TEST_UNIT(test_iterator_operator_sub_by_iterator){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};
    ptrdiff_t ret;

    iterator_t iter_lhs(&container,10);
    iterator_t iter_rhs(&container,0);
    ret=iter_lhs-iter_rhs;
    TEST_CASE(ret==10);

    reverse_iterator_t reverse_iter_lhs(&container,0);
    reverse_iterator_t reverse_iter_rhs(&container,10);
    ret=reverse_iter_lhs-reverse_iter_rhs;
    TEST_CASE(ret==10);
}
// [o] constexpr iterator& operator+=(ptrdiff_t offset)noexcept;
TEST_UNIT(test_iterator_operator_plus_eq){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter(&container,0);
    iter+=ptrdiff_t(3);
    TEST_CASE(iter.index()==3);
    TEST_CASE(*iter==3);

    reverse_iterator_t reverse_iter(&container,10);
    reverse_iter+=ptrdiff_t(3);
    TEST_CASE(reverse_iter.index()==7);
    TEST_CASE(*reverse_iter==7);
}
// [o] constexpr iterator& operator-=(ptrdiff_t offset)noexcept;
TEST_UNIT(test_iterator_operator_sub_eq){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter(&container,10);
    iter-=ptrdiff_t(3);
    TEST_CASE(iter.index()==7);
    TEST_CASE(*iter==7);

    reverse_iterator_t reverse_iter(&container,0);
    reverse_iter-=ptrdiff_t(3);
    TEST_CASE(reverse_iter.index()==3);
    TEST_CASE(*reverse_iter==3);
}
// [o] constexpr bool operator==(iterator const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_eq_by_iterator){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_lhs_1(&container,10);
    iterator_t iter_rhs_1(&container,10);
    TEST_CASE(iter_lhs_1==iter_rhs_1);

    iterator_t iter_lhs_2(&container,0);
    iterator_t iter_rhs_2(&container,10);
    TEST_CASE(!(iter_lhs_2==iter_rhs_2));

    iterator_t iter_lhs_3(nullptr,0);
    iterator_t iter_rhs_3(&container,0);
    TEST_CASE(!(iter_lhs_3==iter_rhs_3));

    reverse_iterator_t reverse_iter_lhs_1(&container,10);
    reverse_iterator_t reverse_iter_rhs_1(&container,10);
    TEST_CASE(reverse_iter_lhs_1==reverse_iter_rhs_1);

    reverse_iterator_t reverse_iter_lhs_2(&container,0);
    reverse_iterator_t reverse_iter_rhs_2(&container,10);
    TEST_CASE(!(reverse_iter_lhs_2==reverse_iter_rhs_2));

    reverse_iterator_t reverse_iter_lhs_3(nullptr,0);
    reverse_iterator_t reverse_iter_rhs_3(&container,0);
    TEST_CASE(!(reverse_iter_lhs_3==reverse_iter_rhs_3));
}
// [o] constexpr bool operator!=(iterator const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_not_eq_by_iterator){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_lhs_1(&container,10);
    iterator_t iter_rhs_1(&container,10);
    TEST_CASE(!(iter_lhs_1!=iter_rhs_1));

    iterator_t iter_lhs_2(&container,0);
    iterator_t iter_rhs_2(&container,10);
    TEST_CASE(iter_lhs_2!=iter_rhs_2);

    iterator_t iter_lhs_3(nullptr,0);
    iterator_t iter_rhs_3(&container,0);
    TEST_CASE(iter_lhs_3!=iter_rhs_3);

    reverse_iterator_t reverse_iter_lhs_1(&container,10);
    reverse_iterator_t reverse_iter_rhs_1(&container,10);
    TEST_CASE(!(reverse_iter_lhs_1!=reverse_iter_rhs_1));

    reverse_iterator_t reverse_iter_lhs_2(&container,0);
    reverse_iterator_t reverse_iter_rhs_2(&container,10);
    TEST_CASE(reverse_iter_lhs_2!=reverse_iter_rhs_2);

    reverse_iterator_t reverse_iter_lhs_3(nullptr,0);
    reverse_iterator_t reverse_iter_rhs_3(&container,0);
    TEST_CASE(reverse_iter_lhs_3!=reverse_iter_rhs_3);
}
// [o] constexpr bool operator< (iterator const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_less){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_lhs(nullptr,0);
    iterator_t iter_rhs(nullptr,0);
    TEST_CASE((iter_lhs<iter_rhs)==false);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(nullptr,10);
    TEST_CASE((iter_lhs<iter_rhs)==true);

    iter_lhs=iterator_t(nullptr,10);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs<iter_rhs)==false);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs<iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs<iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs<iter_rhs)==false);

    iter_lhs=iterator_t(&container,10);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs<iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,10);
    TEST_CASE((iter_lhs<iter_rhs)==true);

    reverse_iterator_t reverse_iter_lhs(nullptr,0);
    reverse_iterator_t reverse_iter_rhs(nullptr,0);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,10);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,10);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,10);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,10);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs<reverse_iter_rhs)==true);
}
// [o] constexpr bool operator<=(iterator const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_less_than){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_lhs(nullptr,0);
    iterator_t iter_rhs(nullptr,0);
    TEST_CASE((iter_lhs<=iter_rhs)==true);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(nullptr,10);
    TEST_CASE((iter_lhs<=iter_rhs)==true);

    iter_lhs=iterator_t(nullptr,10);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs<=iter_rhs)==false);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs<=iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs<=iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs<=iter_rhs)==true);

    iter_lhs=iterator_t(&container,10);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs<=iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,10);
    TEST_CASE((iter_lhs<=iter_rhs)==true);

    reverse_iterator_t reverse_iter_lhs(nullptr,0);
    reverse_iterator_t reverse_iter_rhs(nullptr,0);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,10);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,10);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,10);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,10);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs<=reverse_iter_rhs)==true);
}
// [o] constexpr bool operator> (iterator const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_greater){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_lhs(nullptr,0);
    iterator_t iter_rhs(nullptr,0);
    TEST_CASE((iter_lhs>iter_rhs)==false);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(nullptr,10);
    TEST_CASE((iter_lhs>iter_rhs)==false);

    iter_lhs=iterator_t(nullptr,10);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs>iter_rhs)==true);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs>iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs>iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs>iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,10);
    TEST_CASE((iter_lhs>iter_rhs)==false);

    iter_lhs=iterator_t(&container,10);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs>iter_rhs)==true);

    reverse_iterator_t reverse_iter_lhs(nullptr,0);
    reverse_iterator_t reverse_iter_rhs(nullptr,0);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,10);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(nullptr,10);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,10);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,10);
    TEST_CASE((reverse_iter_lhs>reverse_iter_rhs)==true);
}
// [o] constexpr bool operator>=(iterator const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_greater_than){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter_lhs(nullptr,0);
    iterator_t iter_rhs(nullptr,0);
    TEST_CASE((iter_lhs>=iter_rhs)==true);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(nullptr,10);
    TEST_CASE((iter_lhs>=iter_rhs)==false);

    iter_lhs=iterator_t(nullptr,10);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs>=iter_rhs)==true);

    iter_lhs=iterator_t(nullptr,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs>=iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(nullptr,0);
    TEST_CASE((iter_lhs>=iter_rhs)==false);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs>=iter_rhs)==true);

    iter_lhs=iterator_t(&container,0);
    iter_rhs=iterator_t(&container,10);
    TEST_CASE((iter_lhs>=iter_rhs)==false);

    iter_lhs=iterator_t(&container,10);
    iter_rhs=iterator_t(&container,0);
    TEST_CASE((iter_lhs>=iter_rhs)==true);

    reverse_iterator_t reverse_iter_lhs(nullptr,0);
    reverse_iterator_t reverse_iter_rhs(nullptr,0);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,10);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(nullptr,10);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(nullptr,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(nullptr,0);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==true);

    reverse_iter_lhs=reverse_iterator_t(&container,10);
    reverse_iter_rhs=reverse_iterator_t(&container,0);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==false);

    reverse_iter_lhs=reverse_iterator_t(&container,0);
    reverse_iter_rhs=reverse_iterator_t(&container,10);
    TEST_CASE((reverse_iter_lhs>=reverse_iter_rhs)==true);
}
// [o] constexpr bool operator==(std::nullptr_t const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_eq_by_nullptr){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    container_t container{1,2,3};

    iterator_t iter(&container,0);
    TEST_CASE((iter==nullptr)==false);

    iter=iterator_t(&container,3);
    TEST_CASE((iter==nullptr)==true);

    iter=iterator_t(nullptr,0);
    TEST_CASE((iter==nullptr)==true);

    iter=iterator_t(nullptr,100);
    TEST_CASE((iter==nullptr)==true);

    iter=iterator_t(&container,-1);
    TEST_CASE((iter==nullptr)==true);
}
// [o] constexpr bool operator!=(std::nullptr_t const& rhs)const noexcept;
TEST_UNIT(test_iterator_operator_not_eq_by_nullptr){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    container_t container{1,2,3};

    iterator_t iter(&container,0);
    TEST_CASE((iter!=nullptr)==true);

    iter=iterator_t(&container,3);
    TEST_CASE((iter!=nullptr)==false);

    iter=iterator_t(nullptr,0);
    TEST_CASE((iter!=nullptr)==false);

    iter=iterator_t(nullptr,100);
    TEST_CASE((iter!=nullptr)==false);

    iter=iterator_t(&container,-1);
    TEST_CASE((iter!=nullptr)==false);
}
// [o] constexpr container_t* container()const noexcept;
TEST_UNIT(test_iterator_container){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter(nullptr,0);
    TEST_CASE(iter.container()==nullptr);

    iter=iterator_t(&container,0);
    TEST_CASE(iter.container()==&container);

    reverse_iterator_t reverse_iter(nullptr,0);
    TEST_CASE(reverse_iter.container()==nullptr);

    reverse_iter=reverse_iterator_t(&container,0);
    TEST_CASE(reverse_iter.container()==&container);
}
// [o] constexpr index_t index()const noexcept;
TEST_UNIT(test_iterator_index){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter(nullptr,0);
    TEST_CASE(iter.index()==0);

    iter=iterator_t(&container,0);
    TEST_CASE(iter.index()==0);

    iter=iterator_t(&container,-1);
    TEST_CASE(iter.index()==-1);

    iter=iterator_t(&container,100);
    TEST_CASE(iter.index()==100);

    reverse_iterator_t reverse_iter(nullptr,0);
    TEST_CASE(reverse_iter.index()==0);

    reverse_iter=reverse_iterator_t(&container,0);
    TEST_CASE(reverse_iter.index()==0);

    reverse_iter=reverse_iterator_t(&container,-1);
    TEST_CASE(reverse_iter.index()==-1);

    reverse_iter=reverse_iterator_t(&container,100);
    TEST_CASE(reverse_iter.index()==100);
}
// [o] constexpr bool is_const_iterator()const noexcept;
TEST_UNIT(test_iterator_is_const_iterator){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using const_iterator_t=Iterator<container_t const,element_t const>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;
    using const_reverse_iterator_t=Iterator<container_t const,element_t const,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter(nullptr,0);
    TEST_CASE(iter.is_const_iterator()==false);

    iter=iterator_t(&container,0);
    TEST_CASE(iter.is_const_iterator()==false);

    const_iterator_t const_iter(nullptr,0);
    TEST_CASE(const_iter.is_const_iterator()==true);

    const_iter=const_iterator_t(&container,0);
    TEST_CASE(const_iter.is_const_iterator()==true);

    reverse_iterator_t reverse_iter(nullptr,0);
    TEST_CASE(reverse_iter.is_const_iterator()==false);

    reverse_iter=reverse_iterator_t(&container,0);
    TEST_CASE(reverse_iter.is_const_iterator()==false);

    const_reverse_iterator_t const_reverse_iter(nullptr,0);
    TEST_CASE(const_reverse_iter.is_const_iterator()==true);

    const_reverse_iter=const_reverse_iterator_t(&container,0);
    TEST_CASE(const_reverse_iter.is_const_iterator()==true);
}
// [o] constexpr bool is_reverse_iterator()const noexcept;
TEST_UNIT(test_iterator_is_reverse_iterator){
    using element_t=double;
    using container_t=std::vector<element_t>;
    using iterator_t=Iterator<container_t,element_t>;
    using const_iterator_t=Iterator<container_t const,element_t const>;
    using reverse_iterator_t=Iterator<container_t,element_t,true>;
    using const_reverse_iterator_t=Iterator<container_t const,element_t const,true>;

    container_t container{0,1,2,3,4,5,6,7,8,9,10};

    iterator_t iter(nullptr,0);
    TEST_CASE(iter.is_reverse_iterator()==false);

    iter=iterator_t(&container,0);
    TEST_CASE(iter.is_reverse_iterator()==false);

    const_iterator_t const_iter(nullptr,0);
    TEST_CASE(const_iter.is_reverse_iterator()==false);

    const_iter=const_iterator_t(&container,0);
    TEST_CASE(const_iter.is_reverse_iterator()==false);

    reverse_iterator_t reverse_iter(nullptr,0);
    TEST_CASE(reverse_iter.is_reverse_iterator()==true);

    reverse_iter=reverse_iterator_t(&container,0);
    TEST_CASE(reverse_iter.is_reverse_iterator()==true);

    const_reverse_iterator_t const_reverse_iter(nullptr,0);
    TEST_CASE(const_reverse_iter.is_reverse_iterator()==true);

    const_reverse_iter=const_reverse_iterator_t(&container,0);
    TEST_CASE(const_reverse_iter.is_reverse_iterator()==true);
}
#endif//__TEST_ITERATOR_HPP__