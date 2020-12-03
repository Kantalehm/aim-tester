#include "settings2.h"

Settings2::Settings2()
{

    // Title "Settings"
    title = new QLabel("Settings");
    title->setFont(QtUtils::title_font);

    // "Dark theme" checkbox
    dark_theme = new QCheckBox("Dark theme");

    // Test Mode selection
    mode_selection = new QGroupBox("Test mode selection");
    mode_selection_group = new QButtonGroup;
    fixed_target_count_mode = new QRadioButton("Fixed target count mode");
    fixed_time_mode_1 = new QRadioButton("Fixed time mode 1");
    fixed_time_mode_2 = new QRadioButton("Fixed time mode 2");
    endless_mode = new QRadioButton("Endless mode");
    mode_selection_group->addButton(fixed_target_count_mode, 0);
    mode_selection_group->addButton(fixed_time_mode_1, 1);
    mode_selection_group->addButton(fixed_time_mode_2, 2);
    mode_selection_group->addButton(endless_mode, 3);

    // Test Mode description
    mode_description = new QLabel;
    mode_description->setTextFormat(Qt::RichText);
    mode_description->setWordWrap(true);


    // General Settings
    screen_res_label = new QLabel("Test screen dimensions: ");
    screen_res = new QComboBox;
    res_map = {
        {"640x480 (4:3)", std::pair<int, int>(640, 480)},
        {"800x600 (4:3)", std::pair<int, int>(800, 600)},
        {"1024x576 (16:9)", std::pair<int, int>(1024, 576)},
        {"1280x720 (16:9)", std::pair<int, int>(1280, 720)},
        {"1366x768 (16:9)", std::pair<int, int>(1366, 768)},
        {"1600x900 (16:9)", std::pair<int, int>(1600, 900)},
        {"1920x1080 (16:9)", std::pair<int, int>(1920, 1080)},
        {"2560x1440 (16:9)", std::pair<int, int>(2560, 1440)},
        {"3840x2160 (16:9)", std::pair<int, int>(3840, 2160)},
    };
    for (int i = 0; i < res_map.count(); i++)
    {
        screen_res->addItem(res_map.keys()[i]);
    }

    target_size_label = new QLabel("Target size: ");
    target_size_px = new QLabel;
    target_size = new QSlider;
    target_size->setRange(16, 256);
    target_size->setOrientation(Qt::Horizontal);

    target_renderer = new QLabel;
    target_pixmap = QPixmap(QtUtils::FilePath("target.png"));
    target_renderer->setPixmap(target_pixmap.scaled(s_target_size, s_target_size));


    // Specific Settings
    target_mode_box = new QGroupBox;
    time_mode_box = new QGroupBox;
    endless_mode_box = new QGroupBox;
    target_count_label = new QLabel("Target count: ");
    target_count = new QSpinBox;
    target_count->setMinimum(1);
    target_count->setMaximum(10000);

    time_limit_label = new QLabel("Time limit (sec): ");
    time_limit = new QSpinBox;
    time_limit->setMinimum(3);
    time_limit->setMaximum(3600);

    life_count_label = new QLabel("Life count: ");
    life_count = new QSpinBox;
    life_count->setMinimum(0);
    life_count->setMaximum(50);

    // Bottom Buttons
    ok = new QPushButton("OK");
    ok->setFont(QtUtils::button_font);
    apply = new QPushButton("Apply");
    apply->setFont(QtUtils::button_font);
    cancel = new QPushButton("Cancel");
    cancel->setFont(QtUtils::button_font);

    AssignLayouts();
    MakeConnections();
    SetDefault();

}

void Settings2::AssignLayouts()
{
    /// Organizing Mode selection buttons layout
    mode_selection_layout = new QGridLayout;
    mode_selection_layout->addWidget(fixed_target_count_mode, 0, 0);
    mode_selection_layout->addWidget(endless_mode, 0, 1);
    mode_selection_layout->addWidget(fixed_time_mode_1, 1, 0);
    mode_selection_layout->addWidget(fixed_time_mode_2, 1, 1);
    mode_selection->setLayout(mode_selection_layout);

    /// Organizing General settings layout
    general_settings = new QGridLayout;
    general_settings->addWidget(screen_res_label, 0, 0);
    general_settings->addWidget(screen_res, 0, 1);
    general_settings->addWidget(target_size_label, 1, 0);
    general_settings->addWidget(target_size, 1, 1);
    general_settings->addWidget(target_size_px, 1, 2);
    general_settings->addWidget(target_renderer, 2, 0, 1, 3);
    general_settings->setAlignment(target_size_px, Qt::AlignRight);
    general_settings->setColumnStretch(0, 5);
    general_settings->setColumnStretch(1, 3);
    general_settings->setColumnStretch(2, 2);
    general_settings->setRowMinimumHeight(2, 256);
    general_settings->setAlignment(target_renderer, Qt::AlignCenter);

    /// Organizing Specific settings layouts

    specific_settings_layout = new QStackedLayout;

    target_mode_settings = new QGridLayout;
    target_mode_settings->addWidget(target_count_label, 0, 0);
    target_mode_settings->addWidget(target_count, 0, 1);
    target_mode_box->setLayout(target_mode_settings);

    time_mode_settings = new QGridLayout;
    time_mode_settings->addWidget(time_limit_label, 0, 0);
    time_mode_settings->addWidget(time_limit, 0, 1);
    time_mode_box->setLayout(time_mode_settings);

    endless_mode_settings = new QGridLayout;
    endless_mode_settings->addWidget(life_count_label, 0, 0);
    endless_mode_settings->addWidget(life_count, 0, 1);
    endless_mode_box->setLayout(endless_mode_settings);

    specific_settings_layout->addWidget(target_mode_box);
    specific_settings_layout->addWidget(time_mode_box);
    specific_settings_layout->addWidget(endless_mode_box);

    /// Organizing Bottom-page buttons layout
    bottom_buttons = new QHBoxLayout;
    bottom_buttons->addWidget(cancel);
    bottom_buttons->addWidget(apply);
    bottom_buttons->addWidget(ok);

    /// Organizing Settings page Layout
    settings_layout = new QVBoxLayout;

    settings_layout->addWidget(title);
    settings_layout->setAlignment(title, Qt::AlignHCenter);

    settings_layout->addWidget(dark_theme);

    settings_layout->addWidget(mode_selection);

    settings_layout->addWidget(mode_description);

    settings_layout->addLayout(specific_settings_layout);

    settings_layout->addLayout(general_settings);

    settings_layout->addLayout(bottom_buttons);

    this->setLayout(settings_layout);
}

void Settings2::MakeConnections()
{
    connect(mode_selection_group, SIGNAL(idClicked(int)), this, SLOT(ChangeSpecificSettings(int)));

    connect(target_size, SIGNAL(valueChanged(int)), this, SLOT(ChangeTargetSize(int)));

    connect(ok, SIGNAL(clicked()), this, SLOT(OK()));
    connect(apply, SIGNAL(clicked()), this, SLOT(Apply()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(Cancel()));
}

void Settings2::SetDefault()
{
    dark_theme->setChecked(true);

    fixed_target_count_mode->setChecked(true);


    target_count->setValue(s_target_count);
    time_limit->setValue(s_time_limit);
    life_count->setValue(s_life_count);

    ChangeSpecificSettings(s_mode_id);

    target_size->setValue(s_target_size);
    ChangeTargetSize(target_size->value());
    screen_res->setCurrentIndex(1);

    apply->setEnabled(false);
}

void Settings2::ChangeSpecificSettings(int id)
{
    ChangeModeDescription(id);
    switch(id)
    {
        case 0:
            specific_settings_layout->setCurrentIndex(0);
            break;
        case 1:
        case 2:
            specific_settings_layout->setCurrentIndex(1);
            break;
        case 3:
            specific_settings_layout->setCurrentIndex(2);
            break;
        default:
            break;

    }
}

void Settings2::ChangeModeDescription(int id)
{
    switch(id)
    {
        case 0:
            mode_description->setText("In <b>Fixed target count mode</b>, you will have a fixed amount of target "
                                      "showing up, one after another. You will have <b>1</b> click per target, "
                                      "which means even if you miss the target, another one will show up (and the "
                                      "previous will disappear.");
            break;
        case 1:
            mode_description->setText("In <b>Fixed time mode 1</b>, the test works quite like the Fixed target "
                                      "count mode, except you will have to hit as many targets as possible in "
                                      "a given time.");
            break;
        case 2:
            mode_description->setText("In <b>Fixed time mode 2</b>, you will have to hit as many target as possible "
                                      "in a given time, but you will have to <b>hit</b> the target to make the next "
                                      "one show up.");
            break;
        case 3:
            mode_description->setText("In <b>Endless mode</b>, you will have unlimited targets showing up one "
                                      "after another. The objective is to hit every single one of them without "
                                      "ever missing one. Missing a target will result in losing one life. The test "
                                      "stops when you run out of lives and you miss a target.");
            break;
        default:
            break;
    }

    apply->setEnabled(true);
}

void Settings2::ChangeTargetSize(int size)
{
    int even_size = size - size%2;
    target_renderer->setPixmap(target_pixmap.scaled(even_size, even_size));
    target_size_px->setText(QString::number(even_size) + " px");

    apply->setEnabled(true);
}

void Settings2::Cancel()
{
    // Resetting settings

    this->close();
}

void Settings2::Apply()
{
    // Applying settings

    apply->setEnabled(false);
}

void Settings2::OK()
{
    Apply();
    this->close();
}
