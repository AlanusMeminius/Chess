#pragma execution_character_set("utf-8")

#include "StartUpWindow.h"

Ui::StartUpWindow::StartUpWindow() 
    : timer(new QTimer)
    , verticalLayout(new QVBoxLayout(this))
    , frame(new QFrame(this))
    , titleLabel(new QLabel(frame))
    , horizontalLayoutWidget(new QWidget(frame))
    , progressBar(new QProgressBar(frame))
    , loadingLabel(new QLabel(frame))
    // , createdLabel(new QLabel(frame))
    , horizontalLayout(new QHBoxLayout(horizontalLayoutWidget)) 
{
    this->resize(680, 400);
    setWindowIcon(QPixmap(":/icon.png"));
    // remove title bar
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // set style
    QFile styleFile(":/startWindow.qss");
    styleFile.open(QFile::ReadOnly);
    const QString style(styleFile.readAll());
    this->setStyleSheet(style);
    modeList = {
            {{0, tr("\344\270\216\350\207\252\345\267\261\345\257\271\346\210\230")},
                    new QPushButton(horizontalLayoutWidget)},
            {{1, tr("\344\270\216AI\345\257\271\346\210\230")},
                    new QPushButton(horizontalLayoutWidget)},
            {{2, tr("\347\275\221\347\273\234\345\257\271\346\210\230")},
                    new QPushButton(horizontalLayoutWidget)}};
    setUI();

    for (auto&& item : modeList) {
        item.second->setText(item.first.second);
        item.second->setMaximumSize(QSize(100, 40));
        horizontalLayout->addWidget(item.second);
        connect(item.second, &QPushButton::clicked, this, &StartUpWindow::btnClicked);
    }
    connect(timer, &QTimer::timeout, this, &StartUpWindow::progress);
}

void Ui::StartUpWindow::setUI() 
{
    verticalLayout->addWidget(frame);
    frame->setObjectName(QString::fromUtf8("Frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    QFont titleFont;
    titleFont.setPointSize(40);

    // title
    titleLabel->setText(tr("\344\270\255\345\233\275<strong>\350\261\241\346\243\213</strong>"));
    titleLabel->setGeometry(QRect(190, 50, 280, 65));
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    QFont smallFont;
    smallFont.setPointSize(10);

    //mode select
    horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(100, 160, 461, 91));
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    // progress bar
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setGeometry(QRect(60, 250, 531, 23));
    progressBar->setValue(0);

    // loading label
    loadingLabel->setObjectName(QString::fromUtf8("loadingLabel"));
    loadingLabel->setGeometry(QRect(272, 280, 100, 21));
    loadingLabel->setFont(smallFont);
    loadingLabel->setAlignment(Qt::AlignCenter);
    loadingLabel->setText("WELCOME");

    //            createdLabel->setText(
    //                    tr(R"(<html><head/><body><p align="right"><span style=" font-size:10pt;">Created: Luke </span></p></body></html>)"));
    //            createdLabel->setObjectName(QString::fromUtf8("createdLabel"));
    //            createdLabel->setGeometry(QRect(560, 350, 90, 21));
    //            createdLabel->setFont(smallFont);
    //            createdLabel->setAlignment(Qt::AlignCenter);
}


void Ui::StartUpWindow::btnClicked() 
{
    loadingLabel->setText("Loading..");
    timer->start(7);
}

void Ui::StartUpWindow::progress() 
{
    progressBar->setValue(counter_);
    counter_++;
    if (counter_ > 100) {
        timer->stop();
        accept();
    }
}

SetUp::SetUp() 
    : startUpWindow() 
{
    application = nullptr;
    startUpWindow = new Ui::StartUpWindow;
    for (auto&& item : startUpWindow->modeList)
    {
        connect(item.second, &QPushButton::clicked, this, [this, item](int) { 
            emit btnIndex(item.first.first); 
        });
    }

    connect(this, SIGNAL (btnIndex(int)), this, SLOT (setUpMainWindow(int)));
    startUpWindow->show();
}

SetUp::~SetUp() 
{
    delete startUpWindow;
    delete application;
}

void SetUp::setUpMainWindow(int select)
{
    application = new Application(select);
    if (startUpWindow->exec() == QDialog::Accepted)
    {
        application->show_window();
    }
}