#include "target.h"

target::target()
{

}

int target::getRadius()
{
    return this->m_radius;
}

void target::setRadius(int radiusInPixel)
{
    this->m_radius = radiusInPixel;
}
