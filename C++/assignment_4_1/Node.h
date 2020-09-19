//
// Created by mohasa18 on 9/13/2020.
//

#ifndef ASSIGNMENT_4_1_NODE_H
#define ASSIGNMENT_4_1_NODE_H
#include <iostream>
#include <string>
#include <sstream>

void Display();

using namespace std;

/* List Node: */

template <class T>
class MyNode {
private:
    T data;
public:
    MyNode* next;
    MyNode* previous;

    T getData();
    MyNode(T data){this->data = data;}
    ~MyNode(){}
};

/* Linked List: */

template <class T>
class MyList {
private:
    T* head;
    T* tail;
    std::size_t list_size;

public:
    MyList();
    ~MyList();


    std::size_t size();
    void push_back(T* new_node);
    void remove(std::size_t position);
    T* get(std::size_t index);


    void printList();
    void printOnce(std::size_t posi);
};

//
// Created by mohasa18 on 9/13/2020.
//







using namespace std;

template <class T>
T MyNode<T>::getData() {
    return this->data;
}



template <class T>
MyList<T>::MyList() {
    this->head = NULL;
    this->tail = NULL;
    this->list_size = 0;
}

template <class T>
MyList<T>::~MyList() {
    while (this->head) {
        T* next = this->head->next;
        delete this->head;
        this->list_size = this->list_size - 1;
        this->head = next;
    }
}



template <class T>
void MyList<T>::printList() {

    T* temp = this->head;
    while(temp) {
        cout << temp->getData() << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <class T>
void MyList<T>::printOnce(std::size_t posi) {

    T* temp = get(posi);
    cout << temp->getData() << endl;

}


template <class T>
std::size_t MyList<T>::size() {

    std::size_t size = 0;
    T* temp = this->head;
    while (temp) {
        size++;
        temp = temp->next;
    }
    this->list_size = size;
    return this->list_size;
}

template <class T>
void MyList<T>::push_back(T* new_node) {
    new_node->next = NULL;
    new_node->previous = NULL;

    if (this->head == NULL) {
        this->head = new_node;
        this->tail = this->head;
        this->list_size = this->list_size + 1;
    } else {
        this->tail->next = new_node;
        new_node->previous = this->tail;
        this->tail = new_node;
        this->list_size = this->list_size + 1;
    }
}


template <class T>
void MyList<T>::remove(std::size_t position) {
    if(position == ((this->list_size)-1)) {
        T* temp = this->tail;
        tail = temp->previous;
        tail->next = NULL;
        this->list_size = this->list_size - 1;
        delete  temp;

    }else if (position == 0){
        T* temp = this->head;
        head = temp->next;
        this->list_size = this->list_size - 1;
        delete  temp;
    }else if(position != 0){
        std::size_t position_n_1 = position - 1;
        T *temp1 = get(position_n_1);

        T *temp2 = get(position);
        temp1->next = temp2->next;
        this->list_size = this->list_size - 1;
        delete temp2;
    }
}

//operator []


template <class T>
T* MyList<T>::get(std::size_t index) {
    if (index == 0) {
        return this->head;
    } else if (index == this->list_size - 1) {
        return this->tail;
    } else if (index < 0 || index >= this->list_size) {
        return NULL;
    }
    if (index < this->list_size / 2) {
        T* temp = this->head;
        std::size_t i = 0;
        while (temp) {
            if (i == index) { return temp; }
            i++;
            temp = temp->next;
        }
    } else {
        T* temp = this->tail;
        std::size_t i = this->list_size - 1;
        while (temp) {
            if (i == index) { return temp; }
            i--;
            temp = temp->previous;
        }
    }
    return NULL;
}

void Display(){

    std::cout << "1. Add integer" << std::endl;
    std::cout << "2. Show integer" << std::endl;
    std::cout << "3. Remove integer" << std::endl;

    std::cout << "4. Add string"<< std::endl;
    std::cout << "5. Show string" << std::endl;
    std::cout << "6. Remove string" << std::endl;

    std::cout << "7. Print information" << std::endl;
    std::cout << "8. Exit" << std::endl;

}

//
//void stackAsInt() {
//
//    MyList<MyNode<int> > stack;
//    int i;
//    cin >> i;
//    stack.push_back(new MyNode<int>(i));
//
//    cout << "List Size: " << stack.size() << endl;
//
//    stack.printList();
//
//}
//
//void AddInteger(int data){
//
//
//
//}
#endif //ASSIGNMENT_4_1_NODE_H
