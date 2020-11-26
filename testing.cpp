#include "testing.h"

testing::testing()
{

    target_count = 15;
    target_size = 64;
    screen_res = std::pair<int, int>(600, 400);
    Initialization();

}

testing::testing(settings *setting)
{
    target_count = setting->target_count;
    target_size = setting->target_size;
    screen_res = setting->screen_res;
    Initialization();
}

void testing::Initialization()
{

    this->setAttribute(Qt::WA_DeleteOnClose);
    layout = new QVBoxLayout;
    top_layout = new QHBoxLayout;
    frame_layout = new QVBoxLayout;

    resize(screen_res.first, screen_res.second);

    quit = new QPushButton("Quit");
    quit->setFont(QtUtils::basic_font);
    test_complete = new QLabel("Test complete!");
    test_complete->setFont(QtUtils::title_font);
    view_results = new QPushButton("View results");
    view_results->setFont(QtUtils::button_font);
    countdown = new QLabel;
    countdown->setFont(QtUtils::countdown_font);
    frame = new QFrame;

    // top_layout->addWidget(countdown);
    top_layout->addWidget(quit);
    top_layout->setAlignment(quit, Qt::AlignRight);

    frame_layout->addWidget(countdown);
    frame_layout->addWidget(test_complete);
    frame_layout->addWidget(view_results);
    test_complete->hide();
    view_results->hide();
    frame_layout->setAlignment(countdown, Qt::AlignCenter);
    frame->setLayout(frame_layout);

    layout->addLayout(top_layout);
    layout->addWidget(frame);
    layout->setStretch(0, 1);
    layout->setStretch(1, 10);

    this->setLayout(layout);

    target = new QLabel(frame);
    target->setPixmap(QPixmap(QtUtils::FilePath("target.png")).scaled(
                          target_size, target_size));
    target->setGeometry(0, 0, 0, 0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(StartCountdown()));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(view_results, SIGNAL(clicked()), this, SLOT(ShowResults()));
    timer->start(20);
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
        if (!test_began)
        {
            test_began = true;
            StartTest();
            frame_layout->removeWidget(countdown);
            top_layout->insertWidget(0, countdown);
            countdown->setFont(QtUtils::basic_font);
        }
        countdown->setText(QString::number((double)elapsed_timer.elapsed()/1000 - 3, 'g') + "\ts");
    }
    // countdown->setText("(" + QString::number(QCursor::pos().x() - this->geometry().left()) + " ; " + QString::number(QCursor::pos().y() - this->geometry().top()));
                       // ") | frame L T R B: " + QString::number(frame->geometry().left()) + " ; " + QString::number(frame->geometry().top()) + " ; " +  QString::number(frame->geometry().right()) + " ; " +  QString::number(frame->geometry().bottom()));
}

void testing::StartTest()
{
    target->setGeometry(0, 0, target_size, target_size);
    target_positions.push_back(MoveTarget());
}

std::pair<int, int> testing::MoveTarget()
{
    int left_margin = frame->geometry().left();
    int top_margin = frame->geometry().top();
    int x = QRandomGenerator::global()->bounded(0, frame->geometry().right() - target_size - left_margin);
    int y = QRandomGenerator::global()->bounded(0, frame->geometry().bottom() - target_size - top_margin);
    target->move(x, y);
    qDebug() << "(" + QString::number(x + left_margin + target_size/2) + ", "
                + QString::number(y + target_size/2 + top_margin) + ")";
    return std::pair<int, int>(x + left_margin + target_size/2, y + top_margin + target_size/2);
}

void testing::mousePressEvent(QMouseEvent *event)
{
    if (test_began)
    {
        std::pair<int, int> cursor = std::pair<int, int>(QCursor::pos().x() - this->geometry().left(), QCursor::pos().y() - this->geometry().top());
        qDebug() << cursor;
        if ((int)target_positions.size() == target_count)
        {
            clic_positions.push_back(std::pair<int, int>(QCursor::pos().x() - this->geometry().left(), QCursor::pos().y() - this->geometry().top()));
            target->hide();
            countdown->hide();
            test_complete->show();
            view_results->show();
            frame_layout->setAlignment(view_results, Qt::AlignCenter);
            frame_layout->setAlignment(test_complete, Qt::AlignCenter);
            frame_layout->setAlignment(Qt::AlignCenter);
            data = {target_positions, clic_positions, elapsed_timer.elapsed() - 3000, this->target_size, this->target_count, screen_res};
        }
        else
        {
            clic_positions.push_back(std::pair<int, int>(QCursor::pos().x() - this->geometry().left(), QCursor::pos().y() - this->geometry().top()));
            target_positions.push_back(MoveTarget());
        }

    }
}

void testing::ShowResults()
{
    results *result = new results(data);
    result->show();
    this->close();
}
