
#include <MultiPlotsQt.h>

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsQt::MultiPlotsQt(std::string _ip, short unsigned int _port)
{
	try {
		boost::system::error_code ec;
        boost::asio::io_service io_service;
		serverSocket_ = new boost::asio::ip::tcp::socket(io_service);
		serverSocket_->connect({ boost::asio::ip::address::from_string(_ip), _port}, ec);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsQt::~MultiPlotsQt()
{
	try {
		serverSocket_->close();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------------------------------
bool MultiPlotsQt::setPlotData(std::vector<float> _data)
{	
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
