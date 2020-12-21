template <class T>
struct Node {
	T Data;
	Node* Previous;
	Node* Next;
	Node(T Data, Node* Previous, Node* Next) {
		this->Data = Data;
		this->Previous = Previous;
		this->Next = Next;
	}
};

template <class T>
struct List {
private:
	Node<T>* begin;
	Node<T>* end;
	int Length;
public:
	List() { end = NULL; begin = NULL; Length = 0; }
	List(T Data) {
		begin = new Node<T>(Data, nullptr, nullptr);
		end = begin;
		Length = 1;
	}
	void PushBack(T Data) {
		if (end == NULL) {
			begin = new Node<T>(Data, nullptr, nullptr);
			end = begin;
		}
		else {
			Node<T>* recent = new Node<T>(Data, end, nullptr);
			end = recent;
			recent->Previous->Next = recent;
		}
		Length++;
	}
	void PushFront(T Data) {
		if (begin == NULL) {
			begin = new Node<T>(Data, nullptr, nullptr);
			end = begin;
		}
		else {
			Node<T>* recent = new Node<T>(Data, nullptr, begin);
			begin = recent;
			recent->Next->Previous = recent;
		}
		Length++;
	}
	void RemoveLast() {
		Node<T>* save = end->Previous;
		delete end;
		end = save;
		end->Next = nullptr;
		Length--;
	}
	void RemoveFirst() {
		Node<T>* save = begin->Next;
		delete begin;
		begin = save;
		begin->Previous = nullptr;
		Length--;
	}
	T& At(int item) {
		Node<T>* returned = begin;
		while (item--) returned = returned->Next;
		return returned->Data;
	}
	int getLength() { return Length; }

};