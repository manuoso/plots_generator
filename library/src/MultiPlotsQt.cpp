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

	

	return nPlots_;
}

//---------------------------------------------------------------------------------------------------------------------
bool MultiPlotsQt::setPlotData(std::vector<float> _dataX, std::vector<float> _dataY)
{	
	if(_dataX.size() > nPlots_ || _dataY.size() > nPlots_){
		return false;
	}

	

	return true;
}
