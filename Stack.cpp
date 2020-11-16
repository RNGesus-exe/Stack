#include<iostream>

template <class T>
class Stack {
	class Node {
	public:
		T data;
		Node* next;
	}*head;

public:

	Stack():head(nullptr) {}
	Stack(T data) {
		this->push(data);
	}
	void push(T data) {
		if (head) {
			Node* temp = new Node;
			if (temp) {
				temp->data = data;
				temp->next = head;
				head = temp;
				temp = nullptr;
			}
			else {
				std::cerr << "The Stack is Full!!!\n";
			}
		}
		else {
			this->head = new Node;
			this->head->data = data;
			this->head->next = nullptr;
		}
	}
	T pop() {
		T holder = NULL;
		if (head) {
			holder = this->head->data;
			Node* temp = this->head;
			this->head = this->head->next;
			delete temp;
			temp = nullptr;
		}
		return holder;
	}
	T peekAtTop() const {
		if (head) {
			return this->head->data;
		}
		return NULL;
	}
	void display() const {
		Node* temp = this->head;
		while (temp) {
			std::cout << temp->data;
			temp = temp->next;
		}
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	Node& getHead() {
		return this->head;
	}

	bool checkBraces(std::string equation) {
		Stack<char> braces;

		for (int i = 0; i < equation.length(); i++) {
			if (equation[i] == '(' || equation[i] == '{' || equation[i] == '[') {
				braces.push(equation[i]);
			}
			else if (equation[i] == ')' || equation[i] == '}' || equation[i] == ']') 
			{
				if ((equation[i] == ')' && braces.peekAtTop() == '(') || (equation[i] == '}'
					&& braces.peekAtTop() == '{') || (equation[i] == ']' && braces.peekAtTop() == '[')) {
					braces.pop();
				}
				else {
					return false;
				}
			}
		}
		return braces.isEmpty();
	}

	~Stack() {
		while (this->head) {
			this->pop();
		}
	}
};

int main() {

	Stack<int> stk;
	std::string str = "[{({[]})}];-;[{({[]})}]";
	std::cout << stk.checkBraces(str) << std::endl;

	return EXIT_SUCCESS;
}