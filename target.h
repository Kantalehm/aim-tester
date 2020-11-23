#ifndef TARGET_H
#define TARGET_H

#include <QtWidgets>


class target
{
    private:
        int m_radius;

    public:
        target();
        void setRadius(int radiusInPixel);
        int getRadius();



};

#endif // TARGET_H
