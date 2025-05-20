#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
class Node {
public:
    T data; 
    Node* next; 
    Node* prev;

    Node(T value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};




template <typename T>
class LinkedList : public List<T>
{
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	public:
		LinkedList()
		{
			head = nullptr;
			tail = nullptr;
			size = 0;
		}
		~LinkedList()
		{
			clear();
		}

		void push_back(T value) override
		{
			Node<T>* new_node = new Node<T>(value);
			if (head == nullptr)
			{
				head = tail = new_node;
			}
			else
			{
				tail->next = new_node;
				new_node->prev = tail;
				tail = new_node;
			}
			size++;
		}
		void push_front(T value) override
		{
			Node<T>* new_node = new Node<T>(value);
			if (head == nullptr)
			{
				head = tail = new_node;
			}
			else 
			{
				new_node->next = head;
				head->prev = new_node;
				head = new_node;
			}
			size++;
		}
		void insert(int index, T value) override
		{
		    if (index < 0 || index >= size) return;
		    
		    if (index == 0)
		    {
		        push_front(value);
		        return;
		    }
		    Node<T>* new_node = new Node<T>(value);
		    Node<T>* temp = head;
		    for (int i = 1; i < index; i++) 
		    {
		        temp = temp->next;
		    }
		    new_node->next = temp->next;
		    new_node->prev = temp;
		    if (temp->next != nullptr) 
		    {
		        temp->next->prev = new_node;
		    }
		    temp->next = new_node;
		    if (new_node->next == nullptr)
		    {
		        tail = new_node;
		    }
		    size++;
		}

		void remove(int index) override
		{
		    if (index < 0 || index >= size) return; 
		    if (size == 1)
		    {
		        delete head; 
		        head = tail = nullptr;
		        size = 0;
		        return;
		    }
		    if (index == 0)
		    {
		        Node<T>* temp = head;
		        head = head->next;
		        head->prev = nullptr;
		        delete temp; 
		        size--;
		        return;
		    }
		    if (index == size - 1)
		    {
		        Node<T>* temp = tail;
		        tail = tail->prev;
		        tail->next = nullptr;
		        delete temp; 
		        size--;
		        return;
		    }
		    
		    Node<T>* temp = head;
		    for (int i = 0; i < index; i++)
		    {
		        temp = temp->next;
		    }
		    temp->prev->next = temp->next;
		    if (temp->next != nullptr)
		    {
		        temp->next->prev = temp->prev;
		    }
		    delete temp;
		    size--;
		}

		T& get(int index) const override
		{
			if (index < 0 || index >= size)
			{
				throw std::out_of_range("get(): Out of range");
			}
			Node<T>* temp = head;
			for (int i=0;i<index;i++)
			{
				temp=temp->next;
			}
			return temp->data;
		}
		int length() const override 
		{
			return size;
		}
		void clear() override
		{
			while (head != nullptr)
			{
				Node<T>* next = head->next;
				delete head;
				head = next;
			}
			size = 0;
		}
		void print() const override
		{
			Node<T>* temp = head;
			while (temp->next != nullptr)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << temp->data;
			cout << endl;
		}
		void reverse() override 
        {
            if (head == nullptr || head == tail) return;
        
            Node<T>* front = head;
            Node<T>* back = tail;
        
            while (front != back && front->prev != back)
            {
                swap(front->data, back->data);
        
                front = front->next;
                back = back->prev;
            }
        }
};

class Dataset {
private:
    LinkedList<LinkedList<int>*>* data;
    //You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columnName = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    LinkedList<LinkedList<int>*>* getData() const;
};

class kNN {
private:
    int k;
    Dataset X_train;
    Dataset y_train;
    //You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed
