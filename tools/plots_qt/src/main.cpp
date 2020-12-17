#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>

#include <QApplication>
#include <PlotsQt.h>


void showHelp(){
	std::cout << "--help\n";
	std::cout << "Required arguments: Number Rows(int) Number Cols(int) Number lines(int) \n";
}

int main(int argc, char** argv) {

	int rows = 0, cols = 0, nlines = 0;
	
	if (argc == 4){
		// parse input arguments
		std::vector<std::string> inputArgs;
        for(int i = 1; i < argc;i++){
            inputArgs.push_back(argv[i]);
        }
		if(inputArgs[0] == "--help")
			showHelp();
		else{
			rows = stoi(inputArgs[0]);
			cols = stoi(inputArgs[1]);
			nlines = stoi(inputArgs[2]);
		}
	}
	else{
		std::cout << "No all input arguments provided\n";
		showHelp();
		return 0;
	}

	QApplication a(argc, argv);
    PlotsQt gui;
	int nplots = gui.configure(rows, cols, nlines);
	if(nplots == 0){
		std::cout << "returned 0 nplots" << std::endl;
		return 0;
	}

    gui.show();
    
    return a.exec();
}

