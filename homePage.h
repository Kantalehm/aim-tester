#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "QtUtils.h"
#include "settings.h"
#include "testing.h"
#include "utils.h"

class homePage : public QWidget
{
    Q_OBJECT

    public:
        QPushButton *m_start;
        homePage();

    private:
        QStackedWidget *stackedWidget;
        QLabel *m_title;
        QFont m_title_font;
        QFont m_button_font;
        QPushButton *m_quit;
        QPushButton *m_settings;
        testing *test;
        settings *setting;

    private slots:
        void OpenSettings();
        void StartTest();
};

#endif // HOMEPAGE_H
