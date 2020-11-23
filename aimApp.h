#ifndef AIMTEST_H
#define AIMTEST_H

#include "QtUtils.h"
#include "settings.h"

class aimApp: public QWidget
{
    private:
        static aimApp *instance;

    public:
        static aimApp *get()
        {
            if (!instance)
            {
                instance = new aimApp;
            }
            return instance;
        }

        settings m_settings;

        void OpenSettings();
};

#endif // AIMTEST_H
