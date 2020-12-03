#ifndef SETTINGS2_H
#define SETTINGS2_H

#include "QtUtils.h"

class Settings2 : public QDialog
{
    Q_OBJECT

    public:
        Settings2();
        int s_mode_id = 0;
        int s_target_size = 64;
        int s_target_count = 15;
        int s_life_count = 3;
        int s_time_limit = 30;
        std::pair<int, int> s_screen_res = std::pair<int, int>(1280, 720);


    private:
        QVBoxLayout *settings_layout;

        QLabel *title;
        QCheckBox *dark_theme;

        QGroupBox *mode_selection;
            QGridLayout *mode_selection_layout;
            QButtonGroup *mode_selection_group;
            QRadioButton *fixed_target_count_mode;
            QRadioButton *fixed_time_mode_1;
            QRadioButton *fixed_time_mode_2;
            QRadioButton *endless_mode;

        QLabel *mode_description;

        QGridLayout *general_settings;
            QLabel *screen_res_label;
            QComboBox *screen_res;
            QMap<QString, std::pair<int, int>> res_map;

            QLabel *target_size_label;
            QLabel *target_size_px;
            QSlider *target_size;
            QLabel *target_renderer;
            QPixmap target_pixmap;

        QStackedLayout *specific_settings_layout;
        QGroupBox *target_mode_box;
        QGroupBox *time_mode_box;
        QGroupBox *endless_mode_box;
            QGridLayout *target_mode_settings;
            QGridLayout *time_mode_settings;
            QGridLayout *endless_mode_settings;
            QLabel *target_count_label;
            QSpinBox *target_count;

            QLabel *time_limit_label;
            QSpinBox *time_limit;

            QLabel *life_count_label;
            QSpinBox *life_count;

        QHBoxLayout *bottom_buttons;
            QPushButton *ok;
            QPushButton *apply;
            QPushButton *cancel;


        void SetDefault();
        void MakeConnections();
        void AssignLayouts();

        void ChangeModeDescription(int id);


    public slots:
        void ChangeTargetSize(int size);
        void ChangeSpecificSettings(int id);
        void Cancel();
        void Apply();
        void OK();
};

#endif // SETTINGS2_H
