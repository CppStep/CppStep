#include "CSLabel.hpp"
#include "CSWindow.hpp"

int main() {
    CSLabel* label = new CSLabel("Hello World");
    CSWindow* window = new CSWindow(label,
                                    {100, 100, 100, 100},
                                    "Window",
                                    true,
                                    true
                                    );
    for (;;)
}
