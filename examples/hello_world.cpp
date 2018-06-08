#define CS_Win

#include "../CSLabel.hpp"
#include "../CSWindow.hpp"

#include <iostream>

int main() {
    CSLabel* label = new CSLabel("Hello World");
    CSWindow* window = new CSWindow(label,
                                    {100, 100, 100, 100},
                                    "Window",
                                    true,
                                    true
                                    );
    System::Windows::Forms::Application::Run();
}
