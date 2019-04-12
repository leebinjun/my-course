#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;


#include <cstdio>

template <class T>
class stack {
	public:
		virtual bool isEmpty() const = 0;
		virtual void push(const T &x) = 0;
		virtual T pop()=0;
		virtual T top() const = 0;
		virtual ~stack() { }
};

template <class T>
class seqStack:public stack<T> {
private:
	T *elem;
	int top_p;
	int maxSize;
	
	void doubleSpace();

public:
	seqStack(int initSize = 10) {
		elem = new T[initSize];
		maxSize = initSize; top_p = -1;
	}
	
	~seqStack() { delete[] elem; }
	
	bool isEmpty() const { return top_p = -1; }
	
	void push(const T &x) {
		if (top_p == maxSize - 1) doubleSpace();
		elem[++top_p] = x;
	}
	T pop() { return elem[top_p--]; }
	T top() const { return elem[top_p]; }
};


template <class T>
void seqStack<T>::doubleSpace() {
	T *tmp = elem;
	elem = new T[2 * maxSize];
	
	for (int i=0;i<maxSize;i++)
		elem[i] = tmp[i];
	maxSize *= 2;
	delete[] tmp;
}

template <class T>
class linkStack:public stack<T> {
private:
	struct node {
		T data;
		node *next;
		node(const T &x, node *N = NULL) {
			data = x; next = N;
		}
		node():next(NULL) { }
		~node() {}
	};
	node *elem;
public:
	linkStack() { elem = NULL; }
	~linkStack() {
		node *tmp;
		while (elem != NULL) {
			tmp = elem;
			elem = elem -> next;
			delete tmp;
		}
	}
	bool isEmpty() const { return elem == NULL; }
	void push(const T &x) { node *tmp = new node(x, elem); elem = tmp; }
	T pop() {
		node *tmp = elem;
		T x = tmp->data;
		elem = elem->next;
		delete tmp;
		return x;
	}
	T top() const { return elem->data; }
};


char w[1000][10], buff[10];
int n;
int okay;
linkStack<int> st;

void init() {
	ifstream cin("parser.in");
	n = 0;
	while (cin>>buff) {
		++n;
		strcpy(w[n], buff);
	}
	cin.close();
}

void work() {
	okay = 1;
	for (int i=1;i<=n;i++) {
		if (strcmp(w[i], "if") == 0) {
			if (i == n || (i < n && strcmp(w[i+1], "then") != 0)) {
				okay = 0;
				return;
			}
			st.push(1);
			i ++;
		} else
		if (strcmp(w[i], "then") == 0) {
			okay = 0;
			return;
		} else
		if (strcmp(w[i], "else") == 0) {
			if (st.isEmpty() || (!st.isEmpty() && st.top() != 1)) {
				okay = 0;
				return;
			}
			st.pop();
		} else
		if (strcmp(w[i], "begin") == 0) {
			st.push(2);
		} else
		if (strcmp(w[i], "end") == 0) {
			int found = 0;
			while (!found && !st.isEmpty()) {
				if (st.top() == 1) st.pop(); else found = 1;
			}
			if (!found) {
				okay = 0;
				return;
			}
			st.pop();
		}
	}
	while (!st.isEmpty()) {
		if (st.top() == 2)
			okay = 0;
		st.pop();
	}
}

void print() {
	ofstream cout("parser.out");
	if (okay) cout<<"Match"<<endl; else cout<<"Error"<<endl;
	cout.close();
}

int main() {
	init();
	work();
	print();
	return 0;
}