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

#include <boost/asio.hpp>
#include <boost/array.hpp>


class MultiPlotsQt
{
    public:
        MultiPlotsQt(bool _enableTs);

        bool setPlotDataY(std::vector<float> _data);

        bool setPlotDataXY(std::vector<float> _dataX, std::vector<float> _dataY);

    private:
        std::size_t send_init(std::vector<float> _msg);    
        
    private:
        boost::asio::ip::tcp::socket *socket_;

        bool enableTs_ = false;

};

#endif // MULTIPLOTSQT_H