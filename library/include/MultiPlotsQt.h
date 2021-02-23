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
        MultiPlotsQt(std::string _ip, short unsigned int _port);

        ~MultiPlotsQt();
        
        bool setPlotData(std::vector<float> _data);

    private:
        boost::asio::ip::tcp::socket *serverSocket_;

};

#endif // MULTIPLOTSQT_H