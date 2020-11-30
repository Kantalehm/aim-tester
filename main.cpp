#include <QApplication>
#include "homePage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qApp->setStyle(QStyleFactory::create("Fusion"));

    // clickHandler clickHandler;
    //
    // clickHandler.show();

    homePage home_page;

    QPalette darkTheme;
    darkTheme.setColor(QPalette::Window,          QColor( 37,  37,  37));
    darkTheme.setColor(QPalette::WindowText,      QColor(212, 212, 212));
    darkTheme.setColor(QPalette::Base,            QColor( 60,  60,  60));
    darkTheme.setColor(QPalette::AlternateBase,   QColor( 45,  45,  45));
    darkTheme.setColor(QPalette::PlaceholderText, QColor(127, 127, 127));
    darkTheme.setColor(QPalette::Text,            QColor(212, 212, 212));
    darkTheme.setColor(QPalette::Button,          QColor( 45,  45,  45));
    darkTheme.setColor(QPalette::ButtonText,      QColor(212, 212, 212));
    darkTheme.setColor(QPalette::BrightText,      QColor(240, 240, 240));
    darkTheme.setColor(QPalette::Highlight,       QColor( 38,  79, 120));
    darkTheme.setColor(QPalette::HighlightedText, QColor(240, 240, 240));

    darkTheme.setColor(QPalette::Light,           QColor( 60,  60,  60));
    darkTheme.setColor(QPalette::Midlight,        QColor( 52,  52,  52));
    darkTheme.setColor(QPalette::Dark,            QColor( 30,  30,  30) );
    darkTheme.setColor(QPalette::Mid,             QColor( 37,  37,  37));
    darkTheme.setColor(QPalette::Shadow,          QColor( 0,    0,   0));

    darkTheme.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));

    qApp->setPalette(darkTheme);

    home_page.resize(640, 420);
    home_page.show();

    return app.exec();
}
