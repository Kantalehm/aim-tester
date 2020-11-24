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
    qDebug() << test_time;
    Initialization();
}

void results::Initialization()
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    layout = new QVBoxLayout;
    bottom_layout = new QHBoxLayout;

    target = new QLabel;
    target->setPixmap(QPixmap(QtUtils::FilePath("target.png")).scaled(256, 256));

    percentage = new QLabel;

    time = new QLabel;

    close = new QPushButton("Close");
    save = new QPushButton("Save");

    bottom_layout->addWidget(save);
    save->setDisabled(true);
    bottom_layout->addWidget(close);

    layout->addWidget(time);
    layout->addWidget(percentage);
    layout->addWidget(target);
    layout->addLayout(bottom_layout);

    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);

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
        int x = (clics[i].first - targets[i].first + target_size/2) * 256.0/target_size;
        int y = (clics[i].second - targets[i].second + target_size/2) * 256.0/target_size;
        qDebug() << "(" + QString::number(x) + ", " + QString::number(y) + ")";
        QLabel *cross = new QLabel(target);
        cross->setPixmap(QPixmap(QtUtils::FilePath("cross.png")));
        cross->move(x, y);
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
