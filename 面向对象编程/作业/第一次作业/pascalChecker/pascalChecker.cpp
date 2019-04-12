//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <cstdlib>
//
//using namespace std;
//
//template <class T, int SZ = 16>
//class Cstack {
//	public:
//	    Cstack();
//	    ~Cstack();
//		bool isEmpty()  {  return (m_top==m_bottom? true:false);}
//		void push(T ele);
//		bool pop(T& ele);
//		void print();
//    private:
//        T* data;
//        int m_top, m_bottom, m_nSize;
//};
//
//template <class T, int SZ>      //构造函数
//Cstack<T,SZ>::Cstack()
//{
//    data = new T[SZ];
//    m_nSize = SZ;
//    m_bottom = m_top - 1;
//
//    cout << "m_bottom: " << m_bottom << endl;
//    cout << "m_top:    " << m_top << endl;
//}
//
//template <class T, int SZ>      //析构函数
//Cstack<T,SZ>::~Cstack()
//{
//    delete []data;
//}
//
//template <class T, int SZ>      //display
//void Cstack<T,SZ>::print()
//{
//    for(int i; i< m_top; ++i)
//        cout << data[i] << '\t';
//    cout << endl;
//}
//
//template <class T, int SZ>      //.push 进栈
//void Cstack<T,SZ>::push(T ele)
//{
//    if (m_top < m_nSize)
//        data[++m_top] = ele;
//}
//
//template <class T, int SZ>      //.pop  出栈
//bool Cstack<T,SZ>::pop(T& ele)
//{
//    if (!isEmpty())
//    {
//        ele = data[m_top--];
//        return true;
//    }else
//        return false;
//}
//
//template <class T, int SZ>      //.top  取顶栈
//<T,SZ> Cstack<T,SZ>::top(T ele)
//{
//    return data[m_top];
//}
//
//
//
//
//
//
//
//class CChecker{
//    public:
//        void init();       //初始化，读入pascal文件
//        void check();
//        void result()；
//    private:
//        bool m_matching;          //符号匹配的标志位
//        int m_n;                  //文本长度
//        char w[10000][100];       //存文本的长字符数组
//        char buff[100];           //存文本单个字符
//        Cstack<int, 8> st;
//
//};
//
//void CChecker::init()
//{
//    //读入pascal文件
//
////    string fileName = "";
////    cin >> fileName;                   //获取文件名
////	  ifstream fin(fileName.c_str());    //打开文件
//
//    //ifstream fin("hashCracker.pas");   //测试文件1
//    ifstream fin("parser.in");           //测试文件2
//    if (fin.fail())
//    {
//        cout<<"Open the file error."<<endl;
//        exit(0);
//    }
//    m_n = 0;
//    while (fin>>buff)
//    {
//        ++m_n;
//        strcpy(w[m_n], buff);
//        //cout << w[n] << endl;
//        cout << buff << endl;
//    }
//    cout << "file has been read in." << endl;
//    fin.close();
//}
//
///**
//idx
//1       if
//2       begin
//*/
//void CChecker::check()
//{
//    m_matching = 1;
//	int else_flag = 0;
//	for (int i=1;i<=m_n;i++)
//    {
//		if (strcmp(w[i], "if") == 0)
//		{
//            cout << "if find +1" <<endl;
//			st.push(1);
//			else_flag = 1;
//		}
//        else if (strcmp(w[i], "then") == 0)
//        {
//            cout << "then find +1" <<endl;
//			if (st.isEmpty() || (!st.isEmpty() && st.top() != 1))
//			{
//				m_matching = 0;
//				return;
//			}
//			st.pop();
//		}
//		else if (strcmp(w[i], "else") == 0)
//        {
//            cout << "else find +1" <<endl;
//            if (else_flag == 0)
//            {
//                m_matching = 0;
//                return;
//            }
//            else
//            {
//                else_flag = 0;
//            }
//		}
//		else if (strcmp(w[i], "begin") == 0)
//        {
//            cout << "begin find +1" <<endl;
//			st.push(2);
//		}
//		else if ((strcmp(w[i], "end") == 0) || (strcmp(w[i], "end.") == 0) || (strcmp(w[i], "end;") == 0))
//        {
//            cout << "end find +1" <<endl;
//			int found = 0;
//			while (!found && !st.isEmpty())
//			{
//				if (st.top() == 1) st.pop(); else found = 1;
//			}
//			if (!found)
//			{
//				m_matching = 0;
//				return;
//			}
//			st.pop();
//		}
//	}
//	while (!st.isEmpty())
//    {
//		if (st.top() == 2)
//			m_matching = 0;
//		st.pop();
//	}
//}
//
//
//void CChecker::result()
//{
//    if (m_matching == 1)  {  cout << "Match" << endl;}
//    else  {  cout << "Error" << endl;}
//}
//
//int main()
//{
//    CChecker che1;
//
//    che1.init();
//    che1.check();
//    che1.result();
//
//    return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////#include <iostream>
////#include <fstream>
////#include <string>
////#include <string.h>
////#include <unistd.h>
////#include <cstdlib>
////using namespace std;
////
////char w[10000][100], buff[100];
////int n;
////
////bool matching;
////
////void init()     //初始化，读入pascal文件
////{
////    //读入pascal文件
////
//////    string fileName = "";
//////    cin >> fileName;                   //获取文件名
//////	  ifstream fin(fileName.c_str());    //打开文件
////
////    //ifstream fin("hashCracker.pas");  //测试文件1
////    ifstream fin("parser.in");          //测试文件2
////
////	if (fin.fail())
////    {
////        cout<<"Open the file error."<<endl;
////        exit(0);
////    }
////
////	n = 0;
////	while (fin>>buff)
////    {
////		++n;
////		strcpy(w[n], buff);
////		//cout << w[n] << endl;
////	    //cout << buff << endl;
////	}
////	cout << "file has been read in." << endl;
////	fin.close();
////}
////
////void print()    //用于检测代码的print函数
////{
////    int i = 0;
////    for (i = 0; i < n; i++)
////    {
////        cout << w[i] << endl;
////        if ((strcmp(w[i], "end;") == 0) || (strcmp(w[i], "end") == 0))
////        {
////            cout << "find end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
////        }
////    }
////}
////
////void check()
////{
////    matching = 1;
////
////
////}
////
////void result()
////{
////    if (matching == 1)
////    {
////        cout << "Match" << endl;
////    }
////    else
////    {
////        cout << "Error" << endl;
////    }
////}
////
////int main()
////{
////    init();      //初始化，读入pascal文件
////    //print();   //用于检测代码的print函数
////    check();
////    result();
////    return 0;
////}
////
//
//////

//template <class T>
//class stack {
//	public:
//		virtual bool isEmpty() const = 0;
//		virtual void push(const T &x) = 0;
//		virtual T pop()=0;
//		virtual T top() const = 0;
//		virtual ~stack() { }
//};
////
////template <class T>
////class seqStack:public stack<T> {
////private:
////	T *elem;
////	int top_p;
////	int maxSize;
////
////	void doubleSpace();
////
////public:
////	seqStack(int initSize = 10) {
////		elem = new T[initSize];
////		maxSize = initSize; top_p = -1;
////	}
////
////	~seqStack() { delete[] elem; }
////
////	bool isEmpty() const { return top_p = -1; }
////
////	void push(const T &x) {
////		if (top_p == maxSize - 1) doubleSpace();
////		elem[++top_p] = x;
////	}
////	T pop() { return elem[top_p--]; }
////	T top() const { return elem[top_p]; }
////};
////
////
////template <class T>
////void seqStack<T>::doubleSpace() {
////	T *tmp = elem;
////	elem = new T[2 * maxSize];
////
////	for (int i=0;i<maxSize;i++)
////		elem[i] = tmp[i];
////	maxSize *= 2;
////	delete[] tmp;
////}
//
//template <class T>
//class linkStack:public stack<T> {
//private:
//	struct node {
//		T data;
//		node *next;
//		node(const T &x, node *N = NULL) {
//			data = x; next = N;
//		}
//		node():next(NULL) { }
//		~node() {}
//	};
//	node *elem;
//public:
//	linkStack() { elem = NULL; }
//	~linkStack() {
//		node *tmp;
//		while (elem != NULL) {
//			tmp = elem;
//			elem = elem -> next;
//			delete tmp;
//		}
//	}
//	bool isEmpty() const { return elem == NULL; }
//	void push(const T &x) { node *tmp = new node(x, elem); elem = tmp; }
//	T pop() {
//		node *tmp = elem;
//		T x = tmp->data;
//		elem = elem->next;
//		delete tmp;
//		return x;
//	}
//	T top() const { return elem->data; }
//};

