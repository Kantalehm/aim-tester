#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include <QApplication>
#include <QtWidgets>
#include "experience.h"

class clickHandler : public QWidget
{
    Q_OBJECT

    private:
        QLabel *m_cursorPos;
        QLabel *m_target;
        experience *m_exp;

    protected:
        void mousePressEvent(QMouseEvent *event) override;

    public:
        clickHandler();

    public slots:
        void update();


};

#endif // CLICKHANDLER_H
