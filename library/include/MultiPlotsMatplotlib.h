#ifndef MULTIPLOTSMATPLOTLIB_H
#define MULTIPLOTSMATPLOTLIB_H

#include <iostream>
#include <mutex>
#include <vector>
#include <random>
#include <map>
#include <math.h>
#include <chrono>

#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

class MultiPlotsMatplotlib
{
public:
    MultiPlotsMatplotlib();

    ~MultiPlotsMatplotlib();

    int configure(std::string _name, int _rows, int _cols);

    bool setPlotData(std::vector<float> _dataX, std::vector<float> _dataY);

private:
    std::string name_;
    int nPlots_ = 0;
    int nRows_ = 0;
    int nCols_ = 0;

    int delData_ = 30;

    std::map<int, std::vector<float>> storedDataX_, storedDataY_; 
	std::vector<std::string> lineColors_;

};

#endif // MULTIPLOTSMATPLOTLIB_H