template<class T>
class SeqQueue
{
public:
	SeqQueue(int mSize);
	~SeqQueue() { delete[] q; };
	bool IsEmpty() const { return front == rear; }
	bool IsFull() const { return (rear + 1) % maxSize == front; }
	bool Front(T& x) const;
	bool EnQueue(T x);
	bool DeQueue();
private:
	int front, rear;
	int maxSize;
	T *q;
};
template <class T>
SeqQueue<T>::SeqQueue(int mSize)
{
	maxSize = mSize;
	q = new T[maxSize];
	front = rear = 0;
}
template <class T>
bool SeqQueue<T>::Front(T& x) const
{
	if (IsEmpty()) {
		cout << "empty" << endl; return false;
	}
	x = q[(front + 1) % maxSize];
	return true;
}
template <class T>
bool SeqQueue<T>::EnQueue(T x)
{
	if (IsFull()) {
		cout << "Full" << endl; return false;
	}
	q[(rear = (rear + 1) % maxSize)] = x;
	return true;
}
template <class T>
bool SeqQueue<T>::DeQueue()
{
	if (IsEmpty()) {
		cout << "Underflow" << endl; return false;
	}
	front = (front + 1) % maxSize;
	return true;
}