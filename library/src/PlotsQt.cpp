#include <PlotsQt.h>

//---------------------------------------------------------------------------------------------------------------------
PlotsQt::PlotsQt(QWidget *parent) :
    QMainWindow(parent)
    {
		centralWidget_ = new QWidget();
		mainLayout_ = new QGridLayout();
		centralWidget_->setLayout(mainLayout_);

		setCentralWidget(centralWidget_);
		this->setWindowTitle("Plots gui");
	}

//---------------------------------------------------------------------------------------------------------------------
PlotsQt::~PlotsQt()
{
	stopAll_ = true;
	dataThread_->join();
}

//---------------------------------------------------------------------------------------------------------------------
bool PlotsQt::configure(int _rows, int _cols)
{	
	nPlots_ = _rows * _cols;
	for(int i = 0; i < nPlots_; i++){
		data_.push_back(0);
	}
	
	QPen pen; 
	pen.setWidthF(3);
	pen.setStyle(Qt::SolidLine);
	pen.setColor(QColor(0, 0, 255));

	int cont = 0;
	for(int j = 0; j < _rows; j++){
		for(int k = 0; k < _cols; k++){
			plots_.push_back(new QCustomPlot());
			plots_[cont]->addGraph(); 
        	plots_[cont]->graph(0)->setPen(pen);

			mainLayout_->addWidget(plots_[cont], j, k, 1, 1);
			cont++;
		}
	}
	
	dataThread_ = new std::thread(&PlotsQt::getData, this);

	dataTimer_ = new QTimer(this);
	connect(dataTimer_, SIGNAL(timeout()), this, SLOT(realTimePlot()));
	dataTimer_->start(0);

	return true;
}

//---------------------------------------------------------------------------------------------------------------------
bool PlotsQt::getData(){
	try {
		boost::asio::io_service io_service;
		serverSocket_ = new boost::asio::ip::udp::socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080));
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	
	while(!stopAll_) {
		try {
			float recFloat[nPlots_];
			boost::array<char, sizeof(data_)> recv_buf;

			boost::asio::ip::udp::endpoint *remote_endpoint = new boost::asio::ip::udp::endpoint();
			serverSocket_->receive_from(boost::asio::buffer(recv_buf), *remote_endpoint);

			memcpy(&recFloat, &recv_buf[0], sizeof(data_));

			dataMutex_.lock();
			for(int i = 0; i < nPlots_; i++){
				data_[i] = recFloat[i];
			}
			dataMutex_.unlock();

			// std::cout << "data: ";
			// for(int i = 0; i < nPlots_; i++){
			// 	std::cout << recFloat[i] << " , ";
			// }
			// std::cout << std::endl;
			// std::cout << "----------" << std::endl;

		}catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}

		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return true;
}

//---------------------------------------------------------------------------------------------------------------------
void PlotsQt::realTimePlot()
{	
	static QTime time(QTime::currentTime());

    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.005) { // at most add point every 2 ms
		for(int i = 0; i < nPlots_; i++){
			dataMutex_.lock();
			plots_[i]->graph(0)->addData(key, data_[i]);
			dataMutex_.unlock();
		}

        lastPointKey = key;
    }
	
	for(int i = 0; i < nPlots_; i++){
		plots_[i]->graph(0)->rescaleAxes();

    	// make key axis range scroll with the data (at a constant range size of 8):
    	plots_[i]->xAxis->setRange(key, 8, Qt::AlignRight);
    	plots_[i]->replot();
	}
    
}
