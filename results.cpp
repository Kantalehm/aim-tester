#include "results.h"

results::results()
{
    time = new QLabel("Missing data", this);
}

results::results(struct test_data data)
{
    this->targets = data.target_positions;
    this->clics = data.mouse_positions;
    this->test_time = (double)data.time / 1000;
    this->target_size = data.target_size;
    this->target_count = data.target_count;
    this->res = data.screen_res;
    qDebug() << test_time;
    Initialization();
}

void results::Initialization()
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    layout = new QVBoxLayout;
    bottom_layout = new QHBoxLayout;

    target = new QLabel;
    target->setPixmap(QPixmap(QtUtils::FilePath("target_result.png")));

    percentage = new QLabel;
    percentage->setFont(QtUtils::basic_font);
    time = new QLabel;
    time->setFont(QtUtils::basic_font);
    resolution = new QLabel;
    resolution->setFont(QtUtils::basic_font);
    target_count_label = new QLabel;
    target_count_label->setFont(QtUtils::basic_font);
    target_size_label = new QLabel;
    target_size_label->setFont(QtUtils::basic_font);

    close = new QPushButton("Close");
    save = new QPushButton("Save");

    bottom_layout->addWidget(save);
    save->setDisabled(true);
    bottom_layout->addWidget(close);

    layout->addWidget(resolution);
    layout->addWidget(target_count_label);
    layout->addWidget(target_size_label);
    layout->addWidget(time);
    layout->addWidget(percentage);
    layout->addWidget(target);
    layout->addLayout(bottom_layout);


    layout->setAlignment(resolution, Qt::AlignCenter);
    layout->setAlignment(target_count_label, Qt::AlignCenter);
    layout->setAlignment(target_size_label, Qt::AlignCenter);
    layout->setAlignment(time, Qt::AlignCenter);
    layout->setAlignment(percentage, Qt::AlignCenter);
    layout->setAlignment(target, Qt::AlignCenter);
    layout->setAlignment(bottom_layout, Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);

    resolution->setText("Window resolution: " + QString::number(res.first) + "x" + QString::number(res.second) + "px");
    target_count_label->setText("Target count: " + QString::number(target_count));
    target_size_label->setText("Target size: " + QString::number(target_size) + " px");
    time->setText("Test duration: " + QString::number(test_time) + " seconds.");
    percentage->setText("Target hit rate: " + QString::number(ComputePercentage()) + "%");

    PlaceCursors();

    // QTimer *timer = new QTimer;
    // connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    // timer->start(20);

    connect(close, SIGNAL(clicked()), this, SLOT(close()));
}


void results::PlaceCursors()
{
    for (int i = 0; i < target_count; i++)
    {
        int x = (clics[i].first - targets[i].first + target_size/2) * 200.0/target_size + 200;
        int y = (clics[i].second - targets[i].second + target_size/2) * 200.0/target_size + 200;
        qDebug() << "(" + QString::number(x) + ", " + QString::number(y) + ")";
        QLabel *cross = new QLabel(target);
        cross->setPixmap(QPixmap(QtUtils::FilePath("cross.png")));
        cross->move(x - 10, y - 10);
    }
}

float results::ComputePercentage()
{
    int correct_hits = 0;
    for (int i = 0; i < target_count; i++)
    {
        if (ClicInTarget(clics[i], targets[i]))
        {
            correct_hits += 1;
        }
    }

    return (float)correct_hits / target_count * 100;
}

bool results::ClicInTarget(std::pair<int, int> clic, std::pair<int, int> target)
{
    if (utils::square(clic.first - target.first) + utils::square(clic.second - target.second) <= utils::square(target_size/2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void results::update()
{
    time->setText("(" + QString::number(QCursor::pos().x() - this->geometry().left()) + " ; " + QString::number(QCursor::pos().y() - this->geometry().top()));
    percentage->setText("target L T R B: " + QString::number(target->geometry().left()) + " ; " + QString::number(target->geometry().top()) + " ; " +  QString::number(target->geometry().right()) + " ; " +  QString::number(target->geometry().bottom()));
}
