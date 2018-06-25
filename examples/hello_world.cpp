#include "../src/CSLabel.hpp"
#include "../src/CSTextField.hpp"
#include "../src/CSTableView.hpp"
#include "../src/CSAlignView.hpp"
#include "../src/CSRect.hpp"
#include "../src/CSWindow.hpp"
#include "../src/CSApp.hpp"

#include <iostream>

#if defined(CS_Mac)
#import <AppKit/AppKit.h>
#elif defined(CS_Win)
#endif

class DataSource : public CSTableViewDataSource {
public:
    virtual int numberOfRows() { return 3; }
    virtual int numberOfColumns() { return 1; }
    virtual std::string getColumnName(int index) { return "Column"; }
    virtual bool isReadOnly() { return false; }
    virtual std::string getStringValueInCell(std::string col, int row) { return std::to_string(row); }
    virtual void setStringValueInCell(std::string col, int row, std::string value) { std::cerr << "(" << col << "," << row << ")" << value << std::endl; }
    virtual bool canDragFromRow(int row) { return true; }
    virtual bool canDropIntoRow(int row) { return true; }
    virtual std::string dragStringValueFromRow(int row) { return "Dragged"; }
    virtual void dropStringValueInRow(int row, std::string value) { std::cerr << value << std::endl; }
};

#if defined(CS_Win)
[System::STAThread]
#endif
int main() {
    CSApp::Init();

    CSLabel* label = new CSLabel("label");

    CSTextField* text = new CSTextField();
    text->setText("field");
    text->setCallback([](std::string str){ std::cout << str << std::endl; return true; });

    CSTableViewDataSource* dataSource = new DataSource();
    CSTableView* table = new CSTableView();
    table->setDataSource(dataSource);
    table->addColumn("Column");

    CSAlignView* align = new CSAlignView(CSAlignView::Direction::Horizontal);
    align->addView(label, false);
    align->addView(text, true);

    CSMenuBar* menuBar = new CSMenuBar("");
    CSSubMenu* subMenu = new CSSubMenu("SubMenu");
    subMenu->addItem(new CSMenuItem(new CSMenu<false>("Item"), CSKeyCode(), [](){ std::cerr << "Click Item" << std::endl; }));
    menuBar->addItem(new CSMenuItem(subMenu, CSKeyCode(), [](){ std::cerr << "Click SubMenu" << std::endl; }));

    CSRect size = CSRect(0, 0, 500, 500);
    CSWindow* window = new CSWindow(size,
                                    "Window",
                                    true,
                                    true
                                    );
    label->setWidth(50);
    window->presentView(table, menuBar);
    window->show();
    CSApp::Run();
}
