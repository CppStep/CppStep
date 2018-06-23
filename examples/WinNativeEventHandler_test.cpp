#include "../WinNativeEventHandler.hpp"
#include <string>

ref class A {
public:
    virtual property System::String^ Prop1 {
        virtual System::String^ get() {
            return "Hello";
        }
    }
    virtual property System::String^ Prop2 {
        virtual System::String^ get() {
            return "World";
        }
    }
};

void f(std::string str1, std::string str2) {
    std::cout << str1 << " " << str2 << std::endl;
}

int main() {
    auto a = gcnew A();
    callFunctionOnObject<void, std::string, std::string>(f, a, gcnew PropertyNames<std::string, std::string>("Prop1", gcnew PropertyNames<std::string>("Prop2")));
}
