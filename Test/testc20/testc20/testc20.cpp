// testc20.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <utility>
#include <functional>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <ranges>
#include <coroutine>
#include <future>
#include <thread>
#include <chrono>
#include <optional>
#include <assert.h>

struct Value
{
public:
    Value()
    {
        std::cout << "value" << std::endl;
    }
    ~Value()
    {
        std::cout << "~value" << std::endl;
    }
    std::vector<int> v;
};

void fun(const Value& a){
    std::cout << "fun1" << std::endl;
}

void fun(Value&& a){
    std::cout << "fun2" << std::endl;
}

Value getvalue()
{
    return Value();
}
Value ccb = Value();
using T1 = decltype(ccb);
using T2 = decltype((ccb));
void t1(T1 c)
{

}

void t2(T2 c)
{

}

struct Test {
public:
    Test(int a)
    {
        
    }
    int add()
    {
        return 1;
    }
};

using T4 = decltype((std::declval<Test>().add()));
void test4(T4 t)
{

}

using TT1 = decltype(std::declval<int>());
void testtt1(TT1 t1) {

}

template<typename T>
class TestAdd
{
public:
    TestAdd()
    {

    }
    T add(T t1, T t2)
    {
        return t1 + t2;
    }
};

template<typename T>
T myadd(T t1, T t2)
{
    if constexpr (std::is_integral<T>::value)
    {
        return t1 + t2;
    }
    else
    {
        return t1 - t2;
    }
}

template<typename T, typename = void>
struct HasMember : public std::false_type
{

};

template<typename T>
struct HasMember<T , std::void_t<typename T::type>> : public std::true_type
{

};

consteval int getdouble(int a)
{
    return a * 2;
}

void testcall(int)
{

}

template<typename T>
void testcall(T)
{

}

struct TestStarShip
{
    TestStarShip(int a)
        : value(a)
    {

    }
    bool operator==(const TestStarShip& other)const = default;
    std::strong_ordering operator<=>(const TestStarShip& other)const
    {
        if (value == other.value)
        {
            return std::strong_ordering::equivalent;
        }
        else if (value < other.value) {
            return std::strong_ordering::less;
        }
        else
        {
            return std::strong_ordering::greater;
        }
    }

    int value;

};

constexpr int testconst(int a)
{
    if (std::is_constant_evaluated())
    {
        return a + 1;
    }
    else
    {
        return a;
    }
}
constinit int kc2 = testconst(1);

struct empty_coroutine
{

};

struct Future {
    
    struct promise_type {
        template<typename T>
        promise_type(T &&t) {
            std::cout << "promise_type1" << std::endl;
        }
        promise_type(int n) {
            std::cout << "promise_type2" << std::endl;
        }
        promise_type() {
            std::cout << "promise_type3" << std::endl;
        }
        auto get_return_object() {
            std::cout << "get_return_object" << std::endl;
            return Future();
        }
        auto initial_suspend() noexcept {
            std::cout << "initial_suspend" << std::endl;
            return std::suspend_always();
        }
        auto final_suspend() noexcept {
            std::cout << "final_suspend" << std::endl;
            return std::suspend_always();
        }
        void unhandled_exception() {
            std::terminate();
        }
        void return_void() {
            std::cout << "return_void" << std::endl;
        }
    };

};
struct Class {
    Future member_coro(int) {
        co_return;
    }
};
Future test_coor(int a) {
    co_return;
}

//struct MyFuture {
//    struct Awaiter {
//        std::optional<std::string>& result;
//        Awaiter(std::optional<std::string> &_r):result(r){
//            std::cout << "Awaiter move" << std::endl;
//        }
//        bool await_ready() {
//            std::cout << "await_ready" << std::endl;
//            return result.has_value();
//        }
//        void await_suspend(std::coroutine_handle<> h) {
//            std::cout << "await_suspend" << std::endl;
//        }
//        std::string await_resume() {
//            std::cout << "await_resume" << std::endl;
//            return result.value();
//        }
//    };
//
//    struct promise_type : std::promise<std::string> {
//        std::optional<std::string> result;
//
//        template<typename T>
//        promise_type(T&& t) {
//            std::cout << "promise_type1" << std::endl;
//        }
//        promise_type() {
//            std::cout << "promise_type2" << std::endl;
//        }
//        MyFuture::Awaiter await_transform(std::future<std::string> f) {
//            return { std::move(f) };
//        }
//        auto get_return_object() {
//            std::cout << "get_return_object" << std::endl;
//            //return future();
//            //return std::coroutine_handle<promise_type>::from_promise(*this);
//            return await_transform(this->get_future());
//        }
//        auto initial_suspend() noexcept {
//            std::cout << "initial_suspend" << std::endl;
//            return std::suspend_always();
//        }
//        auto final_suspend() noexcept {
//            std::cout << "final_suspend" << std::endl;
//            return std::suspend_always();
//        }
//        void unhandled_exception() {
//            std::terminate();
//        }
//        template<typename U>
//        void return_value(U&& u) {
//            std::cout << "return_value" << std::endl;
//            //set_value(std::forward<U>(u));
//        }
//    };
//};

std::future<std::string> gettext(std::string a) {
    std::cout << "enter gettext" << std::endl;
    std::shared_ptr<std::promise<std::string>> pp = std::make_shared<std::promise<std::string>>();
    std::thread t = std::thread([pp,a]() {
        std::cout << "gettext" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pp->set_value(a + "123");
    });
    t.detach();
    return pp->get_future();
}

template<typename Future>
class coroutine_base {
    Future& get_future() { return static_cast<Future&>(*this); }
protected:
    using suspend_never = std::suspend_never;
    using suspend_always = std::suspend_always;
    template<typename... U>
    using coroutine_handle = std::coroutine_handle<U...>;

    template<typename Promise>
    struct promise_base_type {
        auto initial_suspend() { return suspend_never{}; }
        auto final_suspend() noexcept { return suspend_always{}; }
        Future get_return_object() {
            return coroutine_handle<Promise>::from_promise(static_cast<Promise&>(*this));
        }
        void unhandled_exception() { std::terminate(); }
    };

    void resume() { if (!get_future().co_handle_.done()) get_future().co_handle_.resume(); }

public:
    ~coroutine_base() { get_future().co_handle_.destroy(); }

};


template<typename Signal, typename Result>
struct StateMachine : coroutine_base<StateMachine<Signal, Result>> {
    struct promise_type :
        coroutine_base<StateMachine>::
        template promise_base_type<promise_type> {
        std::optional<Result> res_;
        std::optional<Signal> recent_signal_;

        void return_value(Result res) { res_ = res; };

        struct SignalAwaiter {
            std::optional<Signal>& recent_signal_;
            SignalAwaiter(std::optional<Signal>& signal) :
                recent_signal_(signal) {}

            bool await_ready() { return recent_signal_.has_value(); }
            void await_suspend(std::coroutine_handle<>) {}
            Signal await_resume() {
                assert(recent_signal_.has_value());
                Signal sig = *recent_signal_;
                recent_signal_.reset();
                return sig;
            }
        };

        struct signal {
            signal()
            {
                std::cout << "signal" << std::endl;
            }
        };
        SignalAwaiter await_transform(signal) {
            return SignalAwaiter{ recent_signal_ };
        }
    };

    using signal = typename promise_type::signal;

    StateMachine(std::coroutine_handle<promise_type> coroutine) :
        co_handle_(coroutine) {}

    void send_signal(Signal signal) {
        co_handle_.promise().recent_signal_ = signal;
        if (!co_handle_.done()) co_handle_.resume();
    }

    std::optional<Result> get_result() {
        return co_handle_.promise().res_;
    }

    std::coroutine_handle<promise_type> co_handle_;
};

enum class ButtonPress {
    LEFT_MOUSE,
    RIGHT_MOUSE
};

StateMachine<ButtonPress, std::FILE*> open_file(const char* file_name) {
    using ThisCoroutine = StateMachine<ButtonPress, std::FILE*>;
    std::cout << "open_file1" << std::endl;
    ButtonPress first_press = co_await ThisCoroutine::signal{};
    while (true) {
        std::cout << "open_file2" << std::endl;
        ButtonPress second_press = co_await ThisCoroutine::signal{};
        if (first_press == second_press &&
            first_press == ButtonPress::LEFT_MOUSE) {
            std::cout << "open_file return" << std::endl;
            co_return std::fopen(file_name, "r");
        }
        first_press = second_press;
    }
}

void testm() {
    StateMachine<ButtonPress, std::FILE*> machine = open_file("/dev/zero");
    std::cout << "test_coroutine1" << std::endl;
    machine.send_signal(ButtonPress::LEFT_MOUSE);
    std::cout << "test_coroutine2" << std::endl;
    machine.send_signal(ButtonPress::RIGHT_MOUSE);
    std::cout << "test_coroutine3" << std::endl;
    machine.send_signal(ButtonPress::LEFT_MOUSE);
    std::cout << "test_coroutine4" << std::endl;
    machine.send_signal(ButtonPress::LEFT_MOUSE);

    std::cout << "machine done: " << machine.co_handle_.done() << std::endl;
    auto result = machine.get_result();
    std::cout << "machine result: " << result.has_value() << std::endl;
    if (result.has_value()) { std::fclose(*result); }
}

struct TestCoroutine {
    struct Awaiter {
        Awaiter(std::list<std::string>&_r, std::string _l):r(_r), l(_l) {

        }
        bool await_ready() {
            return !r.empty();
        }
        std::string await_resume() {
            std::string tmp = r.front();
            r.pop_front();
            return l + tmp;
        }
        void await_suspend(std::coroutine_handle<>) {

        }
        std::list<std::string>& r;
        const std::string l;
    };
    struct InputValue {
        std::string inputValue;
    };

    
    struct promise_type {
        std::list<std::string> result;
        std::string total_result;
        TestCoroutine* tc;

        promise_type() {
            tc = new TestCoroutine(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        void setResult(std::string s) {
            result.push_back(s);
            if (!tc->co_handle_.done()) {
                tc->co_handle_.resume();
            }
        }

        auto initial_suspend() {
            return std::suspend_never();
        }

        auto final_suspend()noexcept {
            return std::suspend_always();
        }

        Awaiter await_transform(InputValue s) {
            return Awaiter(result, s.inputValue);
        }

        TestCoroutine get_return_object() {
            return *tc;
            //return std::coroutine_handle<promise_type>::from_promise(*this);
        }

        void return_value(std::string b) {
            total_result = b;
            return;
        }

        std::string get_result() {
            return total_result;
        }

        void unhandled_exception() {
            std::terminate();
        }
    };

    std::coroutine_handle<promise_type> co_handle_;
    TestCoroutine(std::coroutine_handle< promise_type> coroutine):co_handle_(coroutine){
        std::cout << "TestCoroutine" << std::endl;
    }
};

TestCoroutine mytestc(std::string s) {
    std::string str1 = co_await TestCoroutine::InputValue(s);
    std::string str2 = co_await TestCoroutine::InputValue(str1);
    co_return str2;
}

void testc() {
    TestCoroutine tc = mytestc("abc");
    tc.co_handle_.promise().setResult("123");
    if (tc.co_handle_.done()) {
        std::cout << "done" << std::endl;
    }
    else {
        std::cout << "not done" << std::endl;
    }
    tc.co_handle_.promise().setResult("456");
    if (tc.co_handle_.done()) {
        std::cout << "done" << std::endl;
    }
    else {
        std::cout << "not done" << std::endl;
    }
    std::cout << "total result:" << tc.co_handle_.promise().get_result() << std::endl;
}

std::coroutine_handle g_h;
void test_coroutine()
{
    testc();
    testm();

    empty_coroutine c;
    //Class obj;
    //auto f1 = obj.member_coro(0);
    //auto f2 = test_coor(1);
   /* auto f3 = test_coro1("abc");
    if (!f3.await_ready()) {
        f3.await_suspend(g_h);
    }
    std::string s = f3.mf.get();
    int a;*/
    //scanf("%d", &a);
}
int main()
{
    test_coroutine();
    auto rr = std::views::iota(1)
        | std::views::transform([](auto n) {return n * n; })
        | std::views::filter([](auto n) {return (n % 2) == 0; })
        | std::views::take_while([](auto n) {return n < 20; });
    for (auto it = rr.begin();
        it != rr.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::vector<int> v = { 1,2,3,4,5 };

    int kc = testconst(1);
    
    TestStarShip ts1(1), ts2(2), ts11(1);
    if (ts1 <= ts2)
    {
        std::cout << "less";
    }
    auto tsb = ts2 < ts1;
    if (ts2 < ts1)
    {
        std::cout << "greater";
    }
    if (ts1 == ts2)
    {
        std::cout << "equal";
    }
    testcall(1);
    testcall(1.0);
    testcall((long)1);
    constexpr bool hasmem1 = HasMember<int>::value;
    constexpr bool hasmem2 = HasMember<std::true_type>::value;
    constexpr int getd = getdouble(90);
    testtt1(1);
    myadd(1, 2);
    myadd(1.0, 2.0);
    constexpr bool isClass = std::is_class<TestAdd<int>>::value;
    TestAdd<int> testAdd = TestAdd<int>();
    auto ff2 = [&testAdd](int b) {return testAdd.add(5, b); };
    auto ff = std::bind(&TestAdd<int>::add, &testAdd, 5, std::placeholders::_1);
    int ret = ff(6);
    ret = ff2(6);
    int ck = 1;

    test4(ck);
    auto&& cb = ccb;
    t1(cb);
    t2(cb);
    Value a = {};
    Value& b = a;
    Value&& c = {};
    fun(a);
    fun(c);
    fun({});
    auto&& cc = getvalue();
    fun(cc);
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
