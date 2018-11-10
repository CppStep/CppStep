#include "WinString.hpp"

std::string WinString::toStdString(System::String^ string) {
    return msclr::interop::marshal_as<std::string>(string);
}
msclr::gcroot<System::String^> WinString::toSysString(std::string string) {
    return gcnew System::String(string.c_str());
}
