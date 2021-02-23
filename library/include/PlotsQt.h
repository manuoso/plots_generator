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
#include <list>

#include <QWidget>
#include <QDialog>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <qcustomplot.h>

#include <boost/asio.hpp>
#include <boost/array.hpp>

class PlotsQt : public QDialog
{
    Q_OBJECT
    public:
        PlotsQt(QWidget *parent = 0);

        ~PlotsQt();

        int configure(int _rows, int _cols, int _nLines, std::string _ip, int _port);
    
    protected:
        void closeEvent(QCloseEvent *event) override;

    private: 
        bool getData();

    private slots:
        void realTimePlot();
        
    private:
        QGridLayout *mainLayout_;

        std::vector<QColor> lineColors_;
        std::vector<Qt::PenStyle> lineStyle_;

        std::vector<QCustomPlot*> plots_;
        QTimer *dataTimer_;

        std::thread *dataThread_;

        boost::asio::ip::tcp::socket *serverSocket_;
        boost::asio::ip::tcp::acceptor *acc_;
        std::mutex dataMutex_;
        
        std::string ip_ = "";
        short unsigned int port_ = 0;
        int nPlots_ = 0;
        int nLines_ = 0;
        std::vector<float> data_;

        bool stopAll_ = false;

};

#endif // PLOTSQT_H