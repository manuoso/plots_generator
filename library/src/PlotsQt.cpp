#include <PlotsQt.h>

//---------------------------------------------------------------------------------------------------------------------
PlotsQt::PlotsQt(QWidget *parent)
    {
		mainLayout_ = new QGridLayout();
		this->setLayout(mainLayout_);

		this->setWindowTitle("Plots gui");
	}

//---------------------------------------------------------------------------------------------------------------------
PlotsQt::~PlotsQt()
{
	stopAll_ = true;
	dataThread_->join();
}

//---------------------------------------------------------------------------------------------------------------------
void PlotsQt::closeEvent(QCloseEvent *event) {
	stopAll_ = false;
	try {
		serverSocket_->close();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------------------------------
int PlotsQt::configure(int _rows, int _cols, int _nLines, std::string _ip, int _port)
{	
	if(nLines_ > 5){
		std::cout << "Too much Lines in same graph" << std::endl;
		return 0;
	}

	ip_ = _ip;
	port_ = _port;
	nLines_ = _nLines;
	nPlots_ = _rows * _cols * _nLines;
	
	for(int i = 0; i < nPlots_; i++){
		data_.push_back(0);
	}

	QPen pen; 
	pen.setWidthF(3);
	
	lineColors_.push_back(QColor(255, 0, 0));
	lineColors_.push_back(QColor(0, 255, 0));
	lineColors_.push_back(QColor(0, 0, 255));
	lineColors_.push_back(QColor(128, 0, 128));
	lineColors_.push_back(QColor(0, 255, 255));
	lineColors_.push_back(QColor(255, 255, 0));
	lineColors_.push_back(QColor(34, 34, 34));

	lineStyle_.push_back(Qt::SolidLine);
	lineStyle_.push_back(Qt::DotLine);
	lineStyle_.push_back(Qt::DashLine);
	lineStyle_.push_back(Qt::DashDotLine);
	lineStyle_.push_back(Qt::DashDotDotLine);

	int cont = 0, contColor = 0;
	for(int j = 0; j < _rows; j++){
		for(int k = 0; k < _cols; k++){
			if(contColor > lineColors_.size()){
				contColor = 0;
			}

			pen.setColor(lineColors_[contColor]);
			plots_.push_back(new QCustomPlot());

			for(int l = 0; l < _nLines; l++){
				pen.setStyle(lineStyle_[l]);
				plots_[cont]->addGraph(); 
        		plots_[cont]->graph(l)->setPen(pen);
			}

			mainLayout_->addWidget(plots_[cont], j, k, 1, 1);
			cont++;
			contColor++;
		}
	}
	
	dataThread_ = new std::thread(&PlotsQt::getData, this);

	dataTimer_ = new QTimer(this);
	connect(dataTimer_, SIGNAL(timeout()), this, SLOT(realTimePlot()));
	dataTimer_->start(0);

	return nPlots_;
}

//---------------------------------------------------------------------------------------------------------------------
bool PlotsQt::getData(){
	try {
		boost::asio::io_service io_service;
		acc_ = new boost::asio::ip::tcp::acceptor(io_service, boost::asio::ip::tcp::endpoint{ boost::asio::ip::address::from_string(ip_), port_});

		boost::system::error_code ec;
		serverSocket_ = new boost::asio::ip::tcp::socket(io_service);
		acc_->accept(*serverSocket_, ec);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	
	while(!stopAll_) {
		try {
			std::vector<float> recSocket;
			recSocket.resize(nPlots_);
			boost::system::error_code recEc;
			std::size_t length = boost::asio::read(*serverSocket_, boost::asio::buffer(recSocket), recEc);

			dataMutex_.lock();
			for(int i = 0; i < nPlots_; i++){
				data_[i] = recSocket[i];
			}
			dataMutex_.unlock();

			// std::cout << "length rec: " << length << std::endl;

			// std::cout << "data: ";
			// for(int i = 0; i < nPlots_; i++){
			// 	std::cout << recSocket[i] << " , ";
			// }
			// std::cout << std::endl;
			// std::cout << "----------" << std::endl;

		}
		catch (std::exception &e) {
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
	
	float maxValue = std::numeric_limits<float>::min();
	float minValue = std::numeric_limits<float>::max();

    if (key-lastPointKey > 0.005) { // at most add point every 2 ms
		int cont = 0;
		for(int i = 0; i < nPlots_; i = i+nLines_){
			for(int j = 0; j < nLines_; j++){
				dataMutex_.lock();
				plots_[cont]->graph(j)->addData(key, data_[i+j]);
				dataMutex_.unlock();
			}
			cont++;
		}

        lastPointKey = key;
    }

	int nplots = nPlots_/nLines_;
	for(int i = 0; i < nplots; i++){
		plots_[i]->graph(0)->rescaleAxes(false);

    	// make key axis range scroll with the data (at a constant range size of 8):
    	plots_[i]->xAxis->setRange(key, 8, Qt::AlignRight);
    	plots_[i]->replot();
	}
    
}
