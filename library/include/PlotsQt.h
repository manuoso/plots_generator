#ifndef PLOTSQT_H
#define PLOTSQT_H

#include <iostream>
#include <mutex>
#include <vector>
#include <random>
#include <map>
#include <math.h>
#include <chrono>

#include <QMainWindow>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <qcustomplot.h>


class PlotsQt : public QMainWindow
{
    Q_OBJECT
    public:
        explicit PlotsQt(QWidget *parent = 0);

        ~PlotsQt();

        bool configure(int _rows, int _cols);

        bool getData();

        private slots:
            void realTimePlot();
        
    private:
        QWidget *centralWidget_;
        QGridLayout *mainLayout_;

        std::vector<QCustomPlot*> plots_;
        QTimer *dataTimer_;
        
        int nPlots_ = 0;
        std::vector<float> data_;

        bool stopAll_ = false;

};

#endif // PLOTSQT_H