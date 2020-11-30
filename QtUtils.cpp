#include "QtUtils.h"

QString QtUtils::FilePath(std::string filename)
{
    return QApplication::applicationDirPath() + "/" + QString::fromStdString(filename);
}

QFont QtUtils::title_font = QFont("Lato", 20, QFont::Bold);
QFont QtUtils::button_font = QFont("Lato", 14);
QFont QtUtils::countdown_font = QFont("Lato", 80, QFont::Bold, true);
QFont QtUtils::basic_font = QFont("Lato", 9);
