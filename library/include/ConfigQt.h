#ifndef CONFIGQT_H
#define CONFIGQT_H

#include <iostream>
#include <mutex>
#include <vector>
#include <random>
#include <map>
#include <math.h>
#include <chrono>
#include <thread>
#include <list>

#include <QMainWindow>
#include <QTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include <PlotsQt.h>


class ConfigQt : public QMainWindow
{
    Q_OBJECT
    public:
        ConfigQt(QWidget *parent = 0);

        ~ConfigQt();

    private:
        void buildPanel();

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots: 
        void openPlotsWindow();  

        void configSocket();  
    private:
        QWidget *centralWidget_;
        QVBoxLayout *mainLayout_;

        QHBoxLayout *plotsDataLayout_, *openWindowLayout_, *socketDataLayout_;
        QLabel *plotsDataLabel_, *socketDataLabel_;

        QPushButton *socketBut_;
        QLineEdit *ipText_, *portText_;
        QLineEdit *filText_, *colText_, *nlinesText_;

        QPushButton *openWindowBut_;

        std::string ip_ = "127.0.0.1";
        int port_ = 8080;

        PlotsQt *lastPlotsQt_ = nullptr;

};

#endif // CONFIGQT_H