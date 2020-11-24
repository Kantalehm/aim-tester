#include "homePage.h"
#include "testing.h"

homePage::homePage()
{
    m_title_font = QFont("Lato", 20, QFont::Bold);
    m_button_font = QFont("Lato", 14);

    QGridLayout *home_page_layout = new QGridLayout;

    m_title = new QLabel("Welcome to my aim tester!");
    m_start = new QPushButton("  S&tart test");
    m_settings = new QPushButton("  S&ettings");
    m_quit = new QPushButton("&Quit");

    m_title->setFont(m_title_font);
    this->setWindowIcon(QIcon(QtUtils::FilePath("aim_tester_icon.png")));
    this->setWindowTitle("Aim Tester v0.0");
    m_start->setFont(m_button_font);
    m_start->setIcon(QIcon(QtUtils::FilePath("aim_tester_play.png")));
    m_settings->setFont(m_button_font);
    m_settings->setIcon(QIcon(QtUtils::FilePath("aim_tester_settings.png")));
    m_quit->setFont(m_button_font);

    home_page_layout->addWidget(m_title, 1, 0, 1, 4);
    home_page_layout->addWidget(m_start, 2, 0, 1, 2);
    home_page_layout->addWidget(m_settings, 2, 2, 1, 2);
    home_page_layout->addWidget(m_quit, 0, 3);
    home_page_layout->addWidget(m_quit, 2, 1, 1, 1);


    home_page_layout->setAlignment(m_title, Qt::AlignHCenter);

    home_page_layout->setColumnStretch(0, 8);
    home_page_layout->setColumnStretch(1, 1);
    home_page_layout->setColumnStretch(2, 8);
    home_page_layout->setColumnStretch(3, 1);

    setting = new settings;

    connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(m_settings, SIGNAL(clicked()), this, SLOT(OpenSettings()));
    connect(m_start, SIGNAL(clicked()), this, SLOT(StartTest()));

    this->setLayout(home_page_layout);
}

void homePage::OpenSettings()
{
    setting->exec();
}

void homePage::StartTest()
{
    testing *test = new testing(this->setting);
    test->Begin();
}
