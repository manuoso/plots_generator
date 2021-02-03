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
bool PlotsQt::configure(bool _enableTs, int _rows, int _cols, int _nLines)
{	
	enableTs_ = _enableTs;
	
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

	if(nLines_ > 5){
		std::cout << "Too much Lines in same graph" << std::endl;
		return false;
	}

	nLines_ = _nLines;
	nPlots_ = _rows * _cols * _nLines;
	
	for(int i = 0; i < nPlots_; i++){
		dataY_.push_back(0);
	}

	for(int i = 0; i < nPlots_; i++){
		dataX_.push_back(0);
	}
	
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

	if(_enableTs){
		dataTimer_ = new QTimer(this);
		connect(dataTimer_, SIGNAL(timeout()), this, SLOT(realTimePlot()));
		dataTimer_->start(0);
	}else{
		connect(this, &PlotsQt::updateplotXY , this, &PlotsQt::plotDataXY);
	}

	return true;
}

//---------------------------------------------------------------------------------------------------------------------
bool PlotsQt::getData(){
	try {
		boost::asio::io_service io_service;
		acc_ = new boost::asio::ip::tcp::acceptor(io_service, boost::asio::ip::tcp::endpoint{ boost::asio::ip::address::from_string("127.0.0.1"), 8080 });

		boost::system::error_code ec;
		socket_ = new boost::asio::ip::tcp::socket(io_service);
		acc_->accept(*socket_, ec);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	
	while(!stopAll_) {
		try {			
			boost::system::error_code recEc;
			std::vector<float> inity;
			inity.resize(1);
			std::size_t lengthIY = boost::asio::read(*socket_, boost::asio::buffer(inity), recEc);

			if(inity[0] == 1){
				std::vector<float> recSocket1;
				recSocket1.resize(nPlots_);
				std::size_t length1 = boost::asio::read(*socket_, boost::asio::buffer(recSocket1), recEc);

				dataMutex_.lock();
				for(int i = 0; i < recSocket1.size(); i++){
					dataY_[i] = recSocket1[i];
				}
				dataMutex_.unlock();

				// std::cout << "data Y: ";
				// for(int i = 0; i < nPlots_; i++){
				// 	std::cout << recSocket1[i] << " , ";
				// }
				// std::cout << std::endl;
			}

			if(!enableTs_){	
				std::vector<float> initx;
				initx.resize(1);
				std::size_t lengthIX = boost::asio::read(*socket_, boost::asio::buffer(initx), recEc);

				if(initx[0] == 2){
					std::vector<float> recSocket2;
					recSocket2.resize(nPlots_);
					std::size_t length2 = boost::asio::read(*socket_, boost::asio::buffer(recSocket2), recEc);

					dataMutex_.lock();
					for(int i = 0; i < recSocket2.size(); i++){
						dataX_[i] = recSocket2[i];
					}
					dataMutex_.unlock();

					// std::cout << "data X: ";
					// for(int i = 0; i < nPlots_; i++){
					// 	std::cout << recSocket2[i] << " , ";
					// }
					// std::cout << std::endl;
					// std::cout << "----------" << std::endl;

					emit updateplotXY(); 

				}
			}
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}

		// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return true;
}

//---------------------------------------------------------------------------------------------------------------------
void PlotsQt::plotDataXY(){

	int cont = 0;
	for(int i = 0; i < nPlots_; i = i+nLines_){
		for(int j = 0; j < nLines_; j++){
			// plots_[0]->clearGraphs(); 

			dataMutex_.lock();
			plots_[cont]->graph(j)->addData(dataX_[i+j], dataY_[i+j]);
			dataMutex_.unlock();
		}
		cont++;
	}

	int nplots = nPlots_/nLines_;
	for(int i = 0; i < nplots; i++){
		plots_[i]->graph(0)->rescaleAxes();

    	plots_[i]->replot();
	}
}

//---------------------------------------------------------------------------------------------------------------------
void PlotsQt::realTimePlot()
{	
	static QTime time(QTime::currentTime());

    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.005) { // at most add point every 2 ms
		int cont = 0;
		for(int i = 0; i < nPlots_; i = i+nLines_){
			for(int j = 0; j < nLines_; j++){
				dataMutex_.lock();
				plots_[cont]->graph(j)->addData(key, dataY_[i+j]);
				dataMutex_.unlock();
			}
			cont++;
		}

        lastPointKey = key;
    }
	
	int nplots = nPlots_/nLines_;
	for(int i = 0; i < nplots; i++){
		plots_[i]->graph(0)->rescaleAxes();

    	// make key axis range scroll with the data (at a constant range size of 8):
    	plots_[i]->xAxis->setRange(key, 8, Qt::AlignRight);
    	plots_[i]->replot();
	}
    
}
