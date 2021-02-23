#include <ConfigQt.h>

//---------------------------------------------------------------------------------------------------------------------
ConfigQt::ConfigQt(QWidget *parent) :
    QMainWindow(parent)
    {
		centralWidget_ = new QWidget();
		mainLayout_ = new QVBoxLayout();
		centralWidget_->setLayout(mainLayout_);

		setCentralWidget(centralWidget_);
		this->setWindowTitle("Config gui");

		buildPanel();
	}

//---------------------------------------------------------------------------------------------------------------------
ConfigQt::~ConfigQt()
{

}

//---------------------------------------------------------------------------------------------------------------------
void ConfigQt::buildPanel()
{
	plotsDataLayout_ = new QHBoxLayout();

	plotsDataLabel_ = new QLabel("Specify N Plots: Fil / Col / N lines"); 
    plotsDataLayout_->addWidget(plotsDataLabel_);

	filText_ = new QLineEdit();
	filText_->setMaximumWidth(50);
    plotsDataLayout_->addWidget(filText_);

	colText_ = new QLineEdit();
	colText_->setMaximumWidth(50); 
    plotsDataLayout_->addWidget(colText_);

	nlinesText_ = new QLineEdit();
	nlinesText_->setMaximumWidth(50); 
    plotsDataLayout_->addWidget(nlinesText_);

	mainLayout_->addLayout(plotsDataLayout_);

	// **************************************************
	socketDataLayout_ = new QHBoxLayout();

	socketDataLabel_ = new QLabel("Specify use internal ip or external"); 
    socketDataLayout_->addWidget(socketDataLabel_);

	socketBut_ = new QPushButton("Set IP"); 
	socketBut_->setMaximumWidth(110); 
	socketBut_->setStyleSheet("background-color : yellow");
	socketDataLayout_->addWidget(socketBut_);
    connect(socketBut_, SIGNAL (released()), this, SLOT (configSocket()));

	ipText_ = new QLineEdit("127.0.0.1");
	ipText_->setMaximumWidth(100);
    socketDataLayout_->addWidget(ipText_);
	
	portText_ = new QLineEdit("8080");
	portText_->setMaximumWidth(50);
    socketDataLayout_->addWidget(portText_);

	mainLayout_->addLayout(socketDataLayout_);

	// **************************************************
	openWindowLayout_ = new QHBoxLayout();

	openWindowBut_ = new QPushButton("Open Plot Window"); 
	openWindowLayout_->addWidget(openWindowBut_);
    connect(openWindowBut_, SIGNAL (released()), this, SLOT (openPlotsWindow()));

	mainLayout_->addLayout(openWindowLayout_);

}

//---------------------------------------------------------------------------------------------------------------------
void ConfigQt::closeEvent(QCloseEvent *event) {

}

//---------------------------------------------------------------------------------------------------------------------
void ConfigQt::openPlotsWindow()
{	
	QString qFil = filText_->text();
	double fil = qFil.toDouble(); 

	QString qCol = colText_->text();
	double col = qCol.toDouble(); 

	QString qNlines = nlinesText_->text();
	double nlines = qNlines.toDouble(); 

	std::cout << "Params: " << fil << "|" << col << "|" << nlines << std::endl;
	std::cout << "IP: " << ip_  << " Port: " << port_ << std::endl;

	if(lastPlotsQt_ != nullptr){
        lastPlotsQt_->close();
        lastPlotsQt_ = nullptr;
    }

	lastPlotsQt_ = new PlotsQt();
	int nplots = lastPlotsQt_->configure(fil, col, nlines, ip_, port_);
	if(nplots == 0){
		std::cout << "returned 0 nplots" << std::endl;
        lastPlotsQt_ = nullptr;
	}else{
		std::cout << "returned: " << nplots << std::endl;
		lastPlotsQt_->setModal(true);
		lastPlotsQt_->resize(500,500);
    	lastPlotsQt_->exec();
	}
    
}

//---------------------------------------------------------------------------------------------------------------------
void ConfigQt::configSocket()
{	
	QString qIP = ipText_->text();
    ip_ = qIP.toStdString();

	QString qPort = portText_->text();
    port_ = qPort.toInt();

	socketBut_->setStyleSheet("background-color : green");
	std::cout << "Set IP: " << ip_ << std::endl;
    
}
