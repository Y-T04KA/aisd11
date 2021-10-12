#include <iostream>

using namespace std;

#define MAX 1000

class Stack {//stack via array
    int top;
public:
    int a[MAX]; //max size of stack
    Stack() { top = -1; }
    bool push(int x);//add to stack
    int pop();//get from stack
    int peek();//show top of stack
    bool isEmpty();
    char Top();
};

bool Stack::push(int x) {
    if (top >= (MAX - 1)) {
        cout << "Stack overflow";
        return false;
    }
    else {
        a[++top] = x;
        return true;
    }
}

int Stack::pop(){
    if (top < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        int x = a[top--];
        return x;
    }
}

int Stack::peek() {
    if (top < 0) {
        cout << "stack is empty";
        return 0;
    }
    else {
        int x = a[top];
        return x;
    }
}

bool Stack::isEmpty() {
    return (top < 0);
}
///////////
class Dyn {
private:
    int* pa; // points to the array
    int length; 
    int nextIndex; 
public:
    Dyn(); 
    ~Dyn(); 
    int& operator[](int index); 
    void add(int val); 
    int size(); 
};
Dyn::Dyn() {
    pa = new int[3];
    for (int i = 0; i < 3; i++)
        pa[i] = 0;
    length = 3;
    nextIndex = 0;
}
Dyn::~Dyn() {
    delete[] pa;
}
int& Dyn::operator[](int index) {
    int* pnewa; 
    if (index >= length) { 
        pnewa = new int[index + 5]; 
        for (int i = 0; i < nextIndex; i++) 
            pnewa[i] = pa[i];
        for (int j = nextIndex; j < index + 5; j++) 
            pnewa[j] = 0;
        length = index + 5; 
        delete[] pa; 
        pa = pnewa; 
    }
    if (index > nextIndex) 
        nextIndex = index + 1;
    return *(pa + index); 
}
void Dyn::add(int val) {
    int* pnewa;
    if (nextIndex == length) {
        length = length + 5;
        pnewa = new int[length];
        for (int i = 0; i < nextIndex; i++)
            pnewa[i] = pa[i];
        for (int j = nextIndex; j < length; j++)
            pnewa[j] = 0;
        delete[] pa;
        pa = pnewa;
    }
    pa[nextIndex++] = val;
}
int Dyn::size() {
    return length;
}
////////////////
template <typename T>
class List {
public:
    List(); //list init
    ~List(); //destruct list
    void add_head(T data);//add head elem
    void del_head();//delete head
    void add_last(T data);//add elem to the end of the list
    void del_last();//same but delete
    void add_node(int index, T data);//add elem between head and end
    void del_node(int index);
    void clear(); //to clear list
    int GetCount() { return Count; };//to get lenght of the list
    T& operator[](const int index); //overloaded operator
private:
    template<typename T>
    class Node { //declare element of the list
    public:
        Node* nextnode;
        T data;

        Node(T data = T(), Node* nextnode = nullptr) {
            this->data = data;
            this->nextnode = nextnode;
        }
    };
    int Count;
    Node<T>* head;
};

template<typename T>
List<T>::List() {
    Count = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::del_head() {
    Node<T>* temp = head;
    head = head->nextnode;
    delete temp;
    Count--;
}

template<typename T>
void List<T>::add_last(T data) {
    if (head == nullptr) {
        head = new Node<T>(data);
    }
    else {
        Node<T>* current = this->head;
        while (current->nextnode != nullptr) {
            current = current->nextnode;
        }
        current->nextnode = new Node<T>(data);
    }
    Count++;
}

template<typename T>
void List<T>::clear() {
    while (Count) {
        del_head();
    }
}

template<typename T>
T& List<T>::operator[](const int index) {
    int c = 0; 
    Node<T>* current = this->head;
    while (current != nullptr) {
        if (c == index) {
            return current->data; 
        }
        current = current->nextnode;
        c++;
    }
}

template<typename T>
void List<T>::add_head(T data) {
    head = new Node<T>(data, head);
    Count++;
}

template<typename T>
void List<T>::add_node(int index, T data) {
    if (index == 0) {
        add_head(data);
    }
    else {
        Node<T>* previous = this->head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->nextnode;
        }
        Node<T>* newNode = new Node<T>(data, previous->nextnode);
        previous->nextnode = newNode;
        Count++;
    }
}

template<typename T>
void List<T>::del_node(int index) {
    if (index == 0) {
        del_head();
    }
    else {
        Node<T>* previous = this->head;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->nextnode;
        }
        Node<T>* deleting = previous->nextnode;
        previous->nextnode = deleting->nextnode;
        delete deleting;
        Count--;
    }
}

template<typename T>
void List<T>::del_last() {
    del_node(Count - 1);
}

int prec(char c) {
    if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

int main() {
    int selector(5);
    List<char> lst;
    class Stack s;
    Dyn d;
    while (selector != 0) {
        cout << "\n1 to fill the list, 2 to show the list, 3 to convert, 4 to add node, 5 to delete node, 6 to array, 0 to exit\n";
        cin >> selector;
        switch (selector) {
        case 1: {
            char token;
            cout << "What the first element will be?\nenter e to end\n";
            cin >> token;
            lst.add_head(token);
            while (token != 'e') {
                //cout << "enter next elem, enter e to end\n";
                cin >> token;
                if (token == 'e') { break; }
                else {
                    lst.add_last(token);
                };
            }break; }
        case 2: {
            cout << "Nodes: " << lst.GetCount() << endl;
            for (int i = 0; i < lst.GetCount(); i++)
            {
                cout << lst[i] << " ";
            }
            cout << endl;
            break; }
        case 3: {
            char result;
            for (int i = 0; i < lst.GetCount(); i++) {
                char c = lst[i];
                if (c >= '0' && c <= '9') cout << c << ' ';
                else if (c == '(') s.push('(');
                else if (c == ')') {
                    while (s.peek() != '(') {
                        result = s.peek();
                        cout << result << ' ';
                        s.pop();
                    }
                    s.pop();
                }
                else {
                    while (!s.isEmpty() && prec(lst[i]) <= prec(s.peek())) {
                        result = s.peek();
                        cout << result << ' ';
                        s.pop();
                    }
                    s.push(c);
                }
            }
            while (!s.isEmpty()) {
                result = s.peek();
                cout << result << ' ';
                s.pop();
            }
            break; }
        case 4: { //add node
            int pos(-1);
            char temp;
            while (pos == -1) {
                cout << "enter number of the node and symbol\n";
                cin >> pos >> temp;
                if (pos > lst.GetCount() + 1) {
                    cout << "too big number, try again\n";
                    pos = -1;
                }
            }
            lst.add_node(pos, temp);
            break; }
        case 5: { //delete node
            int pos(-1);
            while (pos == -1) {
                cout << "number of the node you want to delete - ";
                cin >> pos;
                if (pos > lst.GetCount()) {
                    cout << "too big number, try again\n";
                    pos = -1;
                }
            }
            lst.del_node(pos);
            break; }
        case 6: {
            int token(0);
            cout << "enter next elem, enter -1 to end\n";
            while (token != -1) {
                cin >> token;
                if (token == -1) { break; }
                else {
                    d.add(token);
                };
            }
                for (int i = 0; i < d.size(); i++) 
                    cout << d[i] << endl;
                break;
            }
        }

        }
        return 0;
    }
