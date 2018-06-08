#include "../CSLabel.hpp"
#include "../CSRect.hpp"
#include "../CSWindow.hpp"
#include "../CSApp.hpp"

#include <iostream>

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#endif

int main() {
    CSLabel* label = new CSLabel("Hello World");
    CSRect size = {500, 500, 500, 500};
    CSWindow* window = new CSWindow(label,
                                    size,
                                    "Window",
                                    true,
                                    true
                                    );
    CSAppRun();
}
