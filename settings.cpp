#include "settings.h"

settings::settings()
{
    QGridLayout *settings_layout = new QGridLayout;

    resize(300, 420);

    screen_res_label = new QLabel("Test screen resolution: ");
    screen_res_label->setFont(QtUtils::basic_font);
    target_count_label = new QLabel("Target count: ");
    target_count_label->setFont(QtUtils::basic_font);
    target_size_label = new QLabel("Target size: ");
    target_size_label->setFont(QtUtils::basic_font);
    target_px_label = new QLabel;
    target_px_label->setText(QString::number(target_size) + " px");
    target_px_label->setFont(QtUtils::basic_font);


    screen_res_input = new QComboBox;
    res_map = {
        {"640x480 (4:3)", std::pair<int, int>(640, 480)},
        {"800x600 (4:3)", std::pair<int, int>(800, 600)},
        {"1024x576 (16:9)", std::pair<int, int>(1024, 576)},
        {"1280x720 (16:9)", std::pair<int, int>(1280, 720)},
        {"1366x768 (16:9)", std::pair<int, int>(1366, 768)},
        {"1600x900 (16:9)", std::pair<int, int>(1600, 900)},
        {"1920x1000 (16:9)", std::pair<int, int>(1920, 1080)},
        {"2560x1440 (16:9)", std::pair<int, int>(2560, 1440)},
        {"3840x2160 (16:9)", std::pair<int, int>(3840, 2160)},
    };
    for (int i = 0; i < res_map.count(); i++)
    {
        screen_res_input->addItem(res_map.keys()[i]);
    }
    screen_res_input->setFont(QtUtils::basic_font);

    target_count_input = new QSpinBox;
    target_count_input->setValue(this->target_count);
    target_count_input->setFont(QtUtils::basic_font);

    target_size_slider = new QSlider;
    target_size_slider->setRange(16, 256);
    target_size_slider->setValue(this->target_size);
    target_size_slider->setPageStep(16);
    target_size_slider->setOrientation(Qt::Horizontal);

    target_pixmap = QPixmap(QtUtils::FilePath("target.png"));

    target_renderer = new QLabel;
    target_renderer->setPixmap(target_pixmap.scaled(target_size, target_size));

    validate = new QPushButton("&Validate");
    validate->setFont(QtUtils::button_font);
    cancel = new QPushButton("&Cancel");
    cancel->setFont(QtUtils::button_font);

    settings_layout->addWidget(screen_res_label, 0, 0);
    settings_layout->addWidget(screen_res_input, 0, 1, 1, 2);
    settings_layout->addWidget(target_count_label, 1, 0);
    settings_layout->addWidget(target_count_input, 1, 1, 1, 2);
    settings_layout->addWidget(target_size_label, 2, 0);
    settings_layout->addWidget(target_size_slider, 2, 1);
    settings_layout->addWidget(target_px_label, 2, 2);
    settings_layout->addWidget(target_renderer, 3, 0, 1, 3);
    settings_layout->addWidget(validate, 4, 0);
    settings_layout->addWidget(cancel, 4, 1, 1, 2);

    settings_layout->setAlignment(target_renderer, Qt::AlignHCenter);
    settings_layout->setAlignment(target_px_label, Qt::AlignRight);

    settings_layout->setColumnStretch(0, 9);
    settings_layout->setColumnStretch(1, 6);
    settings_layout->setColumnStretch(2, 3);

    connect(target_size_slider, SIGNAL(valueChanged(int)), this, SLOT(ChangeTargetSize(int)));
    connect(target_size_slider, SIGNAL(valueChanged(int)), this, SLOT(DisplaySize(int)));
    connect(validate, SIGNAL(clicked()), this, SLOT(Validate()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(Cancel()));

    this->setLayout(settings_layout);

}

void settings::Validate()
{
    if (!ScreenSizeOK())
    {
        QMessageBox *error = new QMessageBox;
        error->critical(0, "Invalid screen resolution.", "The test screen resolution you chose is larger than your screen resolution. \n"
                                                         "Please choose a resolution that fits your screen's.");
        return;
    }
    int width = std::min(res_map.value(screen_res_input->currentText()).first, QApplication::desktop()->availableGeometry().width());
    int height = std::min(res_map.value(screen_res_input->currentText()).second,
                          QApplication::desktop()->availableGeometry().height() - this->style()->pixelMetric(QStyle::PM_TitleBarHeight));
    this->screen_res = std::pair<int, int>(width, height);
    this->target_count = target_count_input->text().toInt();
    this->target_size = target_size_slider->value() - target_size_slider->value()%2;
    this->close();
}

void settings::Cancel()
{
    target_count_input->setValue(this->target_count);
    target_size_slider->setValue(this->target_size);
    this->close();
}

void settings::ChangeTargetSize(int size)
{
    this->target_renderer->setPixmap(this->target_pixmap.scaled(size, size));
}

void settings::DisplaySize(int size)
{
    this->target_px_label->setText(QString::number(size - size%2) + " px");
}

bool settings::ScreenSizeOK()
{
    if (res_map.value(screen_res_input->currentText()).first > QApplication::desktop()->screenGeometry().width())
    {
        return false;
    }
    if (res_map.value(screen_res_input->currentText()).second > QApplication::desktop()->screenGeometry().height())
    {
        return false;
    }
    return true;
}
