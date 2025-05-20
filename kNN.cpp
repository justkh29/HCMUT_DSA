#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
/////////////////////////////// DATASET ///////////////////////////////
Dataset::Dataset() 
{
	data = new LinkedList<LinkedList<int>*>;
}

Dataset::~Dataset() 
{
	for (int i = 0; i < data->length(); i++) 
	{
		delete data->get(i);
	}
	delete data;
}

Dataset::Dataset(const Dataset& other) 
{
	data = new LinkedList<LinkedList<int>*>;
	for (int i = 0; i < other.data->length(); i++) 
	{
		LinkedList<int>* newList = new LinkedList<int>;
		for (int j = 0; j < other.data->get(i)->length(); j++) 
		{
			newList->push_back(other.data->get(i)->get(j));
		}
		data->push_back(newList);
	}
}

Dataset& Dataset::operator=(const Dataset& other) 
{
	if (this == &other) return *this;
	
	for (int i = 0; i < data->length(); i++) 
	{
		delete data->get(i);
	}
	delete data;
	
	data = new LinkedList<LinkedList<int>*>;
	for (int i = 0; i < other.data->length(); i++) 
	{
		LinkedList<int>* newList = new LinkedList<int>;
		for (int j = 0; j < other.data->get(i)->length(); j++) 
		{
			newList->push_back(other.data->get(i)->get(j));
		}
		data->push_back(newList);
	}
	
	return *this;
}

bool Dataset::loadFromCSV(const char* fileName) 
{
	ifstream infile(fileName);
	if (!infile.is_open() || infile.peek() == EOF) return false;
	
	string line;

	getline(infile, line);
	while (getline(infile, line)) 
	{
		stringstream ss(line);
		string value;
		LinkedList<int>* row = new LinkedList<int>;
		
		while (std::getline(ss, value, ',')) 
		{
			row->push_back(stoi(value));
		}
		
		data->push_back(row);
	}
	
	infile.close();
	return true;
}


void Dataset::printHead(int nRows, int nCols) const 
{
	if (nRows < 0 || nCols < 0) return;
	
	if (nRows > data->length()) nRows = data->length();
	
	if (nCols > data->get(0)->length()) nCols = data->get(0)->length();
	cout << "label" << " ";
	int tempRow =1;
	int count = 1;
	int i=1;
	for (count; count < nCols; count++) 
	{
		if (i > 28)
		{
			tempRow++;
			i=1;
		}
		if (count == nCols - 1)
		{
			cout << tempRow << "x" << i;
			break;
		}
		cout << tempRow <<"x" << i << " ";
		i++;
	}
	cout << endl;
	for (int i = 0; i < nRows; i++) 
	{
        for (int j = 0; j < nCols; j++) 
		{
            cout << data->get(i)->get(j);
            if (j < nCols - 1) cout << " "; 
        }
        if (i < nRows - 1) cout << endl; 
    }
}

void Dataset::printTail(int nRows, int nCols) const 
{
	if (nRows < 0 || nCols < 0) return;
	

	if (nRows > data->length()) nRows = data->length();
	

	if (nCols > data->get(0)->length()) nCols = data->get(0)->length();
	int tempCol,tempRow;
	if (nCols == data->get(0)->length())
	{
		cout << "label" << " ";
		tempCol = 1;
		tempRow = 1;
	}
	else
	{
		tempCol = 28 - nCols % 28 + 1;
		tempRow = 28 - nCols / 28;
	}
	int step = 0;
	for (int count = 1;count < nCols;count++)
	{

		if (tempCol > 28)
		{
			tempRow++;
			tempCol = 1;
		}
		cout << tempRow << "x" << tempCol << " ";
		if (tempRow == 28 && tempCol + 1 == 28)
		{
			cout << tempRow << "x" << tempCol + 1;
			break;
		}
		tempCol++;
	}
	cout << endl;
	for (int i = data->length() - nRows; i < data->length(); i++) {
        for (int j = data->get(i)->length() - nCols; j < data->get(i)->length(); j++) 
		{
			if (j == data->get(i)->length() - 1)
			{
				cout << data->get(i)->get(j);
				break;
			}
            cout << data->get(i)->get(j) << " ";
            
        }
        if (i < data->length() - 1) cout << endl; 
    }
}
void Dataset::getShape(int& nRows, int& nCols) const 
{
	nRows = data->length();
	nCols = data->get(0)->length();
}

void Dataset::columns() const 
{
	cout << "label" << endl;
	bool isLastColumn = false;
	int tempRow =1;
	for (int i = 0; i < data->get(0)->length(); i++) 
	{
		if (i > 28)
		{
			tempRow++;
			i=0;
		}
		if (tempRow >=28 && i == 28)
		{
			break;
		}
		cout << tempRow <<"x" << i + 1;
		if (i == data->get(0)->length() - 1) isLastColumn = true;
		if (!isLastColumn) cout << " ";
	}
	
}

bool Dataset::drop(int axis, int index, string columnName) {
  if (axis == 0) {
    if (index < 0 || index >= data->length()) {
      return false;
    }

    delete data->get(index);
    data->remove(index);

    return true;
  }

  if (axis == 1) {
    bool found = false;
    for (int i = 0; i < data->length(); i++) {
      if (to_string(data->get(i)->get(0)) == columnName) { 
        delete data->get(i);
        data->remove(i);
        found = true;
        break;
      }
    }

    if (!found) {
      return false;
    }

    return true;
  }

  return false;
}



Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const 
{
	if (endRow == -1) endRow = data->length() - 1;
	if (endCol == -1) endCol = data->get(0)->length() - 1;
	
	Dataset extracted;
	
	for (int i = startRow; i <= endRow; i++) 
	{
		LinkedList<int>* newList = new LinkedList<int>;
		for (int j = startCol; j <= endCol; j++) 
		{
			newList->push_back(data->get(i)->get(j));
		}
		extracted.data->push_back(newList);
	}
	
	return extracted;
}



LinkedList<LinkedList<int>*>* Dataset::getData() const
{
	return data;
}
/////////////////////////////// DATASET ///////////////////////////////

/////////////////////////////// TRAIN - TEST SPLIT ///////////////////////////////
void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test)
{
	int nRows = 0, nCols = 0;
	X.getShape(nRows, nCols);

	X_train = X.extract(0,nRows - nRows*test_size - 1,0,-1);
	X_test = X.extract(nRows - nRows*test_size,-1,0,-1);
	y_train = y.extract(0,nRows - nRows*test_size - 1,0,-1);
	y_test = y.extract(nRows - nRows*test_size,-1,0,-1);
}
/////////////////////////////// TRAIN - TEST SPLIT ///////////////////////////////


/////////////////////////////// kNN ALGORITHM ///////////////////////////////
kNN::kNN(int k) 
{
	this->k = k;
}
void kNN::fit(const Dataset& X_train, const Dataset& y_train) 
{
    this->X_train = X_train;
    this->y_train = y_train; 
}


Dataset kNN::predict(const Dataset& X_test) {
    Dataset predictions; 

    int nRows, nCols;
    X_test.getShape(nRows, nCols); 

    for (int i = 0; i < nRows; i++) {
        LinkedList<int>* testRow = X_test.getData()->get(i);
        pair<double, int>* nearest = new pair<double, int>[k];
        const double MAX_DOUBLE_VALUE = 1e308;
		
		for (int m = 0; m < k; m++) {
		    nearest[m].first = MAX_DOUBLE_VALUE;
		}

        for (int j = 0; j < X_train.getData()->length(); j++) {
            LinkedList<int>* trainRow = X_train.getData()->get(j);
            double dist = 0.0;
            for (int l = 0; l < nCols; l++) {
                dist += pow((trainRow->get(l)) - (testRow->get(l)), 2);
            }
            dist = sqrt(dist);

            if (dist < nearest[k-1].first) {
                nearest[k-1] = std::make_pair(dist, y_train.getData()->get(j)->get(0));
                for (int m = k - 1; m > 0 && nearest[m].first < nearest[m-1].first; m--) {
                    swap(nearest[m], nearest[m-1]);
                }
            }
        }

        int count[10] = {0};
        for (int m = 0; m < k; m++) {
            int label = nearest[m].second;
            count[label]++;
        }

        int maxCount = 0;
        int classification = -1;
        for (int n = 0; n < 10; n++) {
            if (count[n] > maxCount) {
                maxCount = count[n];
                classification = n;
            }
        }

        LinkedList<int>* predictionRow = new LinkedList<int>;
        predictionRow->push_back(classification);
        predictions.getData()->push_back(predictionRow);

        delete[] nearest;
    }

    return predictions; 
}


double kNN::score(const Dataset& y_test, const Dataset& y_pred) 
{
    int correct = 0;
    int nRows = y_test.getData()->length();

    for (int i = 0; i < nRows; i++) {
        if (y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0)) {
            correct++;
        }
    }

    return static_cast<double>(correct) / nRows;
}
