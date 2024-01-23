#ifndef __TEST_HPP__
#define __TEST_HPP__
#include<string>
#include<string_view>
#include<iostream>
#include<vector>
#include<functional>
#include<stdexcept>
#include<chrono>
class __Test{
public:
    static bool add(
        std::string_view const& test_name,
        std::function<void()>const& test_func
    );
    static void run();
    static void throw_error(std::runtime_error const& error);
private:
    static std::vector<std::function<void()>> test_funcs;
    static std::vector<std::string_view> test_names;
    static std::vector<std::runtime_error> test_errors;
    static size_t test_unit_count;
    static size_t test_unit_pass_count;
    static size_t test_unit_fail_count;
public:
    static size_t test_unit_case_count;
    static size_t test_unit_case_pass_count;
    static size_t test_unit_case_fail_count;
};
std::vector<std::function<void()>> __Test::test_funcs={};
std::vector<std::string_view> __Test::test_names={};
std::vector<std::runtime_error> __Test::test_errors={};
size_t __Test::test_unit_count=0;
size_t __Test::test_unit_pass_count=0;
size_t __Test::test_unit_fail_count=0;
size_t __Test::test_unit_case_count=0;
size_t __Test::test_unit_case_pass_count=0;
size_t __Test::test_unit_case_fail_count=0;
bool __Test::add(
    std::string_view const& test_name,
    std::function<void()>const& test_func
){
    __Test::test_names.push_back(test_name);
    __Test::test_funcs.push_back(test_func);
    ++__Test::test_unit_count;
    return true;
}
void __Test::run(){
    size_t size=__Test::test_funcs.size();
    std::chrono::high_resolution_clock::time_point start_time{},end_time{};
    double duration=0;
    ::std::string exception_string{};
    bool test_unit_is_pass=false;
    for(size_t index=0;index<size;++index){
        test_unit_is_pass=false;
        __Test::test_unit_case_count=0;
        __Test::test_unit_case_pass_count=0;
        __Test::test_unit_case_fail_count=0;
        start_time=std::chrono::high_resolution_clock::now();
        try{
            __Test::test_funcs[index]();
        }catch(std::exception const& exception){
            exception_string=exception.what();
        }catch(std::string const& str){
            exception_string=str;
        }catch(std::string_view const& str_view){
            exception_string=str_view;
        }catch(char const* c_str){
            exception_string=c_str;
        }catch(...){
            exception_string="unknown exception!";
        }
        end_time=std::chrono::high_resolution_clock::now();
        duration=std::chrono::duration_cast<std::chrono::duration<double>>(
                end_time - start_time
            ).count()*1000; // ms
        test_unit_is_pass=exception_string.empty()&&__Test::test_errors.empty();
        std::cout<<"[TEST] "<<__Test::test_names[index]
            <<" ["<<(test_unit_is_pass?"PASS":"FAIL")<<"] ("<<duration<<" ms)\n";
        std::cout<<"case:"<<__Test::test_unit_case_count<<","
            <<"pass:"<<__Test::test_unit_case_pass_count<<","
            <<"fail:"<<__Test::test_unit_case_fail_count<<","
            <<"jump:"<<__Test::test_unit_case_count-(
                __Test::test_unit_case_pass_count+__Test::test_unit_case_fail_count
            )<<".\n";
        for(size_t index=0;auto const& error:__Test::test_errors){
            std::cout<<" + <fail> "<<index<<"\n";
            std::cout<<error.what()<<"\n";
            ++index;
        }
        if(!exception_string.empty()){
            std::cout<<" + <fail> "<<__Test::test_errors.size()<<"\n"
                <<"\t<exce> "<<exception_string<<"\n";
        }
        exception_string.clear();
        __Test::test_errors.clear();
        if(test_unit_is_pass){
            ++__Test::test_unit_pass_count;
        }else{
            ++__Test::test_unit_fail_count;
        }
    }
    std::cout<<"[TOTAL]\n";
    std::cout<<"unit:"<<__Test::test_unit_count<<","
        <<"pass:"<<__Test::test_unit_pass_count<<","
        <<"fail:"<<__Test::test_unit_fail_count<<".\n";
}
void __Test::throw_error(std::runtime_error const& error){
    __Test::test_errors.push_back(error);
}
#define __TEST_ADD(__FUNC_NAME__) \
    static bool __test_flag_##__FUNC_NAME__= \
    __Test::add(#__FUNC_NAME__,std::function<void()>{__FUNC_NAME__}) \
//
#define TEST_UNIT(__FUNC_NAME__) \
    static void __FUNC_NAME__(); \
    __TEST_ADD(__FUNC_NAME__); \
    void __FUNC_NAME__() \
//
#define __TEST_THROW_ERROR(__INFO__) do { \
    __Test::throw_error(std::runtime_error( \
        "\t<file> "+std::string(__FILE__)+"\n" \
        "\t<line> "+std::to_string(__LINE__)+"\n" \
        "\t<func> "+std::string(__func__)+"\n" \
        "\t<info> "+__INFO__ \
    )); \
}while(0) \
//
#define TEST_CASE(...) do{ \
    ++__Test::test_unit_case_count; \
    if(!(__VA_ARGS__)){ \
        ++__Test::test_unit_case_fail_count; \
        __TEST_THROW_ERROR(#__VA_ARGS__); \
    }else{ \
        ++__Test::test_unit_case_pass_count; \
    } \
}while(0) \
//
#define TEST_RUN() do{ \
    __Test::run(); \
}while(0) \
//
#endif//__TEST_HPP__