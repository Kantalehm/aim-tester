#include "settings.h"

settings::settings()
{
    QGridLayout *setting_layout = new QGridLayout;

    edit_target_count = new QLineEdit;
    edit_target_count->setValidator(new QIntValidator(1, 9999, this));

    slider_size = new QSlider;
    slider_size->setRange(16, 256);

    this->setLayout(setting_layout);

}
