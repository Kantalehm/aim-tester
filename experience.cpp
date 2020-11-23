#include "experience.h"
#include "utils.h"

experience::experience()
{
    target_size_px = 64;
    click_count = 0;
    target_count = 10;
}

void experience::compute_result()
{
    for (int i = 0; i < target_count; i++)
    {
        if (utils::square(clic_positions[i].first - target_positions[i].first) + utils::square(clic_positions[i].second - target_positions[i].second) <= utils::square(target_size_px))
        {
            m_in_target.push_back(true);
        }
        else
        {
            m_in_target.push_back(false);
        }
    }
}
