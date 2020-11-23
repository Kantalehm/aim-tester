#ifndef SETTINGS_H
#define SETTINGS_H

#include "QtUtils.h"

class settings: public QDialog
{
    Q_OBJECT

    public:
        settings();
        int target_count = 15;
        int target_size = 64;

    private:
        QLineEdit *edit_target_count;
        QSlider *slider_size;
        QLabel *target_renderer;
};

#endif // SETTINGS_H
