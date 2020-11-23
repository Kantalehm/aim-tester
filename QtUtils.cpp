#include "QtUtils.h"

QString QtUtils::FilePath(std::string filename)
{
    return QApplication::applicationDirPath() + "/" + QString::fromStdString(filename);
}
