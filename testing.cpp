#include "testing.h"

testing::testing()
{

    target_count = 15;
    target_size = 64;
    Initialization();

}

testing::testing(settings *setting)
{
    target_count = setting->target_count;
    target_size = setting->target_size;
    Initialization();
}

void testing::Initialization()
{
    QHBoxLayout *layout = new QHBoxLayout;
    countdown = new QLabel("Bonjour");
    layout->addWidget(countdown);
    this->setLayout(layout);
    this->setMinimumSize(150, 150);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CountDown()));
    timer->start(100);
    elapsed_timer.start();
}

void testing::Begin()
{
    this->show();
}

void testing::StartCountdown()
{
    if (!elapsed_timer.hasExpired(3000))
    {
        countdown->setText(QString::number(3 - elapsed_timer.elapsed()/1000));
    }
    else
    {
        countdown->setText(QString::number((double)elapsed_timer.elapsed()/1000 - 3, 'g'));
    }
}
