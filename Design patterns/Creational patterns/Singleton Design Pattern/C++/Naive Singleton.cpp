#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class Singleton {
private:
    static Singleton * instance_;
    std::string value;
private:
    Singleton(std::string value): value(value) {}
public:
    // Singletons should not be cloneable.
    Singleton(Singleton &other) = delete;
    // Singletons should not be assignable.
    void operator=(const Singleton &) = delete;

    static Singleton *GetInstance(const std::string& value) {
        if (instance_ == nullptr) {
            instance_ = new Singleton(value);
        }
        return instance_;
    }

    std::string GetValue() const {
        return value;
    } 
};
 
Singleton* Singleton::instance_ = nullptr;;

void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->GetValue() << "\n";
}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->GetValue() << "\n";
}

int main() {
    std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n";   
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}