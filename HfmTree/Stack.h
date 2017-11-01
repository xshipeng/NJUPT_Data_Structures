using namespace std;
template <class T>
class SeqStack
{
public:
	SeqStack(int mSize);
	~SeqStack() { delete[]s; }
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == maxTop; }
	bool Top(T &x) const;
	bool Push(T x);
	bool Pop();
	void Clear() { top = -1; }
	void Output(string& a);								//从底部开始读
private:
	int top;                                      //栈顶指针
	int maxTop;                                   //最大栈顶指针
	T *s;
};
template <class T>
SeqStack<T>::SeqStack(int mSize)
{
	maxTop = mSize - 1;
	s = new T[mSize];
	top = -1;
}
template <class T>
bool SeqStack<T>::Top(T &x) const
{
	if (IsEmpty()) {
		cout << "Empty" << endl; return false;
	}
	x = s[top]; return true;
}
template <class T>
bool SeqStack<T>::Push(T x)
{
	if (IsFull()) {                                    //溢出处理
		cout << "Overflow" << endl; return false;
	}
	s[++top] = x; return true;
}
template <class T>
bool SeqStack<T>::Pop()
{
	if (IsEmpty()) {                                  //空栈处理
		cout << "Underflow" << endl;   return false;
	}
	top--; return true;
}
template <class T>
void SeqStack<T>::Output(string &a)
{
	for (int i = 0; i <= top; i++)
	{
		std::stringstream ss;
		std::string str;
		ss << s[i];
		ss >> str;
		a.append(str);
	}
}