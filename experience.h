#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <QApplication>
#include <QtWidgets>
#include <vector>
#include <string>


class experience
{
    public:
        experience();
        int target_size_px;
        int target_count;
        int click_count;
        std::vector<std::pair<int, int>> target_positions;
        std::vector<std::pair<int, int>> clic_positions;
        std::vector<bool> m_in_target;
        void compute_result();


};

#endif // EXPERIENCE_H
