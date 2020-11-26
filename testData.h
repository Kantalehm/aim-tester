#ifndef TESTDATA_H
#define TESTDATA_H

#include "QtUtils.h"

struct test_data{
    std::vector<std::pair<int, int>> target_positions;
    std::vector<std::pair<int, int>> mouse_positions;
    qint64 time;
    int target_size;
    int target_count;
    std::pair<int, int> screen_res;
};
#endif // TESTDATA_H
