#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <csignal>

#include <MultiPlotsQt.h>


bool fin = false;

// Replacement handler
void finishHandler(int _sig){
    std::cout << "Finish Handler: Catch signal " << _sig << std::endl;
    fin = true;
}

int main(int argc, char** argv) {
	signal(SIGINT, finishHandler);
    signal(SIGTERM, finishHandler);

	int nplots = 3*2*2;
	MultiPlotsQt plotter(false);

	int cont = 0;
	while(!fin){
		std::vector<float> dataX, dataY;

		for(int i = 0; i < nplots; i++){
			dataX.push_back(cont + i);
			dataY.push_back((cont + i ) * 2);
		}

		// plotter.setPlotDataY(dataY);
		plotter.setPlotDataXY(dataX, dataY);
		cont++;

		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}

