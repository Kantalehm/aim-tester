#include <QApplication>
#include "clickHandler.h"
#include "homePage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // clickHandler clickHandler;
    //
    // clickHandler.show();

    homePage home_page;
    home_page.resize(640, 420);
    home_page.show();

    return app.exec();
}
