#include <iostream>
#include <initializer_list>
using namespace std;
template<typename T>
class List
{
private:
	class Node
	{
	private:

	public:
		Node* next;
		T value;
		Node(T v)
		{
			this->value = v;
			this->next = nullptr;
		}
	};
	int size = 0;
	Node* head = nullptr;;


public:
	class Iterator
	{
	private:
		
	public:
		Node* ptr;
		Iterator(Node* node)
		{
			this->ptr = node;
		}
		T& operator*()
		{
			return ptr->value;
		}
		T* operator->()
		{
			return &ptr->value;
		}
		Iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		bool operator !=(const Iterator& other)
		{
			return ptr != other.ptr;
		}
		bool operator ==(const Iterator& other)
		{
			return ptr == other.ptr;
		}
		friend class List;
	};
	class ConstIterator
	{

	public:
		Node* ptr;
		ConstIterator(Node* node)
		{
			this->ptr = node;
		}
		const T& operator*() const
		{
			return ptr->value;
		}
		const T* operator->() const
		{
			return &ptr->value;
		}
		ConstIterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		bool operator!=(const ConstIterator& other) const
		{
			return ptr != other.ptr;
		}
	
		friend class List;

	};
	Iterator begin()
	{
		return Iterator(head);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
	ConstIterator begin() const
	{
		return ConstIterator(head);
	}
	ConstIterator end() const
	{
		return ConstIterator(nullptr);
	}
	List()
	{
		this->head = nullptr;
	}
	void push_back(T value)
	{
		Node* current = new Node(value);
		if (head == nullptr)
		{
			head = current;
			size++;
		}

		else
		{
			Node* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = current;
			size++;
		}
	}
	List(std::initializer_list<T> other)
	{
		head = nullptr;
		for (auto& x : other)
		{
			push_back(x);
		}
	}
	List& operator=(std::initializer_list<T> other)
	{

		clear();

		for (auto& value : other)
		{
			push_back(value);
		}
		return *this;

	}


	Iterator erase_by_index(Iterator it)
	{
		if (it.ptr == head)
		{
			Node* current = head;
			head = head->next;
			delete current;

			return Iterator(head);
		}
		Node* cur = head;
		while (cur->next != it.ptr)
		{
			cur = cur->next;
		}
		Node* toDelete = it.ptr;
		cur->next = toDelete->next;
		delete toDelete;
		size--;

		return Iterator(cur->next);
	}
	Iterator push_by_index(Iterator it, T value)
	{
		Node* newNode = new Node(value);
		if (it.ptr == head)
		{
			newNode->next = head;
			head = newNode;
			size++;
			return Iterator(head);
		}
		Node* cur = head;
		while (cur->next != it.ptr)
		{
			cur = cur->next;
		}
		newNode->next = it.ptr;
		cur->next = newNode;;

		size++;
		return Iterator(newNode);
	}

	List(const List& other)
	{
		head = nullptr;
		size = 0;
		Node* current = other.head;
		while (current)
		{
			push_back(current->value);
			current = current->next;
		}
	}
	List(List&& other)
	{
		head = other.head;
		size = other.size;

		other.head = nullptr;
		other.size = 0;
	}
	List& operator=(const List& other)
	{
		if (this == &other)
			return *this;

		clear();

		Node* current = other.head;
		while (current)
		{
			push_back(current->value);
			current = current->next;
		}

		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)
			return *this;

		clear();

		head = other.head;
		size = other.size;

		other.head = nullptr;
		other.size = 0;

		return *this;
	}

	int get_size()
	{
		return size;
	}
	bool empty()
	{
		return head == nullptr;
	}
	T& front()
	{
		return  head->value;
	}
	T& back()
	{
		Node* current = head;
		while (current->next)
		{
			current = current->next;

		}
		return current->value;
	}
	int find_index(T value)
	{
		Node* current = head;
		int index = 0;
		while (current)
		{

			if (current->value == value)
			{
				return index;
			}
			current = current->next;
			index++;
		}
		return -1;
	}
	T& operator[](int index)
	{
		Node* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->value;
	}
	Node* find(T value)
	{
		Node* current = head;
		while (current)
		{
			if (current->value == value)
			{
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}
	void insert_answer(Node* node, T value)
	{
		Node* newNode = new Node(value);
		newNode->next = node->next;
		node->next = newNode;
		size++;
	}
	bool contains(T value)
	{
		return find(value) != nullptr;
	}
	void push_front(T value)
	{
		Node* current = new Node(value);
		current->next = head;
		head = current;
		size++;
	}
	void pop_front()
	{
		Node* current = head;
		head = head->next;
		size--;
		delete current;
	}
	void pop_back()
	{
		if (head == nullptr)
			return;

		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			return;
		}
		Node* current = head;
		while (current->next->next)
		{
			current = current->next;
		}
		Node* toDelete = current->next;
		current->next = nullptr;
		size--;
		delete toDelete;
	}
	void  push_by_index(T value, int index)
	{
		Node* current = new Node(value);
		Node* t = head;
		for (int i = 0; i < index - 1; i++)
		{
			t = t->next;
		}
		current->next = t->next;
		t->next = current;
		size++;
	}
	void print1()
	{
		for (auto it = begin(); it != end(); ++it)
		{
			std::cout << *it << std::endl;
		}
		std::cout << std::endl;

	}
	/*Iterator find(T value)
	{
		for (auto it = begin(); it != end(); ++i)
		{
			if (*it == value)
			{
				return it;
			}
		}
		return end();
	}*/
	void swap(int index, int twoindex)
	{
		
		Node* n1 = head;
		Node* n2 = head;

		for (int i = 0; i < index; i++)
		{
			n1 = n1->next;
		}
		for (int i = 0; i < twoindex; i++)
		{
			n2 = n2->next;
		}

		T time = n1->value;
		n1->value = n2->value;
		n2->value = time;


	}
	void erase_by_index(int index)
	{
		if (index == 0)
		{
			Node* cur = head;
			head = head->next;
			delete cur;
			size--;
			return;
		}
		Node* h = head;
		for (int i = 0; i < index - 1; i++)
		{
			h = h->next;
		}
		Node* toDelete = h->next;
		h->next = toDelete->next;
		size--;
		delete toDelete;
	}
	void clear()
	{
		Node* h = head;
		while (h)
		{
			Node* next = h->next;
			delete h;
			h = next;
		}
		head = nullptr;
		size = 0;
	}
	void print()
	{
		Node* h = head;
		while (h)
		{
			std::cout << h->value << " ";
			h = h->next;
		}
		std::cout << std::endl;
	}
	void reverse()
	{
		Node* prev = nullptr;
		Node* h = head;
		Node* next = nullptr;
		while (h)
		{
			next = h->next;
			h->next = prev;
			prev = h;
			h = next;
		}
		head = prev;
	}
	int  count_elements(T value)
	{
		int count = 0;
		Node* h = head;
		while (h)
		{
			if (h->value == value)
			{
				count++;
			}
			h = h->next;
		}
		return count;
	}
	void destroy_all_element(T value)
	{
		while (head && head->value == value)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
		Node* current = head;
		while (current->next)
		{
			if (current->next->value == value)
			{
				Node* toDelete = current->next;
				current->next = toDelete->next;
				delete toDelete;
				size--;
			}
			else
			{
				current = current->next; 
			}
		}
	}
	void SwapNodes(int index, int index2)
	{
		Node* n1 = head, * n2 = head;
		Node* p1 = nullptr, * p2 = nullptr;
		for (int i = 0; i < index; i++)
		{
			p1 = n1;
			n1 = n1->next;
		}
		for (int i = 0; i < index2; i++)
		{
			p2 = n2;
			n2 = n2->next;
		}
		if (p1)
		{
			p1->next = n2;
		}
		p2->next = n1;
		
		std::swap(n1->next, n2->next);
	}
	void DeletePeriod(int i, int j)
	{
		if (i > j) return;

		Node* prev = nullptr;
		Node* start = head;

		// найти начало диапазона
		for (int k = 0; k < i; k++)
		{
			if (!start) return;
			prev = start;
			start = start->next;
		}

		Node* end = start;

		// найти конец диапазона
		for (int k = i; k < j; k++)
		{
			if (!end) return;
			end = end->next;
		}

		if (!start || !end) return;

		Node* after = end->next;

		// удаляем диапазон
		Node* cur = start;
		while (cur != after)
		{
			Node* temp = cur;
			cur = cur->next;
			delete temp;
			size--;
		}
		if (prev)
		{
			prev->next = after;
		}
		else
		{
			head = after;
		}
			

	}
	template <typename Predicate>
	void remove_if(Predicate value)
	{
		while (head && value(head->value))
		{
			Node* cur = head;
			head = head->next;
			delete cur;
			size--;
		}

		Node* current = head;

		while (current && current->next)
		{
			if (value(current->next->value))
			{
				Node* toDelete = current->next;
				current->next = toDelete->next;
				delete toDelete;
				size--;
			}
			else
			{
				current = current->next;
			}
		}
	}

	~List()
	{
		clear();
	}
	Node* reverseRec(Node* node)
	{
		// 📌 БАЗА РЕКУРСИИ:
		// если список пуст или остался один элемент —
		// он уже "перевёрнут", возвращаем его как новую голову
		if (node == nullptr || node->next == nullptr)
			return node;

		// 📌 УХОД В РЕКУРСИЮ:
		// идём до конца списка (до последнего элемента)
		// на этом этапе ничего не переворачиваем
		Node* newHead = reverseRec(node->next);

		// 📌 КЛЮЧЕВОЙ МОМЕНТ (разворот связи):

		// node->next — это следующий элемент
		// node->next->next = node означает:
		// "следующий узел теперь указывает назад на текущий"

		node->next->next = node;

		// 📌 ЛОМАЕМ СТАРУЮ СВЯЗЬ:

		// иначе получится цикл (например 2 ↔ 3 ↔ 2 ...)
		node->next = nullptr;

		// 📌 ВОЗВРАЩАЕМ НОВУЮ ГОЛОВУ:

		// newHead — это последний элемент исходного списка
		// он становится первым после разворота
		return newHead;
	}
	void splice(int index, List& other)
	{

		Node* current = head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		if (!other.head) return;
		Node* tail = other.head;
		while (tail->next)
		{
			tail = tail->next;
		}
		Node* nextPart = current->next;
		current->next = other.head;
		tail->next = nextPart;

		other.head = nullptr;
		other.size = 0;
	}
	Node* merge(Node* a, Node* b)
	{
		Node dummy(0);
		Node* tail = &dummy;

		while (a && b)
		{
			if (a->value < b->value)
			{
				tail->next = a;
				a = a->next;
			}
			else
			{
				tail->next = b;
				b = b->next;
			}
			tail = tail->next; // ❗ ВАЖНО
		}

		tail->next = (a ? a : b);

		return dummy.next;
	}
	void split(Node* head, Node*& left, Node*& right)
	{
		Node* first = head;
		Node* second = head->next;

		while (second && second->next)
		{
			first = first->next;
			second = second->next->next;
		}
		left = head;
		right = first->next;
		first->next = nullptr;
	}
	Node* mergeSort(Node* node)
	{
		if (!node || !node->next)
			return node;

		Node* left;
		Node* right;

		split(node, left, right);

		left = mergeSort(left);
		right = mergeSort(right);

		return merge(left, right);
	}
	void sort()
	{
		head = mergeSort(head);
	}

	

};

int main()
{
	List<int> a;

	cout << "Push back:\n";
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(2);
	a.push_back(5);
	a.print();

	cout << "\nPush front:\n";
	a.push_front(0);
	a.print();

	cout << "\nFront / Back:\n";
	cout << "front = " << a.front() << endl;
	cout << "back  = " << a.back() << endl;

	cout << "\nFind index of 2:\n";
	cout << a.find(2) << endl;

	cout << "\nCount elements (2):\n";
	cout << a.count_elements(2) << endl;

	cout << "\nInsert 99 at index 2:\n";
	a.push_by_index(99, 2);
	a.print();

	cout << "\nErase index 3:\n";
	a.erase_by_index(3);
	a.print();

	cout << "\nContains 5:\n";
	cout << (a.contains(5) ? "true" : "false") << endl;

	cout << "\nReverse:\n";
	a.reverse();
	a.print();

	cout << "\nRemove if (remove all 2):\n";
	a.remove_if([](int x) { return x == 2; });
	a.print();

	cout << "\nDeletePeriod (1, 2):\n";
	a.DeletePeriod(1, 2);
	a.print();

	cout << "\nSwap nodes (0, 2):\n";
	a.SwapNodes(0, 2);
	a.print();

	cout << "\nClear:\n";
	a.clear();
	a.print();

	cout << "\nCheck empty:\n";
	cout << (a.empty() ? "empty" : "not empty") << endl;

	// ===== MOVE TEST =====
	cout << "\nMove test:\n";

	List<int> b;
	b.push_back(10);
	b.push_back(20);

	cout << "b before move:\n";
	b.print();

	List<int> c = std::move(b);

	cout << "c after move:\n";
	c.print();

	cout << "b (should be empty):\n";
	b.print();

	return 0;
}
