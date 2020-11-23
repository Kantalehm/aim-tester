#include "clickHandler.h"
#include <QDebug>
#include "utils.h"

clickHandler::clickHandler()
{
    m_exp = new experience();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(33);

    m_cursorPos = new QLabel(this);
    m_cursorPos->setGeometry(10, 10, 100, 15);

    m_target = new QLabel(this);
    m_target->setPixmap(QPixmap::fromImage(QImage(QApplication::applicationDirPath() + "/target.png").scaled(m_exp->target_size_px, m_exp->target_size_px)));
    m_target->setGeometry(0, 0, 0, 0);


}

void clickHandler::update()
{
    m_cursorPos->setText("(" + QString::number(QCursor::pos().x() - this->geometry().left()) + " ; " + QString::number(QCursor::pos().y() - this->geometry().top())  + ")");
}

void clickHandler::mousePressEvent(QMouseEvent *event)
{
    if (m_exp->click_count > m_exp->target_count)
    {
        return;
    }
    if (event->button() == Qt::LeftButton)
    {
        if (m_exp->click_count != 0)
        {
            m_exp->clic_positions.push_back(std::pair<int, int>(QCursor::pos().x() - this->geometry().left(), QCursor::pos().y() - this->geometry().top()));
            if (m_exp->click_count == m_exp->target_count)
            {
                qDebug() << m_exp->target_positions << "\n";
                qDebug() << m_exp->clic_positions << "\n";
                m_exp->compute_result();
                qDebug() << m_exp->m_in_target << "\n";
                return;
            }

        }
        int x = QRandomGenerator::global()->bounded(this->geometry().right() - this->geometry().left() - m_exp->target_size_px);
        int y = QRandomGenerator::global()->bounded(this->geometry().bottom() - this->geometry().top() - m_exp->target_size_px);
        m_target->setGeometry(x, y, m_exp->target_size_px, m_exp->target_size_px);
        m_exp->target_positions.push_back(std::pair<int, int>(x + m_exp->target_size_px/2, y + m_exp->target_size_px / 2));
        m_exp->click_count += 1;
    }
}
