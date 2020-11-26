#ifndef RESULTS_H
#define RESULTS_H

#include "QtUtils.h"
#include "utils.h"
#include "testData.h"

class results : public QDialog
{
    Q_OBJECT

    private:
        std::vector<std::pair<int, int>> targets;
        std::vector<std::pair<int, int>> clics;
        double test_time;
        int target_size;
        int target_count;
        std::pair<int, int> res;

        QVBoxLayout *layout;
        QHBoxLayout *bottom_layout;

        QLabel *resolution;
        QLabel *target_count_label;
        QLabel *target_size_label;
        QLabel *target;
        QLabel *percentage;
        QLabel *time;

        QPushButton *close;
        QPushButton *save;

        void Initialization();
        float ComputePercentage();
        bool ClicInTarget(std::pair<int, int> clic, std::pair<int, int> target);
        void PlaceCursors();

    public:
        results();
        results(struct test_data data);

    private slots:
        void update();
};

#endif // RESULTS_H
