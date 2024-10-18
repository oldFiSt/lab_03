#include <iostream>

template <typename T>
class DynamicArray {
private:
    T* data; //указатель на массив элементов типа Т
    size_t capacity;
    size_t length;
    
    //служит для увеличения размера массива, когда размер достигает capacity, он вызывается и увеличивает размер на 50%
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }


public:
    //Начальная вместимость равна 10. Это означает, что при создании контейнера выделяется память для хранения 10 элементов типа Т
    DynamicArray(size_t initial_capacity = 10) 
        : capacity(initial_capacity), length(0), data(new T[initial_capacity]) {}

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), length(other.length), data(new T[other.capacity]) {//копирует данные и выделяет память для нового массива
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray(DynamicArray&& other) noexcept //конструктор перемещения, который принимает r-value ссылку на другой объект noexcept - без исключений
        : capacity(other.capacity), length(other.length), data(other.data) {
        other.data = nullptr;//обновление ресурсов у перемещаемого объекта 
        other.length = 0;
        other.capacity = 0;
    }

    DynamicArray& operator=(const DynamicArray& other) {//оператор присваивания копирования 
        if (this == &other) return *this;//проверка для предотвращения ненужного выполнения кода
        delete[] data;
        capacity = other.capacity;
        length = other.length;
        data = new T[capacity];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        length = other.length;
        data = other.data;
        other.data = nullptr;
        other.length = 0;
        other.capacity = 0;
        return *this;
    }

    void push_back(const T& value) {
        if (length == capacity) {
            resize(capacity + capacity / 2);//чтобы увеличить размер массива
        }
        data[length++] = value;
    }

    void insert(size_t index, const T& value) {
        if (index > length) throw std::out_of_range("Index out of range");
        if (length == capacity) {
            resize(capacity + capacity / 2);
        }
        for (size_t i = length; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = value;
        ++length;
    }

    void erase(size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < length - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --length;
    }

    size_t size() const {
        return length;
    }

    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void print() const {
        for (size_t i = 0; i < length; ++i) {
            std::cout << data[i] << (i < length - 1 ? ", " : "");
        }
        std::cout << std::endl;
    }
};

template <typename T>
class DoublyNode {
public:
    T data;
    DoublyNode* next;
    DoublyNode* prev;

    DoublyNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedListIterator {
private:
    DoublyNode<T>* current;

public:
    DoublyLinkedListIterator(DoublyNode<T>* node) : current(node) {}

    T& operator*() {
        return current->data; // Разыменование для доступа к данным
    }

    DoublyLinkedListIterator& operator++() { // Префиксный инкремент
        if (current) current = current->next;
        return *this;
    }

    DoublyLinkedListIterator& operator--() { // Префиксный декремент
        if (current) current = current->prev;
        return *this;
    }

    bool operator!=(const DoublyLinkedListIterator& other) const {
        return current != other.current; // Сравнение итераторов
    }
};

template <typename T>
class DoublyLinkedList {
private:
    DoublyNode<T>* head; // Указатель на первый элемент
    DoublyNode<T>* tail; // Указатель на последний элемент
    size_t length; // Размер списка

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    ~DoublyLinkedList() {
        while (head) {
            DoublyNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

   void push_back(const T& value) { 
       DoublyNode<T>* newNode = new DoublyNode<T>(value); 
       if (!head) { 
           head = tail = newNode; 
       } else { 
           tail->next = newNode; 
           newNode->prev = tail;  
           tail = newNode; 
       } 
       ++length; 
   }

   void push_front(const T& value) { 
       DoublyNode<T>* newNode = new DoublyNode<T>(value); 
       if (!head) { 
           head = tail = newNode; 
       } else { 
           newNode->next = head; 
           head->prev = newNode;  
           head = newNode; 
       } 
       ++length; 
   }

   void insert(size_t index, const T& value) { 
       if (index > length) throw std::out_of_range("Index out of range"); 
       
       if (index == 0) { 
           push_front(value); 
           return; 
       } 
       
       if (index == length) { 
           push_back(value); 
           return; 
       } 

       DoublyNode<T>* newNode = new DoublyNode<T>(value); 
       DoublyNode<T>* current = head;

       for (size_t i = 0; i < index; ++i) { 
           current = current->next; 
       } 

       newNode->next = current;      // Устанавливаем указатель next у нового узла 
       newNode->prev = current->prev; // Устанавливаем указатель prev у нового узла 

       if (current->prev)
           current->prev->next = newNode;

       current->prev = newNode;

       if (index == 0)
           head = newNode;

       ++length; 
   }

   void erase(size_t index) { 
       if (index >= length) throw std::out_of_range("Index out of range"); 
       
       DoublyNode<T>* current = head;

       for (size_t i = 0; i < index; ++i)
           current = current->next;

       if (current->prev)
           current->prev->next = current->next;

       if (current->next)
           current->next->prev = current->prev;

       if (current == head)
           head = current->next;

       if (current == tail)
           tail = current->prev;

       delete current;

       --length; 
   }

   void print() const { 
      DoublyNode<T>* current= head; 
      while(current != nullptr){ 
          std::cout << current -> data << " "; 
          current=current -> next; 
      } 
      std::cout << std::endl; 
   } 

   size_t getSize() const { return length; } 

   DoublyLinkedListIterator<T> begin() { 
      return DoublyLinkedListIterator<T>(head); // Возвращаем итератор на голову 
   } 

   DoublyLinkedListIterator<T> end() { 
      return DoublyLinkedListIterator<T>(nullptr); // Возвращаем итератор на nullptr 
   } 

};

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class SinglyLinkedListIterator {
private:
    Node<T>* current;

public:
    SinglyLinkedListIterator(Node<T>* node) : current(node) {}

    T& operator*() {
        return current->data; // Разыменование для доступа к данным
    }

    SinglyLinkedListIterator& operator++() { // Префиксный инкремент
        if (current) current = current->next;
        return *this;
    }

    bool operator!=(const SinglyLinkedListIterator& other) const {
        return current != other.current; // Сравнение итераторов
    }
};

template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;
    size_t length;

public:
    SinglyLinkedList() : head(nullptr), length(0) {}

    ~SinglyLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        ++length;
    }

    void insert(size_t index, const T& value) {
        if (index > length) throw std::out_of_range("Index out of range");
        Node<T>* newNode = new Node<T>(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* temp = head;
            for (size_t i = 0; i < index - 1; ++i) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        ++length;
    }

    void erase(size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        Node<T>* temp = head;
        if (index == 0) {
            head = head->next;
            delete temp;
        } else {
            for (size_t i = 0; i < index - 1; ++i) {
                temp = temp->next;
            }
            Node<T>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
        }
        --length;
    }

    size_t size() const {
        return length;
    }

    SinglyLinkedListIterator<T> begin() {
        return SinglyLinkedListIterator<T>(head); // Возвращаем итератор на голову
    }

    SinglyLinkedListIterator<T> end() {
        return SinglyLinkedListIterator<T>(nullptr); // Возвращаем итератор на nullptr
    }

    void print() const {
        Node<T>* temp = head;
        while (temp) {
            std::cout << temp->data << (temp->next ? ", " : "");
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DynamicArray<int> arr;

    
    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }

    std:: cout << "Вывод ожидаемого контейнера: " << '\n';
    arr.print(); 

    // Вывод размера
    std::cout << "Size: " << arr.size() << std::endl; // Size: 10

    // Удаление элементов (удаляется на элемент меньше, т.к. нумеруются с нуля)
    arr.erase(2);  
    arr.erase(4);  
    arr.erase(5);  

    std::cout << "Вывод содержимого на экран " << '\n';
    arr.print();

    arr.insert(0, 10);
    std::cout << "Вывод содержимого с десяткой в начале " << '\n';
    arr.print();  

    arr.insert(4, 20);
    std::cout << "Вывод содержимого с 20 в середине " << '\n';
    arr.print();  

    arr.push_back(30);

    std::cout << "Вывод содержимого с 30 в конце " << '\n';
    arr.print();  
    
    SinglyLinkedList<int> list;

    // Добавление 10 элементов
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    std:: cout << "Вывод однонаправленного списка: " << '\n';
    
    list.print();

    list.erase(2);
    list.erase(4);
    list.erase(5);
    
    list.print();

    list.insert(0, 10);
    list.print(); 

    list.insert(4, 20);
    list.print(); 

    list.push_back(30);
    list.print();
    
    DoublyLinkedList<int> doubleList;

    for (int i=0; i<10; ++i){
        doubleList.push_back(i);
    }

    std::cout << "Двунаправленный список:\n";
    doubleList.print();

    doubleList.erase(2); 
    doubleList.insert(4, 20);

    std::cout << "После изменений:\n";
    doubleList.print();

    SinglyLinkedList<int> sing_list_1;
    
    for (int i = 0; i < 10; i++)
    {
     sing_list_1.push_back(i);
    }

    std::cout << "Однонаправленный список:\n";

    for (auto it = sing_list_1.begin(); it != sing_list_1.end(); ++it) {
        std::cout << *it << " "; 
    }

    std::cout << std::endl;

    DoublyLinkedList<int> double_list_1;
    for (int i = 0; i < 10; ++i) {
        double_list_1.push_back(i);
    }

    std::cout << "Двунаправленный список:\n";
    
    for (auto it = double_list_1.begin(); it != double_list_1.end(); ++it) {
        std::cout << *it << " "; 
    }
    
    std::cout << std::endl;

    return 0;
}
