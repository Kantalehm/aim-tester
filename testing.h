#ifndef TESTING_H
#define TESTING_H

#include "QtUtils.h"
#include "settings.h"
#include "results.h"
#include "testData.h"

class testing : public QDialog
{
    Q_OBJECT

    private:
        // settings *setting;
        int target_count;
        int target_size;

        QVBoxLayout *layout;
        QHBoxLayout *top_layout;
        QVBoxLayout *frame_layout;

        QLabel *target;

        QLabel *countdown;
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
        testing();
        testing(settings *setting);

        void Begin();

    private slots:
        void StartCountdown();
        void ShowResults();


};

#endif // TESTING_H
