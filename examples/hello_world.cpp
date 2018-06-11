#include "../CSLabel.hpp"
#include "../CSTextField.hpp"
#include "../CSAlignView.hpp"
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
    CSLabel* label = new CSLabel("label");
    std::cerr << label->getWidth() << std::endl;
    CSTextField* text = new CSTextField();
    text->setText("field");
    CSAlignView* align = new CSAlignView(CSAlignView::Direction::Horizontal);
    align->addView(label, false);
    align->addView(text, true);
    CSRect size = CSRect(0, 0, 500, 100);
    CSWindow* window = new CSWindow(size,
                                    "Window",
                                    true,
                                    true
                                    );
    label->setWidth(50);
    window->presentView(align);
    CSApp::Run();
}
