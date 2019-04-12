#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>

#define IF    1          //此处宏定义check函数中if begin的索引
#define BEGIN 2

using namespace std;

/**
    定义链栈类
*/
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
	node *elem;                        //私有成员
public:
	linkStack() { elem = NULL; }       //构造函数
	~linkStack() {                     //析构函数
		node *tmp;
		while (elem != NULL) {
			tmp = elem;
			elem = elem -> next;
			delete tmp;
		}
	}
	bool isEmpty() const { return elem == NULL; }                           //Empty
	void push(const T &x) { node *tmp = new node(x, elem); elem = tmp; }    //进栈
	T pop() {                                                               //出栈
		node *tmp = elem;
		T x = tmp->data;
		elem = elem->next;
		delete tmp;
		return x;
	}
	T top() const { return elem->data; }                                    //取栈顶
};

/**
    定义CChecker类
*/
class CChecker{
    public:
        void init();           //初始化函数用于读取文件
        void check();          //检查函数
        void result();         //输出结果

    private:
        char w[10000][100], buff[100];   //字符串数组用于存文件字符
        int m_n;                         //文件字符数量
        int m_matching;                  //检查匹配标志位
        linkStack<int> st;               //链栈用于检查是否匹配
};

void CChecker::init() {                  //读入pascal文件
//    string fileName = "";
//    cin >> fileName;                   //获取文件名
//	  ifstream fin(fileName.c_str());    //打开文件

    //ifstream fin("hashCracker.pas");   //测试文件1
    //ifstream fin("parser.in");         //测试文件2
    ifstream fin("test1.in");            //测试文件3
    if (fin.fail()) {
        cout<<"Open the file error."<<endl;
        exit(0);
    }
    m_n = 0;
    while (fin>>buff) {
        ++m_n;
        strcpy(w[m_n], buff);
        //cout << w[n] << endl;         //输出获取的字符串
        //cout << buff << endl;
    }
    cout << "file has been read in." << endl;
    fin.close();
}

/**
idx
1       if
2       begin
*/
void CChecker::check()
{
    m_matching = 1;
	int else_flag = 0;
	for (int i=1;i<=m_n;i++)
    {
		if (strcmp(w[i], "if") == 0) {                 //如果为if，进栈，else_flag置1
            cout << "if find +1" <<endl;
			st.push(IF);
			else_flag = 1;
		}
        else if (strcmp(w[i], "then") == 0) {          //如果为then，检查栈顶是否有if
            cout << "then find +1" <<endl;
			if (st.isEmpty() || (!st.isEmpty() && st.top() != IF))
			{
				m_matching = 0;
				return;
			}
			st.pop();                                  //IF出栈
		}
		else if (strcmp(w[i], "else") == 0) {          //如果为else，检查else_flag标志位
            cout << "else find +1" <<endl;
            if (else_flag == 0)
            {
                m_matching = 0;
                return;
            }
            else
            {
                else_flag = 0;                        //标志位清零
            }
		}
		else if (strcmp(w[i], "begin") == 0) {        //如果为begin，进栈
            cout << "begin find +1" <<endl;
			st.push(BEGIN);
		}
		else if ((strcmp(w[i], "end") == 0)          //如果为end，检查栈顶是否有begin
              || (strcmp(w[i], "end.") == 0)         //此处考虑到一些带标点的情况
              || (strcmp(w[i], "end;") == 0)) {      //不做end字符提取的原因是自定义的变量名中会有end
            cout << "end find +1" <<endl;
			int found = 0;
			while (!found && !st.isEmpty()){
				if (st.top() == IF) st.pop(); else found = 1;
			}
			if (!found)
			{
				m_matching = 0;
				return;
			}
			st.pop();                                //begin出栈
		}
	}
	while (!st.isEmpty())                            //判断是否还有剩余begin
    {
		if (st.top() == BEGIN)
			m_matching = 0;
		st.pop();
	}
}

void CChecker::result() {                            //输出结果
    cout << "the result is ";
    if (m_matching == 1) { cout << "Match" << endl; }
    else { cout << "Error" << endl; }
}

int main() {

    CChecker che1;

    che1.init();         //读取文件
    che1.check();        //检查
    che1.result();       //打印结果

	return 0;
}
