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
        std::pair<int, int> screen_res = std::pair<int, int>(600, 400);


    private:

        QButtonGroup *mode_selection;
        QGroupBox *mode_selection_group;
        QGridLayout *mode_selection_layout;
        QRadioButton *fixed_target_count_mode;
        QRadioButton *fixed_time_mode_1;
        QRadioButton *fixed_time_mode_2;
        QRadioButton *endless_mode;

        QLabel *dark_theme_label;
        QCheckBox *dark_theme;

        QLabel *screen_res_label;
        QLabel *target_count_label;
        QLabel *target_size_label;
        QLabel *target_px_label;

        QComboBox *screen_res_input;
        QMap<QString, std::pair<int, int>> res_map;
        QSpinBox *target_count_input;
        QSlider *target_size_slider;
        QPixmap target_pixmap;
        QLabel *target_renderer;
        QPushButton *validate;
        QPushButton *cancel;

        bool ScreenSizeOK();

    public slots:
        void Validate();
        void Cancel();
        void ChangeTargetSize(int size);
        void DisplaySize(int size);
        void ChangeTheme(int state);
};

#endif // SETTINGS_H
