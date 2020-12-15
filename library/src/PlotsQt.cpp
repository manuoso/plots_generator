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

		// plots_[0] = new QCustomPlot();
		// mainLayout_->addWidget(plots_[0], 0, 0, 1, 1);
	}

//---------------------------------------------------------------------------------------------------------------------
PlotsQt::~PlotsQt()
{
	stopAll_ = true;
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

	dataTimer_ = new QTimer(this);
	connect(dataTimer_, SIGNAL(timeout()), this, SLOT(realTimePlot()));
	dataTimer_->start(0);

	return true;
}

//---------------------------------------------------------------------------------------------------------------------
bool PlotsQt::getData()
{

}

//---------------------------------------------------------------------------------------------------------------------
void PlotsQt::realTimePlot()
{	
	static QTime time(QTime::currentTime());

    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.005) { // at most add point every 2 ms
		for(int i = 0; i < nPlots_; i++){
			plots_[i]->graph(0)->addData(key, data_[i]);
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
