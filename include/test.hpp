#ifndef __TEST_HPP__
#define __TEST_HPP__
#include<string>
#include<string_view>
#include<iostream>
#include<vector>
#include<functional>
#include<stdexcept>
class __Test{
public:
    static bool add(
        std::string_view const& test_name,
        std::function<void()>const& test_func
    );
    static void run();
private:
    static std::vector<std::function<void()>> test_funcs;
    static std::vector<std::string_view> test_names;
};
std::vector<std::function<void()>> __Test::test_funcs={};
std::vector<std::string_view> __Test::test_names={};
bool __Test::add(
    std::string_view const& test_name,
    std::function<void()>const& test_func
){
    __Test::test_names.push_back(test_name);
    __Test::test_funcs.push_back(test_func);
    return true;
}
void __Test::run(){
    size_t size=__Test::test_funcs.size();
    for(size_t index=0;index<size;++index){
        try{
            __Test::test_funcs[index]();
            std::cout<<"[TEST] "<<__Test::test_names[index]<<" "
                "[PASS]"<<std::endl;
        }catch(std::runtime_error const& error){
            std::cout<<"[TEST] "<<__Test::test_names[index]<<" "
                "[FAIL]\n"<<error.what()<<std::endl;
        }catch(...){
            std::cout<<"[TEST] "<<__Test::test_names[index]<<" "
                "[FAIL]\n\t"<<"<excp> unknow!"<<std::endl;
        }
    }
}
#define __TEST_ADD(__FUNC_NAME__) \
    static bool __test_flag_##__FUNC_NAME__= \
    __Test::add(#__FUNC_NAME__,std::function<void()>{__FUNC_NAME__}) \
//
#define TEST_DEF(__FUNC_NAME__) \
    static void __FUNC_NAME__(); \
    __TEST_ADD(__FUNC_NAME__); \
    void __FUNC_NAME__() \
//
#define __TEST_THROW_ERROR(__INFO__) do { \
    throw std::runtime_error( \
        "\t<file> "+std::string(__FILE__)+"\n" \
        "\t<line> "+std::to_string(__LINE__)+"\n" \
        "\t<func> "+std::string(__func__)+"\n" \
        "\t<info> "+__INFO__ \
    ); \
}while(0) \
//
#define TEST_REQ(...) do{ \
    if(!(__VA_ARGS__)){ \
        __TEST_THROW_ERROR(#__VA_ARGS__); \
    } \
}while(0) \
//
#define TEST_RUN() do{ \
    __Test::run(); \
}while(0) \
//
#endif//__TEST_HPP__