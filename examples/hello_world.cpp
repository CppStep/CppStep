#include "../CSLabel.hpp"
#include "../CSTextField.hpp"
#include "../CSRect.hpp"
#include "../CSWindow.hpp"
#include "../CSApp.hpp"

#include <iostream>

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#endif

int main() {
    CSApp::Init();
    CSLabel* label = new CSLabel("Hello World");
    CSRect textSize = {400, 400, 400, 400};
    CSTextField* text = new CSTextField(textSize);
    text->setText("hello");
    CSRect size = {500, 500, 500, 500};
    CSWindow* window = new CSWindow(text,
                                    size,
                                    "Window",
                                    true,
                                    true
                                    );
    CSApp::Run();
}

