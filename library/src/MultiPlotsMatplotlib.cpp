#include <MultiPlotsMatplotlib.h>

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsMatplotlib::MultiPlotsMatplotlib()
{
	
}

//---------------------------------------------------------------------------------------------------------------------
MultiPlotsMatplotlib::~MultiPlotsMatplotlib()
{
	
}

//---------------------------------------------------------------------------------------------------------------------
int MultiPlotsMatplotlib::configure(std::string _name, int _rows, int _cols)
{
	name_ = _name;

	nRows_ = _rows;
	nCols_ = _cols;
	nPlots_ = _rows * _cols;

	std::vector<float> initVect = {0.0};
	for(int i = 0; i < nPlots_; i++){
		storedDataX_.insert(std::make_pair(i, initVect));
		storedDataY_.insert(std::make_pair(i, initVect));
	}

	lineColors_.push_back("b-");
	lineColors_.push_back("g-");
	lineColors_.push_back("r-");
	lineColors_.push_back("m-");
	lineColors_.push_back("c-");
	lineColors_.push_back("y-");
	lineColors_.push_back("k-");

	return nPlots_;
}

//---------------------------------------------------------------------------------------------------------------------
bool MultiPlotsMatplotlib::setPlotData(std::vector<float> _dataX, std::vector<float> _dataY)
{	
	if(_dataX.size() > nPlots_ || _dataY.size() > nPlots_){
		return false;
	}

	plt::clf();

	plt::suptitle(name_.c_str());

	int contColor = 0;
	for(int i = 0; i < nPlots_; i++){
		if(storedDataX_[i].size() > delData_){
			storedDataX_[i].erase(storedDataX_[i].begin());
		}

		if(storedDataY_[i].size() > delData_){
			storedDataY_[i].erase(storedDataY_[i].begin());
		}

		storedDataX_[i].push_back(_dataX[i]);
		storedDataY_[i].push_back(_dataY[i]);

		// plt::figure(i+1);
		plt::subplot(nRows_, nCols_, i+1);
		if(contColor > 6){
			contColor = 0;
		}
		plt::plot(storedDataX_[i], storedDataY_[i], lineColors_[contColor].c_str());

		plt::pause(0.001);

		contColor++;	
	}

	return true;
}
