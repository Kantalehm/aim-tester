#ifndef TESTINGTIME_H
#define TESTINGTIME_H

#include "QtUtils.h"
#include "settings2.h"
#include "testData.h"

class TestingTime : public QDialog
{
    Q_OBJECT

    private:
        // settings *setting;
        int time_limit;
        int target_size;
        std::pair<int, int> screen_res;

        QVBoxLayout *layout;
        QHBoxLayout *top_layout;
        QVBoxLayout *frame_layout;

        QLabel *target;

        QLabel *countdown;
        QLabel *test_complete;
        QFrame *frame;
        QElapsedTimer elapsed_timer;
        QPushButton *quit;
        QPushButton *view_results;

        bool test_began = false;

        std::vector<std::pair<int, int>> target_positions;
        std::vector<std::pair<int, int>> clic_positions;

        void Initialization();
        void StartTest();
        std::pair<int, int> MoveTarget();
        void mousePressEvent(QMouseEvent *event);

        test_data data;

    public:
        TestingTime();
        TestingTime(Settings2 *settings);

        void Begin();

    private slots:
        void StartCountdown();
        void ShowResults();


};

#endif // TESTINGTIME_H
