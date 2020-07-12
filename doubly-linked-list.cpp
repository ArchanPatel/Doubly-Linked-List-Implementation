#include "doubly-linked-list.h"
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = prev = nullptr;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = tail_ = nullptr;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node *current = head_;

    while (current != nullptr) { //delete each node
        current = head_->next;
        delete head_;
        head_ = current;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
    delete head_;
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0)
        return true;
    else
        return false;
}

bool DoublyLinkedList::full() const
{
    if (size() == capacity())
        return true;
    else
        return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index > size())
        return tail_->value;
    else{
        if (size()/2 > index){ //iterate from the start
            Node *current = head_;
            int i = 0;
            while (i < index) {
                current = current->next;
                i++;
            }
            return current->value;
        }
        else{ //iterate from the end
            Node *current = tail_;
            int i = size()-1;
            while (i > index) {
                current = current->prev;
                i--;
            }
            return current->value;
        }
    }
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node *current = head_;
    for (int i=0; i < size(); i++) {
        if (current->value == value)
            return i;
        current = current->next;
    }
    return size();
}

void DoublyLinkedList::print() const
{
    if (empty())
        cout<<"the list is empty!"<<endl;
    Node* current = head_;
    while (current->next != nullptr) {
        cout << current->value << " <--> ";
        current = current->next;
    }
    cout << current->value << endl;
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node* current = head_;
    for (int i = 0; i < index; i++){
        current = current->next;
    }
    return current;

}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    //check position validity, compare with 0 and size,
    //if not valid, report error
    if (index > size() || full()){
        cout<<"cannot insert value"<<endl;
        return false;
    }
    if (index == 0 && size() == 0){ //insert into empty list
        Node* temp = new Node(value);
        size_++;
        head_ = temp;
        tail_ = temp;
        return true;
    }
    else if (index == 0) //insert at the front
        insert_front(value);
    else if (index == size()) //insert at the back
        insert_back(value);
    else { //insert at the index value
        size_++;
        Node* temp = new Node(value);
        if (size()/2 >= index) { //iterate from the front
            Node* current = head_;
            for (int i=0; i<index; i++)
                current = current->next;
            temp->prev = current->prev;
            current->prev = temp;
            temp->next = current;
            temp->prev->next = temp;
            return true;
        }
        else { //iterate from the end
            Node* current = tail_;
            for (int i=size()-1; i>index; i--)
                current = current->prev;
            temp->next = current->next;
            current->next = temp;
            temp->prev = current;
            temp->next->prev = temp;
            return true;
        }
    }
}

bool DoublyLinkedList::insert_front(DataType value)
{
    //if not valid, report error
    if (full()){
        cout<<"cannot insert value"<<endl;
        return false;
    }
    Node* temp = new Node(value);
    if (size() == 0){
        size_++;
        head_ = temp;
        tail_ = temp;
    }
    else {
        size_++;
        temp->next = head_;
        head_->prev = temp;
        head_ = temp;
        return true;
    }
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (full()){
        cout<<"cannot insert value"<<endl;
        return false;
    }
    Node* temp = new Node(value);
    if (size() == 0){
        size_++;
        head_ = temp;
        tail_ = temp;
    }
    else{
        size_++;
        temp->prev = tail_;
        tail_->next = temp;
        tail_ = temp;
        return true;
    }
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (index >= size()){ //invalid input
        cout<<"cannot remove from invalid index"<<endl;
        return false;
    }
    else if (empty()){ //cannot remove from empty list
        cout<<"list is already empty"<<endl;
        return false;
    }
    if (index == 0) //remove first node
        remove_front();
    else if (index == size() - 1) //remove last node
        remove_back();

    //remove node at index
    else if (size()/2 > index){ //iterate from the front
        size_--;
        Node* current = head_;
        for (int i = 0; i < index; i++){
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        return true;
    }
    else{ //iterate from the end
        Node* current = tail_;
        for (int i = size()-1; i > index; i--){
            current = current->prev;
        }
        current->next->prev = current->prev;
        current->prev->next = current->next;
        size_--;
        return true;
    }
}

bool DoublyLinkedList::remove_front()
{
    if (empty()){ //cannot remove from empty list
        cout<<"list is already empty"<<endl;
        return false;
    }
    else if (size() == 1){
        delete head_->next;
        head_=tail_= nullptr;
        size_--;
    }
    else {
        Node* temp = head_;
        head_ = head_->next;
        head_->prev = nullptr;

        delete temp;

        size_--;
        return true;
    }
}

bool DoublyLinkedList::remove_back()
{
    if (empty()){ //cannot remove from empty list
        cout<<"list is already empty"<<endl;
        return false;
    }
    else if (size() == 1){
        delete head_->next;
        head_=tail_= nullptr;
        size_--;
    }
    else{

        Node* temp = tail_;
        tail_ = tail_->prev;
        tail_->next = nullptr;

        delete temp;

        size_--;
        return true;
    }
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (index < size()){
        Node* current = head_;
        for (int i = 0; i < index; i++){
            current = current->next;
        }
        current->value = value;
        return true;
    }
    else
        return false;
}

