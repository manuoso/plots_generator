
#include "MultiPlotsQt.h"

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsQt::MultiPlotsQt(bool _enableTs)
{
	enableTs_ = _enableTs;

	try {
		boost::system::error_code ec;
		boost::asio::io_service io_service;
		socket_ = new boost::asio::ip::tcp::socket(io_service);
		socket_->connect({ boost::asio::ip::address::from_string("127.0.0.1"), 8080}, ec);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------------------------------
std::size_t MultiPlotsQt::send_init(std::vector<float> _msg){
	return boost::asio::write(*socket_, boost::asio::buffer(_msg));
}

//---------------------------------------------------------------------------------------------------------------------
bool MultiPlotsQt::setPlotDataY(std::vector<float> _data)
{	
	if(!enableTs_){
		return false;
	}

	try {
		std::vector<float> inity;
		inity.push_back(1);
		send_init(inity);
		boost::system::error_code ec;
		std::size_t length = boost::asio::write(*socket_, boost::asio::buffer(_data), ec);

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

//---------------------------------------------------------------------------------------------------------------------
bool MultiPlotsQt::setPlotDataXY(std::vector<float> _dataX, std::vector<float> _dataY)
{	
	if(enableTs_){
		return false;
	}

	try {
		std::vector<float> inity;
		inity.push_back(1);
		send_init(inity);
		boost::system::error_code ec;
		std::size_t lengthY = boost::asio::write(*socket_, boost::asio::buffer(_dataY), ec);

		std::vector<float> initx;
		initx.push_back(2);
		send_init(initx);
		std::size_t lengthX = boost::asio::write(*socket_, boost::asio::buffer(_dataX), ec);

		// std::cout << "length sended YI: " << lengthYI << std::endl;
		// std::cout << "length sended XI: " << lengthXI << std::endl;

		// std::cout << "length sended Y: " << lengthY << std::endl;
		// std::cout << "length sended X: " << lengthX << std::endl;

		// std::cout << "data X: ";
		// for(int i = 0; i < _dataX.size(); i++){
		// 	std::cout << _dataX[i] << " , ";
		// }
		// std::cout << std::endl;
		// std::cout << "**********" << std::endl;

		// std::cout << "data Y: ";
		// for(int j = 0; j < _dataY.size(); j++){
		// 	std::cout << _dataY[j] << " , ";
		// }
		// std::cout << std::endl;
		// std::cout << "----------" << std::endl;

	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return true;
}
