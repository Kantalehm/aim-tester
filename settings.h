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
        QPixmap target_pixmap;
        QLabel *target_renderer;
        QPushButton *validate;
        QPushButton *cancel;

    public slots:
        void Validate();
        void Cancel();
        void ChangeTargetSize(int size);
};

#endif // SETTINGS_H
