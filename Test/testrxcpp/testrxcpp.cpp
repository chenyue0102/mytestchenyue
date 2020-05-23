// testrxcpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <rxcpp/rx.hpp>
#include <condition_variable>
#include <mutex>
#include <thread>

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
std::mutex console_mutex;
void CTDetails(int val = 0) {
    console_mutex.lock();
    std::cout << "Current Thread id => "
        << std::this_thread::get_id()
        << val
        << std::endl;
    console_mutex.unlock();
}
void test9()
{
    std::cout << "main thread:" << std::this_thread::get_id() << std::endl;
    serialize_one_worker coordination = rxcpp::serialize_new_thread();
    rxsc::worker worker = coordination.create_coordinator().get_worker();
    auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(50)).
        take(5).
        replay(coordination);
    worker.schedule([&](const rxcpp::schedulers::schedulable & schedulable) 
        {
            values.subscribe([](long v) {CTDetails(v); }, []() {CTDetails(); });
        });
    worker.schedule(coordination.now() + std::chrono::microseconds(125), [&](const rxcpp::schedulers::schedulable& schedulable)
        {
            values.subscribe([](long v) {CTDetails(v); }, []() {CTDetails(); });
        });
    worker.schedule([&](const rxcpp::schedulers::schedulable&) {values.connect(); });
    getchar();
}

std::mutex g_mtx;
std::condition_variable g_cv;
std::vector<std::function<void()>> g_funs;
void doProcess()
{
    std::cout << "doProcess threadid:" << std::this_thread::get_id() << std::endl;
    while (true)
    {
        std::unique_lock<std::mutex> lk(g_mtx);
        g_cv.wait(lk, [&]() {return !g_funs.empty(); });
        std::vector<std::function<void()>> funs = std::move(g_funs);
        lk.unlock();
        for (auto& fun : funs)
        {
            fun();
        }
    }
}

void insertfun(std::function<void()> fun)
{
    std::lock_guard<std::mutex> lk(g_mtx);
    g_funs.push_back(fun);
    g_cv.notify_one();
}

void testxx(std::function<void()> fun)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    fun();
}

void test10()
{
    std::cout << "main thread:" << std::this_thread::get_id() << std::endl;
    std::thread t(&doProcess);
    rxcpp::schedulers::run_loop rlp;
    auto mainthread = rxcpp::observe_on_run_loop(rlp);
    auto workthread = rxcpp::synchronize_new_thread();
    auto ob = rxcpp::observable<>::create<std::string>([](rxcpp::subscriber<std::string> s)
        {
            std::cout << "subscriber" << std::this_thread::get_id() << std::endl;
            insertfun([=]() {
                s.on_next("abc123");
                s.on_completed();
                });
        });
    rxcpp::composite_subscription scr;
    auto sub = rxcpp::make_subscriber<std::string>(scr, [](const std::string& text)
        {
            std::cout << "threadid:" << std::this_thread::get_id() << " text:" << text << std::endl;
        }, []() {
            std::cout << "threadid:" << std::this_thread::get_id() << " complete" << std::endl;
        });
    ob.subscribe_on(workthread).observe_on(mainthread).subscribe(sub);
    ob.subscribe_on(workthread).observe_on(mainthread).subscribe([](const std::string& text) {
            std::cout << "threadid2:" << std::this_thread::get_id() << " text:" << text << std::endl;
        }, []() {
            std::cout << "threadid2:" << std::this_thread::get_id() << " complete" << std::endl;
        });

    while (scr.is_subscribed() || !rlp.empty()) {
        while (!rlp.empty() && rlp.peek().when < rlp.now()) {
            rlp.dispatch();
        }
    }
    t.join();
}
int main()
{
    test10();
    return 0;
}

;