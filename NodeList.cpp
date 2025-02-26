#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    //constructor
    this->length = 0;
}

NodeList::~NodeList(){
    //destructor
    for(int i = 0; i < this->length; i++){
        delete this->nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
    //copy constructor
    this->length = other.getLength();
    for(int i = 0; i < this->length; i++){
        this->nodes[i] = new Node(*other.getNode(i));
    }
}

int NodeList::getLength(){
    return this->length;
}

void NodeList::addElement(Node* newPos){
    //add a copy of the node to the back of the list
    Node* node = new Node(*newPos);
    this->nodes[this->length] = node;
    this->length++;
}

Node* NodeList::getNode(int i){
    if (i < 0 || i >= this->length)
        return nullptr;

    return this->nodes[i];
}

bool NodeList::contains(Node* node){
    //check if the node is in the list
    for(int i = 0; i < this->length; i++){
        if(this->nodes[i]->getRow() == node->getRow() &&

        this->nodes[i]->getCol() == node->getCol()){
            return true;
        }
    }
    return false;
}

void NodeList::removeElement(Node* node){
    //remove the node from the list
    for(int i = 0; i < this->length; i++){
        if(this->nodes[i] == node){
            delete this->nodes[i];
            for(int j = i; j < this->length - 1; j++){
                this->nodes[j] = this->nodes[j + 1];
            }
            this->length--;
            break;
        }
    }
}