#ifndef MULTIPLOTSQT_H
#define MULTIPLOTSQT_H

#include <iostream>
#include <mutex>
#include <vector>
#include <random>
#include <map>
#include <math.h>
#include <chrono>
#include <thread>


class MultiPlotsQt
{
public:
    MultiPlotsQt();

    ~MultiPlotsQt();

    int configure(int _rows, int _cols);

    bool setPlotData(std::vector<float> _dataX, std::vector<float> _dataY);

private:
    int nPlots_ = 0;
    int nRows_ = 0;
    int nCols_ = 0;
    
    std::thread *qThread_;

};

#endif // MULTIPLOTSQT_H