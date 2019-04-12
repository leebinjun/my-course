#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>

#define IF    1          //�˴��궨��check������if begin������
#define BEGIN 2

using namespace std;

/**
    ������ջ��
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
	node *elem;                        //˽�г�Ա
public:
	linkStack() { elem = NULL; }       //���캯��
	~linkStack() {                     //��������
		node *tmp;
		while (elem != NULL) {
			tmp = elem;
			elem = elem -> next;
			delete tmp;
		}
	}
	bool isEmpty() const { return elem == NULL; }                           //Empty
	void push(const T &x) { node *tmp = new node(x, elem); elem = tmp; }    //��ջ
	T pop() {                                                               //��ջ
		node *tmp = elem;
		T x = tmp->data;
		elem = elem->next;
		delete tmp;
		return x;
	}
	T top() const { return elem->data; }                                    //ȡջ��
};

/**
    ����CChecker��
*/
class CChecker{
    public:
        void init();           //��ʼ���������ڶ�ȡ�ļ�
        void check();          //��麯��
        void result();         //������

    private:
        char w[10000][100], buff[100];   //�ַ����������ڴ��ļ��ַ�
        int m_n;                         //�ļ��ַ�����
        int m_matching;                  //���ƥ���־λ
        linkStack<int> st;               //��ջ���ڼ���Ƿ�ƥ��
};

void CChecker::init() {                  //����pascal�ļ�
//    string fileName = "";
//    cin >> fileName;                   //��ȡ�ļ���
//	  ifstream fin(fileName.c_str());    //���ļ�

    //ifstream fin("hashCracker.pas");   //�����ļ�1
    //ifstream fin("parser.in");         //�����ļ�2
    ifstream fin("test1.in");            //�����ļ�3
    if (fin.fail()) {
        cout<<"Open the file error."<<endl;
        exit(0);
    }
    m_n = 0;
    while (fin>>buff) {
        ++m_n;
        strcpy(w[m_n], buff);
        //cout << w[n] << endl;         //�����ȡ���ַ���
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
		if (strcmp(w[i], "if") == 0) {                 //���Ϊif����ջ��else_flag��1
            cout << "if find +1" <<endl;
			st.push(IF);
			else_flag = 1;
		}
        else if (strcmp(w[i], "then") == 0) {          //���Ϊthen�����ջ���Ƿ���if
            cout << "then find +1" <<endl;
			if (st.isEmpty() || (!st.isEmpty() && st.top() != IF))
			{
				m_matching = 0;
				return;
			}
			st.pop();                                  //IF��ջ
		}
		else if (strcmp(w[i], "else") == 0) {          //���Ϊelse�����else_flag��־λ
            cout << "else find +1" <<endl;
            if (else_flag == 0)
            {
                m_matching = 0;
                return;
            }
            else
            {
                else_flag = 0;                        //��־λ����
            }
		}
		else if (strcmp(w[i], "begin") == 0) {        //���Ϊbegin����ջ
            cout << "begin find +1" <<endl;
			st.push(BEGIN);
		}
		else if ((strcmp(w[i], "end") == 0)          //���Ϊend�����ջ���Ƿ���begin
              || (strcmp(w[i], "end.") == 0)         //�˴����ǵ�һЩ���������
              || (strcmp(w[i], "end;") == 0)) {      //����end�ַ���ȡ��ԭ�����Զ���ı������л���end
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
			st.pop();                                //begin��ջ
		}
	}
	while (!st.isEmpty())                            //�ж��Ƿ���ʣ��begin
    {
		if (st.top() == BEGIN)
			m_matching = 0;
		st.pop();
	}
}

void CChecker::result() {                            //������
    cout << "the result is ";
    if (m_matching == 1) { cout << "Match" << endl; }
    else { cout << "Error" << endl; }
}

int main() {

    CChecker che1;

    che1.init();         //��ȡ�ļ�
    che1.check();        //���
    che1.result();       //��ӡ���

	return 0;
}
