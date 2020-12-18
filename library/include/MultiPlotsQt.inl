
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

//---------------------------------------------------------------------------------------------------------------------
template<std::size_t R_, std::size_t C_, std::size_t N_>
MultiPlotsQt<R_, C_, N_>::MultiPlotsQt()
{
	try {
		boost::system::error_code ec;
        boost::asio::io_service io_service;
		serverSocket_ = new boost::asio::ip::tcp::socket(io_service);
		serverSocket_->connect({ boost::asio::ip::address::from_string("127.0.0.1"), 8080}, ec);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<std::size_t R_, std::size_t C_, std::size_t N_>
bool MultiPlotsQt<R_, C_, N_>::setPlotData(std::vector<float> _data)
{	
	if(_data.size() != R_*C_*N_){
		return false;
	}

	try {
		boost::system::error_code ec;
		std::size_t length = boost::asio::write(*serverSocket_, boost::asio::buffer(_data), ec);

		// std::cout << "length sended: " << length << std::endl;

		// std::cout << "data: ";
		// for(int i = 0; i < R_*C_*N_; i++){
		// 	std::cout << _data[i] << " , ";
		// }
		// std::cout << std::endl;
		// std::cout << "----------" << std::endl;

	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return true;
}
