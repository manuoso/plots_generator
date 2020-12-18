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


template<std::size_t R_, std::size_t C_, std::size_t N_>
class MultiPlotsQt
{
public:
    MultiPlotsQt();

    bool setPlotData(std::vector<float> _data);

private:
    boost::asio::ip::tcp::socket *serverSocket_;

};

#include <MultiPlotsQt.inl>

#endif // MULTIPLOTSQT_H