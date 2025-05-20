#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{
    vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
	int label;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    kDTreeNode(vector<int> data, int label, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = label;
        this->left = nullptr;
        this->right = nullptr;
    }
    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;
	int size;
public:
    kDTree(int k = 2)
    {
    	this->root = nullptr;
    	this->k = k;
    	this->size = 0;
	}
	
	void setK(int k)
	{
		this->k = k;
	}
	
	void delTree(kDTreeNode *node) 
	{
        if (node != nullptr) 
		{
            delTree(node->left);
            delTree(node->right);
            delete node;
        }
    }
    
    ~kDTree()
    {
    	this->delTree(root);
	}
	
	kDTreeNode* copy(const kDTreeNode *temp) 
	{
	    if (temp == nullptr) 
		{
	        return nullptr;
	    }
	    kDTreeNode *lCopy = copy(temp->left);
	    kDTreeNode *rCopy = copy(temp->right);
	    kDTreeNode *curNode = new kDTreeNode(temp->data, lCopy, rCopy);
	    return curNode;
	}
	
    const kDTree &operator=(const kDTree &other)
    {
		this->root = this->copy(other.root);
    	this->k = other.k;
    	this->size = other.size;
    	return *this;
	}
	
    kDTree(const kDTree &other)
    {
    	this->root = this->copy(other.root);
		this->k = other.k;
    	this->size = other.size;
	}
	
	void rec_In(kDTreeNode *temp, bool &isFirst) const;
    void inorderTraversal() const;
    
    void rec_Pre(kDTreeNode *temp, bool &isFirst) const;
    void preorderTraversal() const;
    
    void rec_Post(kDTreeNode *temp, bool &isFirst) const;
    void postorderTraversal() const;
    
    int findHeight(kDTreeNode *temp) const;
    int height() const;
    
    
    int nodeCount() const
    {
    	return this->size;
	}
	
	int countLeaf(kDTreeNode *temp) const;
    int leafCount() const;

    void insert(const vector<int> &point);
    kDTreeNode *recAdd(kDTreeNode *temp, const vector<int> &point, int level);
    
    void recRem(kDTreeNode *&temp, const vector<int>& point, int level); 
    kDTreeNode *findMin(kDTreeNode *temp, int alpha, int level);
    void remove(const vector<int> &point);
    
    bool recSearch(kDTreeNode *temp, const vector<int> &point, int level);
    bool search(const vector<int> &point);
    
    void buildTree(const vector<vector<int>> &pointList);
    kDTreeNode *recBuildTree(const vector<vector<int>> &pointList, int level);
    
    void buildTree_withLabel(const vector<vector<int>> &pointList, const vector<int> &label);
    kDTreeNode *recBuild_TwL(const vector<vector<int>> &pointList, const vector<int> &label, int level);
    
    void nearestNeighbour(const vector<int> &target, kDTreeNode *&best);
    void check_Near(kDTreeNode *temp, const vector<int>& target, kDTreeNode *&best, int level);
    
	void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode*> &bestList);
    void check_kNear(kDTreeNode *temp, const vector<int> &target, int kth, vector<kDTreeNode*> &bestList, int level);
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    kDTree kdtree;

public:
    kNN(int k = 5):k(k) {};
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

// Please add more or modify as needed
