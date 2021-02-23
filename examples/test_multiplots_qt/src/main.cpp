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
	MultiPlotsQt plotter("127.0.0.1", 8080);

	int cont = 0;
	while(!fin){
		std::vector<float> data;
		for(int i = 0; i < nplots; i++){
			data.push_back(cont + i);
		}

		plotter.setPlotData(data);
		cont++;

		if(cont == 3000)
			cont = 0;

		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}

