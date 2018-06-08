#include "../CSLabel.hpp"
#include "../CSRect.hpp"
#include "../CSWindow.hpp"

#include <iostream>

#import <AppKit/AppKit.h>

int main() {
#if defined(CS_Mac)
//    NSApplication* app = [NSApplication sharedApplication];
#elif defined(CS_Win)
#endif

    CSLabel* label = new CSLabel("Hello World");
    CSRect size = {500, 500, 500, 500};
    CSWindow* window = new CSWindow(label,
                                    size,
                                    "Window",
                                    true,
                                    true
                                    );
#if defined(CS_Mac)
    [[NSApplication sharedApplication] run];
#elif defined(CS_Win)
    System::Windows::Forms::Application::Run();
#endif
}
