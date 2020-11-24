#include "settings.h"

settings::settings()
{
    QGridLayout *setting_layout = new QGridLayout;

    resize(640, 420);

    edit_target_count = new QLineEdit;
    edit_target_count->setText(QString::number(this->target_count));
    edit_target_count->setValidator(new QIntValidator(1, 9999, this));

    target_pixmap = QPixmap(QtUtils::FilePath("target.png"));

    target_renderer = new QLabel;
    target_renderer->setPixmap(target_pixmap.scaled(target_size, target_size));


    slider_size = new QSlider;
    slider_size->setRange(16, 256);
    slider_size->setValue(this->target_size);
    slider_size->setPageStep(16);
    slider_size->setOrientation(Qt::Horizontal);

    validate = new QPushButton("Validate");
    cancel = new QPushButton("Cancel");

    setting_layout->addWidget(edit_target_count, 0, 0);
    setting_layout->addWidget(slider_size, 0, 1);
    setting_layout->addWidget(target_renderer, 1, 0, 1, 2);
    setting_layout->addWidget(validate, 2, 0);
    setting_layout->addWidget(cancel, 2, 1);

    setting_layout->setAlignment(target_renderer, Qt::AlignHCenter);

    connect(slider_size, SIGNAL(valueChanged(int)), this, SLOT(ChangeTargetSize(int)));
    connect(validate, SIGNAL(clicked()), this, SLOT(Validate()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(Cancel()));

    this->setLayout(setting_layout);

}

void settings::Validate()
{
    this->target_count = edit_target_count->text().toInt();
    this->target_size = slider_size->value() - slider_size->value()%2;
    qDebug() << "Target count: " << edit_target_count->text().toInt() << ". Target size: " << this->target_size << ".";
    this->close();
}

void settings::Cancel()
{
    edit_target_count->setText(QString::number(this->target_count));
    slider_size->setValue(this->target_size);
    this->close();
}

void settings::ChangeTargetSize(int size)
{
    this->target_renderer->setPixmap(this->target_pixmap.scaled(size, size));
}
