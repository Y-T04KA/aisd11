#include <iostream>

using namespace std;

template<class T>
class Stack {
private:
    T* m_array;
    int count;
    int maxsize;
    static const int resize = 2;
    static const int init_maxsize = 10;
public:
    Stack();
    inline Stack(const Stack<T>& rhs) { *this = rhs; }
    void operator=(const Stack<T>& rhs);
    Stack(int initial_max_size);
    ~Stack();
    void push(T data);
    void pop();
    void clear();
    void clearElem(int pos);
    void add(T data, int pos);
    char get(int pos);
    inline bool empty() { return count == 0; }
    inline T& top() { return m_array[count - 1]; }
    inline int size() { return count; }
private:
    void init();
    void increase_array_size();
};
template <class T>
Stack<T>::Stack() :count(0), maxsize(init_maxsize) {
    init();
}
template<class T>
Stack<T>::Stack(int initial_max_size) : count(0), maxsize(initial_max_size) {
    init();
}
template<class T>
Stack<T>::~Stack() {
    delete[] m_array;
}
template<class T>
void Stack<T>::init() {
    m_array = new T[maxsize];
    count = 0;
}
template<class T>
void Stack<T>::increase_array_size() {
    maxsize = resize * maxsize;
    T* tmp = new T[maxsize];
    for (int i = 0; i < count; i++) tmp[i] = m_array[i];
    delete[] m_array;
    m_array = tmp;
}
template<class T>
void Stack<T>::push(T data) {
    if (count == maxsize) increase_array_size();
    m_array[count++] = data;
}
template<class T>
void Stack<T>::pop() {
    if (count == 0) cout << "stack underflow\n";
    count--;
}
template<class T>
void Stack<T>::clear() {
    delete[] m_array;
    maxsize = init_maxsize;
    init();
}
template<class T>
void Stack<T>::clearElem(int pos) {
    if (pos >= maxsize) cout << "no such element\n";
    else m_array[pos] = 0;
}
template<class T>
void Stack<T>::add(T data, int pos) {
    while (count >= maxsize) increase_array_size();
    m_array[pos] = data;
}
template<class T>
char Stack<T>::get(int pos) {
    if (pos >= maxsize) cout << "no such element\n";
    else {
        char temp;
        temp = m_array[pos];
        return temp;
    }
}
template<class T>
void Stack<T>::operator=(const Stack<T>& rhs) {
    if (this != &rhs) {
        delete[] m_array;
        init();
        for (int i = 0; i < rhs.count; i++) {
            this->push(rhs.m_array[i]);
        }
    }
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

int priority(char c) {
    if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return -1;
}

int main() {
    int selector(5);
    List<char> lst;
    Stack<char> s;
    while (selector != 0) {
        cout << "\n1 to fill the list, 2 to show the list, 3 to SortStation, 4 to add node, 5 to delete node, 6 to del/add in array\n0 to exit\n";
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
                    while (s.top() != '(') {
                        result = s.top();
                        cout << result << ' ';
                        s.pop();
                    }
                    s.pop();
                }
                else {
                    while (!s.empty() && priority(lst[i]) <= priority(s.top())) {
                        result = s.top();
                        cout << result << ' ';
                        s.pop();
                    }
                    s.push(c);
                }
            }
            while (!s.empty()) {
                result = s.top();
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
            int sel(0), number;
            char sym;
            cout << "1 to add, 2 to delete, 3 to show\nnot recomended in one run with SortStation\n";
            cin >> sel;

            if (sel == 1) {
                cout << "enter position you want to add: ";
                cin >> number;
                cout << "enter element you want to add: ";
                cin >> sym;
                for (int i = 0; i < number + 10; ++i) {//fill array with space symbols
                    s.add(' ', i);
                }
                s.add(sym, number);
            }
            else if (sel == 2) {
                cout << "enter position you want to delete: ";
                cin >> number;
                s.clearElem(number);
            }
            else {
                cout << "how many elems you want to see: ";
                cin >> number;
                for (int i = 0; i < number; ++i) cout << s.get(i) << endl;
            }
            break;
        }
        }

    }
    return 0;
}
