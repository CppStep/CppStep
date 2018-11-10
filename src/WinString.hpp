#ifndef WinString_hpp
#define WinString_hpp

#include <string>
#using <System.dll>
#include <msclr\gcroot.h>
#include <msclr\marshal_cppstd.h>

namespace WinString {
    std::string toStdString(System::String^ string);
    msclr::gcroot<System::String^> toSysString(std::string string);
}

#endif /* WinString_hpp */