#pragma once

#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>

namespace Ui {
    class CustomLabel final : public QLabel {
    public:
        CustomLabel(
            QVBoxLayout* layout, const QString& objName, const QString& label, const int& minimumHeight) {
            setText(label);
            setObjectName(objName);
            setMinimumHeight(minimumHeight);
            layout->addWidget(this);
        }
    };

    class TimeRecord final : public QLabel {
    Q_OBJECT
    public:
        QTime* qTime;
        QTimer* showTimer;
        // 初始化 showTime->start(100)
        // 改变阵营改变 startTime
        // 对局结束 showTime->stop()
        // 一定时间提醒一下 直接在

    public:
        explicit TimeRecord(QObject* = nullptr) : qTime(new QTime), showTimer(new QTimer), secs(0), total(0) {
            showTimer->setInterval(100);
            connect(showTimer, &QTimer::timeout, this, [this]() {
                *qTime = QTime::currentTime();
                secs = -(qTime->secsTo(startTime));
                if (secs > 180)
                {
                    emit timeRemind(secs);
                }
                _set_text(secs);
            });
        }

    public slots:

        void reverse() {
            total += secs;
            startTime = QTime::currentTime();
        }

        void reset() {
            total = 0;
            secs = 0;
            _set_text(secs);
            startTime = QTime::currentTime();
        }

    signals:

        void timeRemind(int secs);

    private:
        int secs;
        int total;
        QTime startTime;

    private:
        QString _set_text(int secs) {
            // max 100 minutes
            if (secs > 6000)
            {
                secs = secs - 6000;
            }

            const int t_sec = secs % 60;
            const int t_min = secs / 60;

            QString result = tr("%1:%2").arg(t_min, 2, 10, QChar('0')).arg(t_sec, 2, 10, QChar('0'));
            setText(result);
            return result;
        }
    };
}
