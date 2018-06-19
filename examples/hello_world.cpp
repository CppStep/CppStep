#include "../CSLabel.hpp"
#include "../CSTextField.hpp"
#include "../CSTableView.hpp"
#include "../CSAlignView.hpp"
#include "../CSRect.hpp"
#include "../CSWindow.hpp"
#include "../CSApp.hpp"

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
};

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

    CSRect size = CSRect(0, 0, 500, 100);
    CSWindow* window = new CSWindow(size,
                                    "Window",
                                    true,
                                    true
                                    );
    label->setWidth(50);
    window->presentView(text);
    CSApp::Run();
}
