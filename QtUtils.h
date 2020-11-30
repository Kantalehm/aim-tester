#ifndef QTUTILS_H
#define QTUTILS_H

#include <QApplication>
#include <QtWidgets>

class QtUtils
{
    public:
        static QString FilePath(std::string filename);

        static QFont title_font;
        static QFont button_font;
        static QFont countdown_font;
        static QFont basic_font;


};

#endif // QTUTILS_H
