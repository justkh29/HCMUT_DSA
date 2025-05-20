#include "kDTree.hpp"

////////////////////////////////// MERGE SORT //////////////////////////////////
void merge(vector<vector<int>> &points, int left, int mid, int right, int alpha) 
{
	int n1 = mid - left + 1;
    int n2 = right - mid;
	int i = 0, j = 0;
    vector<vector<int>> L(n1), R(n2);

    for (i = 0; i < n1; i++)
    {
    	L[i] = points[left + i];
	}    
    for (j = 0; j < n2; j++)
    {
    	R[j] = points[mid + 1 + j];
	}
	i = 0;
	j = 0;
    int k = left;
    while (i < n1 && j < n2) 
	{
        if (L[i][alpha] <= R[j][alpha]) 
		{
            points[k] = L[i];
            i++;
        } 
		else 
		{
            points[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
	{
        points[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) 
	{
        points[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<int>> &points, int left, int right, int alpha) 
{
    if (left < right) 
	{
        int mid = left + (right - left) / 2;

        mergeSort(points, left, mid, alpha);
        
        mergeSort(points, mid + 1, right, alpha);

        merge(points, left, mid, right, alpha);
    }
}


void merge_withLabels(vector<pair<vector<int>, int>>& pointsWithLabels, int left, int mid, int right, int alpha) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
	
	int i = 0, j = 0;
    
    vector<pair<vector<int>, int>> L(n1), R(n2);

    for (i = 0; i < n1; i++)
    {
    	L[i] = pointsWithLabels[left + i];
	}
    for (j = 0; j < n2; j++)
    {
    	R[j] = pointsWithLabels[mid + 1 + j];
	}
	i=0;
	j=0;
    int k = left;
    while (i < n1 && j < n2) 
	{
        if (L[i].first[alpha] <= R[j].first[alpha]) 
		{
            pointsWithLabels[k] = L[i];
            i++;
        } 
		else 
		{
            pointsWithLabels[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
	{
        pointsWithLabels[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
	{
        pointsWithLabels[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_WithLabels(vector<pair<vector<int>, int>>& pointsWithLabels, int left, int right, int alpha) 
{
    if (left >= right) 
	{
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort_WithLabels(pointsWithLabels, left, mid, alpha); 
    mergeSort_WithLabels(pointsWithLabels, mid + 1, right, alpha); 
    merge_withLabels(pointsWithLabels, left, mid, right, alpha); 
}
////////////////////////////////// MERGE SORT //////////////////////////////////

////////////////////////////////// DISTANCE //////////////////////////////////

double disCal(const vector<int> &p1, const vector<int> &p2) 
{
    double dis = 0;
    for (int i = 0; i < p1.size(); ++i) 
	{
        dis += (p1[i] - p2[i]) * (p1[i] - p2[i]);
    }
    return dis;
}

double farthestDis(vector<kDTreeNode*> &bestList, const vector<int> &target) 
{
    double maxDis = 0;
    for (kDTreeNode *node : bestList) 
	{
        double dis = disCal(node->data, target);
        if (dis > maxDis) 
		{
            maxDis = dis;
        }
    }
    return maxDis;
}
////////////////////////////////// DISTANCE //////////////////////////////////


////////////////////////////////// NEIGHBOUR FUNCTION //////////////////////////////////
void updateBestList(kDTreeNode *candidate, const vector<int>& target, int kth, vector<kDTreeNode*>& bestList) 
{
    double candidateDistance = disCal(candidate->data, target);
    for (int i = 0; i < bestList.size(); ++i) 
	{
        if (candidateDistance < disCal(bestList[i]->data, target)) 
		{
            bestList.insert(bestList.begin() + i, candidate);
            if (bestList.size() > kth) 
			{
                bestList.pop_back();
            }
            return;
        }
    }
    if (bestList.size() < kth) 
	{
        bestList.push_back(candidate);
    }
}
////////////////////////////////// NEIGHBOUR FUNCTION //////////////////////////////////


////////////////////////////////// kD TREE //////////////////////////////////
void kDTree::rec_In(kDTreeNode *temp, bool &isFirst) const 
{
    if (temp == nullptr) 
	{
        return;
    }

    rec_In(temp->left, isFirst);

    if (!isFirst) cout << " ";
	cout << *temp;
	isFirst = false;
    rec_In(temp->right, isFirst);
}

void kDTree::inorderTraversal() const
{
	bool isFirst = true;
	this->rec_In(root, isFirst);
}

void kDTree::rec_Pre(kDTreeNode *temp, bool &isFirst) const
{
	if (temp == nullptr) 
	{
        return;
    }
    
    if (!isFirst) cout << " ";
	cout << *temp;
	isFirst = false;
	
    rec_Pre(temp->left, isFirst);

    rec_Pre(temp->right, isFirst);
}

void kDTree::preorderTraversal() const
{
	bool isFirst = true;
	this->rec_Pre(root, isFirst);
}

void kDTree::rec_Post(kDTreeNode *temp, bool &isFirst) const 
{
    if (temp == nullptr) 
	{
        return;
    }
    rec_Post(temp->left, isFirst);
    rec_Post(temp->right, isFirst);
    if (!isFirst) cout << " ";
	cout << *temp;
	isFirst = false;
}

void kDTree::postorderTraversal() const
{
	bool isFirst = true;
	this->rec_Post(root, isFirst);
}
	
int kDTree::findHeight(kDTreeNode *temp) const
{
	if (temp == nullptr)
	{
		return 0;
	}
	int lHeight = findHeight(temp->left);
	
	int rHeight = findHeight(temp->right);
	
	return max(lHeight, rHeight) + 1;
}

int kDTree::height() const
{
	return this->findHeight(root);
}

int kDTree::leafCount() const
{
	return this->countLeaf(root);
}

int kDTree::countLeaf(kDTreeNode *temp) const
{
	if (temp == nullptr) return 0;
	if (temp->left == nullptr && temp->right == nullptr)
	{
		return 1;
	}
	int lLeaf = countLeaf(temp->left);
	int rLeaf = countLeaf(temp->right);
	return lLeaf + rLeaf;
}

void kDTree::insert(const vector<int> &point)
{
	this->root = this->recAdd(root, point, 0);
	this->size++;
}

kDTreeNode *kDTree::recAdd(kDTreeNode *temp, const vector<int> &point, int level)
{
	if (temp == nullptr) 
	{
        return new kDTreeNode(point);
    } 
    int alpha = level % this->k;
    if (point[alpha] < temp->data[alpha]) 
	{
        temp->left = recAdd(temp->left, point, level + 1);
    } 
	else 
	{

        temp->right = recAdd(temp->right, point, level + 1);
    }
    return temp;
}

void kDTree::remove(const vector<int> &point)
{
	recRem(root, point, 0);
}

void kDTree::recRem(kDTreeNode *&temp, const vector<int>& point, int level) 
{

    if (temp == nullptr) 
	{
        return; 
    }

    int alpha = level % k;

    if (temp->data == point) 
	{
        if (temp->left == nullptr && temp->right == nullptr) 
		{
            delete temp;
            temp = nullptr;
            this->size--;
            return;
        }
        if (temp->right != nullptr) 
		{
            kDTreeNode *replacement = findMin(temp->right, alpha, level + 1);
            temp->data = replacement->data;
            recRem(temp->right, replacement->data, level + 1);
        } 
		else 
		{
            kDTreeNode *replacement = findMin(temp->left, alpha, level + 1);
            temp->data = replacement->data;
            temp->right = temp->left;
            temp->left = nullptr;
            recRem(temp->right, replacement->data, level + 1);
        }
    } 
	else 
	{
        if (point[alpha] < temp->data[alpha]) 
		{
            recRem(temp->left, point, level + 1);
        } 
		else 
		{
            recRem(temp->right, point, level + 1);
        }
    }
}

kDTreeNode *kDTree::findMin(kDTreeNode *temp, int alpha, int level) 
{
    if (temp == nullptr) 
	{
        return nullptr;
    }

    int curAlpha = level % k;
    if (curAlpha == alpha) 
	{
        if (temp->left == nullptr) 
		{
            return temp;
        } 
		else 
		{
            return findMin(temp->left, alpha, level + 1);
        }
    } 
	else 
	{
        kDTreeNode *lMin = findMin(temp->left, alpha, level + 1);
        kDTreeNode *rMin = findMin(temp->right, alpha, level + 1);
        kDTreeNode *minNode = temp;

        if (lMin != nullptr && lMin->data[alpha] < minNode->data[alpha]) 
		{
            minNode = lMin;
        }
        if (rMin != nullptr && rMin->data[alpha] < minNode->data[alpha]) 
		{
            minNode = rMin;
        }
        return minNode;
    }
}

bool kDTree::search(const vector<int> &point)
{
	return recSearch(root, point, 0);
}

bool kDTree::recSearch(kDTreeNode *temp, const vector<int> &point, int level)
{
	if (temp == nullptr) 
	{
        return false; 
    }

    if (temp->data == point) 
	{
        return true; 
    }
    int alpha = level % k;

    if (point[alpha] < temp->data[alpha]) 
	{
        return recSearch(temp->left, point, level + 1); 
    } 
	else 
	{
        return recSearch(temp->right, point, level + 1); 
	}
}

void kDTree::buildTree(const vector<vector<int>> &pointList)
{
	this->root = this->recBuildTree(pointList, 0);
}
kDTreeNode *kDTree::recBuildTree(const vector<vector<int>> &pointList, int level)
{
    if (pointList.empty()) 
	{
        return nullptr;
    }

    int alpha = level % k;

    vector<vector<int>> sortedPoints = pointList;
	mergeSort(sortedPoints, 0, sortedPoints.size() - 1, alpha);

    int medianIndex = sortedPoints.size() / 2;
    if (sortedPoints.size() % 2 == 0 && medianIndex > 0) 
	{
        medianIndex--; 
    }
    
    while (medianIndex > 0 && sortedPoints[medianIndex][alpha] == sortedPoints[medianIndex - 1][alpha]) 
	{
    	medianIndex--;
	}
	
    vector<int> medianPoint = sortedPoints[medianIndex];

    kDTreeNode *node = new kDTreeNode(medianPoint);
	size++;

    vector<vector<int>> leftPoints(sortedPoints.begin(), sortedPoints.begin() + medianIndex);
    node->left = recBuildTree(leftPoints, level + 1);

    vector<vector<int>> rightPoints(sortedPoints.begin() + medianIndex + 1, sortedPoints.end());
    node->right = recBuildTree(rightPoints, level + 1);

    return node;
}

void kDTree::buildTree_withLabel(const vector<vector<int>> &pointList, const vector<int> &label) 
{
	this->root = this->recBuild_TwL(pointList, label, 0);
}

kDTreeNode* kDTree::recBuild_TwL(const vector<vector<int>>& pointList, const vector<int>& labels, int level) {
    if (pointList.empty()) 
	{
        return nullptr;
    }

    int alpha = level % k;

    vector<pair<vector<int>,int>> point;
    for (size_t i = 0; i < pointList.size(); ++i) 
	{
        point.push_back(make_pair(pointList[i], labels[i]));
    }

    mergeSort_WithLabels(point, 0, point.size() - 1, alpha);

    int medianIndex = point.size() / 2;
    while (medianIndex > 0 && point[medianIndex].first[alpha] == point[medianIndex - 1].first[alpha]) 
	{
        medianIndex--;
    }

    vector<int> medianPoint = point[medianIndex].first;
    int medianLabel = point[medianIndex].second;

    kDTreeNode *node = new kDTreeNode(medianPoint, medianLabel);

    vector<vector<int>> leftPoint;
    vector<int> leftLabel;
    vector<vector<int>> rightPoint;
    vector<int> rightLabel;

    for (int i = 0; i < medianIndex; ++i) {
        leftPoint.push_back(point[i].first);
        leftLabel.push_back(point[i].second);
    }
    for (size_t i = medianIndex + 1; i < point.size(); ++i) {
        rightPoint.push_back(point[i].first);
        rightLabel.push_back(point[i].second);
    }

    node->left = recBuild_TwL(leftPoint, leftLabel, level + 1);
    node->right = recBuild_TwL(rightPoint, rightLabel, level + 1);

    return node;
}

void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *&best)
{
	best = nullptr;
	check_Near(root, target, best, 0);
}

void kDTree::check_Near(kDTreeNode *temp, const vector<int>& target, kDTreeNode *&best, int level) 
{
    if (temp == nullptr) 
	{
        return; 
    }

    int alpha = level % k;

    kDTreeNode *nextNode = nullptr;
    kDTreeNode *oppNode = nullptr;
    if (target[alpha] < temp->data[alpha]) 
	{
        nextNode = temp->left;
        oppNode = temp->right;
    } 
	else 
	{
        nextNode = temp->right;
        oppNode = temp->left;
    }

    check_Near(nextNode, target, best, level + 1);

    if (best == nullptr || disCal(temp->data, target) < disCal(best->data, target)) 
	{
        best = temp;
    }

    double d = abs(temp->data[alpha] - target[alpha]);
    double R = disCal(best->data, target);

    if (d * d < R) 
	{
        check_Near(oppNode, target, best, level + 1);
    }
}

void kDTree::kNearestNeighbour(const vector<int> &target, int kth, vector<kDTreeNode*> &bestList)
{
	check_kNear(root, target, kth , bestList, 0);
}
void kDTree::check_kNear(kDTreeNode *temp, const vector<int>& target, int kth, vector<kDTreeNode*>& bestList, int level) 
{
    if (temp == nullptr) 
	{
        return;
    }

    int alpha = level % k;

    kDTreeNode *nextNode = nullptr;
    kDTreeNode *oppNode = nullptr;
    if (target[alpha] < temp->data[alpha]) 
	{
        nextNode = temp->left;
        oppNode = temp->right;
    } 
	else 
	{
        nextNode = temp->right;
        oppNode = temp->left;
    }

    check_kNear(nextNode, target, kth, bestList, level + 1);

    updateBestList(temp, target, kth, bestList);

    double d = abs(temp->data[alpha] - target[alpha]);
    double r = farthestDis(bestList, target); 

    if (d * d < r * r || bestList.size() < kth) 
	{
        check_kNear(oppNode, target, kth, bestList, level + 1);
    }
}

////////////////////////////////// kD TREE //////////////////////////////////


////////////////////////////////// kNN //////////////////////////////////

void kNN::fit(Dataset &X_train, Dataset &y_train)
{
    this->X_train = &X_train;
    this->y_train = &y_train;

    int dimen = X_train.data.front().size();
    kdtree.setK(dimen);

    vector<vector<int>> pointList;
    vector<int> label;
    for (const auto &row : X_train.data)
    {
        vector<int> point(row.begin(), row.end());
        pointList.push_back(point);
    }
    for (const auto &row : y_train.data)
    {
        label.push_back(row.front());
    }

    kdtree.buildTree_withLabel(pointList, label);
}

Dataset kNN::predict(Dataset &X_test)
{
    Dataset res;
    res.columnName.push_back("label");

    vector<vector<int>> testData;
    for (const auto &row : X_test.data)
    {
        vector<int> point(row.begin(), row.end());
        testData.push_back(point);
    }

    for (const auto &point : testData)
    {
        vector<kDTreeNode*> bestList;
        kdtree.kNearestNeighbour(point, this->k, bestList);

        vector<int> countLabels(10, 0); 
        for (const auto &node : bestList)
        {
            if (node != nullptr)
            {
                countLabels[node->label]++;
            }
        }

        int maxLabel = 0;
        int maxCount = countLabels[0];
        for (int i = 1; i < countLabels.size(); ++i)
        {
            if (countLabels[i] > maxCount)
            {
                maxCount = countLabels[i];
                maxLabel = i;
            }
        }
        list<int> predictedLabel = {maxLabel};
        res.data.push_back(predictedLabel);
    }

    return res;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    int count = 0;
    auto it_test = y_test.data.begin();
    auto it_pred = y_pred.data.begin();
    while (it_test != y_test.data.end() && it_pred != y_pred.data.end())
    {
        if (it_test->front() == it_pred->front())
        {
            count++;
        }
        ++it_test;
        ++it_pred;
    }

    return count * 1.0 / y_test.data.size();
}

