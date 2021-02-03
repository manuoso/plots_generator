#ifndef PLOTSQT_H
#define PLOTSQT_H

#include <iostream>
#include <mutex>
#include <vector>
#include <random>
#include <map>
#include <math.h>
#include <chrono>
#include <thread>

#include <QMainWindow>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <qcustomplot.h>

#include <boost/asio.hpp>
#include <boost/array.hpp>

class PlotsQt : public QMainWindow
{
    Q_OBJECT
    public:
        PlotsQt(QWidget *parent = 0);

        ~PlotsQt();

        bool configure(bool _enableTs, int _rows, int _cols, int _nLines);

    signals:
        void updateplotXY();

    private: 
        bool getData();

        void plotDataXY();

    private slots:
        void realTimePlot();

    private:
        QWidget *centralWidget_;
        QGridLayout *mainLayout_;

        std::vector<QColor> lineColors_;
        std::vector<Qt::PenStyle> lineStyle_;

        std::vector<QCustomPlot*> plots_;
        QTimer *dataTimer_;

        std::thread *dataThread_;

        boost::asio::ip::tcp::socket *socket_;
        boost::asio::ip::tcp::acceptor *acc_;
        std::mutex dataMutex_;
        
        bool enableTs_ = 0;
        int nPlots_ = 0;
        int nLines_ = 0;
        std::vector<float> dataX_, dataY_;

        bool stopAll_ = false;

};

#endif // PLOTSQT_H