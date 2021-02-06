
#ifndef TEST_DIALOG_SPLASHSCREEN_H
#define TEST_DIALOG_SPLASHSCREEN_H

#include <QTimer>
#include <map>
#include <QDialog>
#include <QGraphicsDropShadowEffect>

#include "Ui_Splashscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SplashScreen; }
QT_END_NAMESPACE

class SplashScreen : public QDialog {
Q_OBJECT

public:
    int Select{};
private:
    int Counter = 0;
//    std::map<QPushButton *, int> btnMap;

public:
    explicit SplashScreen() :
            ui(new Ui::SplashScreen),
            effect(new QGraphicsDropShadowEffect(this)),
            timer(new QTimer) {
        // init UI
        ui->setupUi(this);

        // remove title bar
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);

        // set graphics effect
        effect->setBlurRadius(20);
        effect->setXOffset(0);
        effect->setYOffset(0);
        effect->setColor(QColor(0, 0, 0, 60));
        ui->frame->setGraphicsEffect(effect);

        // set progressBar value
        ui->progressBar->setValue(Counter);
        connect(timer, SIGNAL(timeout()), this, SLOT(progressBar()));

        // connect btn
        std::map<QPushButton *, int> btnMap{{ui->mode1, 0},
                                            {ui->mode2, 1},
                                            {ui->mode3, 2}};
        for (const auto &item : btnMap) {
            connect(item.first, &QPushButton::clicked, [this, item](int) { emit btnIndex(item.second); });
        }
        connect(this, SIGNAL(btnIndex(int)), this, SLOT(btnClicked(int)));

    }

    ~SplashScreen() override {
        delete ui;
        delete timer;
        delete effect;
    }

signals:

    void btnIndex(int);

public slots:

    void btnClicked(int index) {
        ui->loading_label->setText("Loading..");
        Select = index;
        timer->start(1);
    }

    void progressBar() {
        ui->progressBar->setValue(Counter);
        Counter++;
        if (Counter > 100) {
            timer->stop();
            accept();
        }
    }

private:
    Ui::SplashScreen *ui;
    QTimer *timer;
    QGraphicsDropShadowEffect *effect;
};

#endif //TEST_DIALOG_SPLASHSCREEN_H
