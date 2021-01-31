//
// Created by Uniqu on 1/31/2021.
//

#include <QTimer>

#include "Splashscreen.h"
#include "../ui/Ui_Splashscreen.h"


SplashScreen::SplashScreen(QWidget *parent) :
        QDialog(parent),
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
    btnIndex.insert({{ui->mode1, 0},
                     {ui->mode2, 1},
                     {ui->mode3, 2}});

    for (const auto &item : btnIndex) {
        connect(item.first, SIGNAL(clicked()), this, SLOT(btnClicked()));
    }
}

SplashScreen::~SplashScreen() {
    delete ui;
    delete timer;
    delete effect;
}

void SplashScreen::btnClicked() {
    ui->loading_label->setText("Loading..");
    QObject *s = sender();
    for (const auto &item : btnIndex) {
        if (item.first == s) {
            Select = item.second;
            break;
        }
    }
    timer->start(1);
}

void SplashScreen::progressBar() {
    ui->progressBar->setValue(Counter);
    Counter++;
    if (Counter > 100) {
        timer->stop();
        accept();
    }
}


