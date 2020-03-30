// testrxcpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <rxcpp/rx.hpp>

using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::util;

void test1()
{
    auto observable = rxcpp::observable<>::range(1, 12).
        filter([](int n) {return n % 2 == 0; }).map([](int n) {return n + 1; }).average();
    observable.subscribe([](int n) {printf("onNext=%d\n", n); },
        []() {printf("end\n"); });
}

void test2()
{
    auto ins = rxcpp::observable<>::create<int>([](rxcpp::subscriber<int> s) {
        printf("before next\n");
        s.on_next(1);
        printf("before completed\n");
        s.on_completed();
        printf("after completed\n");
        });
    ins.subscribe([](int n) {printf("onnext%d\n", n); },
        []() {printf("completed\n"); });
}

auto printfun = [](int n) {printf("onnext=%d\n", n); };
auto printcompleted = []() {printf("completed\n"); };

void test3()
{
    auto o1 = rxcpp::observable<>::range(1, 3);
    auto o2 = rxcpp::observable<>::range(4, 6);
    auto values = o1.concat(o2);
    auto values2 = o1.merge(o2);
    //auto values3 = o1.start_with(o2);
    values.subscribe(printfun, printcompleted);

    auto values4 = rxcpp::observable<>::just(2);
    values4.subscribe(printfun, printcompleted);
}
void test4()
{
    auto o1 = rxcpp::observable<>::range(1, 10);
    auto o2 = o1.take(3);
    o2.subscribe(printfun, printcompleted);
}

void test5()
{
    //终止
    auto sub = rxcpp::composite_subscription();
    auto values = rxcpp::observable<>::range(1, 10);
    values.subscribe(sub, [&sub](int n) {
        printf("onnext=%d\n", n); 
        if (n > 5)sub.unsubscribe(); },
        []() {printf("complete\n"); });
}

void test6() 
{
    auto values = rxcpp::observable<>::range(1, 10).
        scan(100, [](int seed, int n) {return seed / 2 + n; });
    values.subscribe(printfun, printcompleted);
}

void test7() 
{
    auto ints = rxcpp::observable<>::range(1, 10) | rxcpp::operators::map([](int n) {return n + 1; });
    ints.subscribe(printfun, printcompleted);
 }

void test8()
{
    std::cout << "main thread:"<< std::this_thread::get_id() << std::endl;
    auto values = rxcpp::observable<>::range(1, 10);
    values.observe_on(rxcpp::synchronize_new_thread()).subscribe([](int n) {
        std::cout << "threadid:" << std::this_thread::get_id()<<" n:" << n << std::endl;
        }, []() {std::cout << "threadid:" << std::this_thread::get_id() << " complete" << std::endl; });
    std::cout << "main thread:end" << std::endl;
    getchar();
}
int main()
{
    test8();
    return 0;
}

