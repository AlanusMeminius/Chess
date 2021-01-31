//
// Created by Uniqu on 1/31/2021.
//

#ifndef TEST_DIALOG_SPLASHSCREEN_H
#define TEST_DIALOG_SPLASHSCREEN_H

#include <QDialog>
#include <map>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class SplashScreen; }
QT_END_NAMESPACE

class SplashScreen : public QDialog {
Q_OBJECT

public:
    int Select{};
private:
    int Counter = 0;
    std::map<QPushButton *, int> btnIndex;

public:
    explicit SplashScreen(QWidget *parent = nullptr);

    ~SplashScreen() override;

public slots:

    void btnClicked();

    void progressBar();

private:
    Ui::SplashScreen *ui;
    QTimer *timer;
    QGraphicsDropShadowEffect *effect;
};

#endif //TEST_DIALOG_SPLASHSCREEN_H
