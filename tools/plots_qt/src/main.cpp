#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <csignal>
#include<stdio.h>
#include<stdlib.h>

#include <QApplication>
#include <PlotsQt.h>


int main(int argc, char** argv) {
	QApplication a(argc, argv);

    PlotsQt gui(0);
	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);

	int nplots = gui.configure(rows, cols);
	if(nplots == 0){
		std::cout << "returned 0 nplots" << std::endl;
		return 0;
	}

    gui.show();
    
    return a.exec();
}

