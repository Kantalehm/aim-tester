#ifndef TESTING_H
#define TESTING_H

#include "QtUtils.h"
#include "settings.h"

class testing : public QDialog
{
    Q_OBJECT

    private:
        // settings *setting;
        int target_count;
        int target_size;

        QLabel *countdown;
        QElapsedTimer elapsed_timer;

        std::vector<std::pair<int, int>> target_positions;
        std::vector<std::pair<int, int>> clic_positions;
        std::vector<bool> m_in_target;


    public:
        testing();
        testing(settings *setting);
        void Initialization();

        void Begin();

        void StartTest();


    private slots:
        void StartCountdown();


};

#endif // TESTING_H
