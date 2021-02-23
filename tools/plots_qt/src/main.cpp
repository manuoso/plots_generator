#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>

#include <QApplication>
#include <ConfigQt.h>

int main(int argc, char** argv) {

	QApplication a(argc, argv);
    ConfigQt gui;

	gui.resize(500,200);
    gui.show();
    
    return a.exec();
}
