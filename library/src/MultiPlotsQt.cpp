#include <MultiPlotsQt.h>

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsQt::MultiPlotsQt()
{
	
}

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsQt::~MultiPlotsQt()
{
	// qThread_.join();
}

//---------------------------------------------------------------------------------------------------------------------
int MultiPlotsQt::configure(int _rows, int _cols)
{
	nRows_ = _rows;
	nCols_ = _cols;
	nPlots_ = _rows * _cols;

	try {
        boost::asio::io_service io_service;
		serverSocket_ = new boost::asio::ip::udp::socket(io_service);
		serverSocket_->open(boost::asio::ip::udp::v4());
		// boost::asio::io_service io_service;
		// serverSocket_ = new boost::asio::ip::udp::socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8989));
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return nPlots_;
}

//---------------------------------------------------------------------------------------------------------------------
bool MultiPlotsQt::setPlotData(std::vector<float> _dataX, std::vector<float> _dataY)
{	
	if(_dataX.size() > nPlots_ || _dataY.size() > nPlots_){
		return false;
	}

	try {
		float sendFloat[_dataY.size()];
		
		for(int i = 0; i < nPlots_; i++){
			sendFloat[i] = _dataY[i];
		}

		boost::array<char, sizeof(_dataY)> send_buffer;
		memcpy(&send_buffer[0], &sendFloat, sizeof(_dataY));

		// std::cout << "data: ";
		// for(int i = 0; i < nPlots_; i++){
		// 	std::cout << sendFloat[i] << " , ";
		// }
		// std::cout << std::endl;
		// std::cout << "----------" << std::endl;

		boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080);
		serverSocket_->send_to(boost::asio::buffer(send_buffer), endpoint);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return true;
}
