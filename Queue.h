#ifndef ASP_QUEUE_H
#define ASP_QUEUE_H
#include <string>
#include <iostream>


using namespace std;

//covrovi stabla
struct Node{
    string info;
    Node* left;
    Node* right;

    Node(string info, Node* left = nullptr, Node* right = nullptr) : info(info), left(left), right(right){}

};

//elementi reda
struct NodeQ{
    Node* qnode;
    NodeQ* next;

    NodeQ(Node* qnode, NodeQ* next = nullptr) : qnode(qnode), next(next){}

};

class Queue {
    NodeQ* front;
    NodeQ* rear;

public:

    Queue( NodeQ* front = nullptr, NodeQ* rear = nullptr) : front(front), rear(rear){}

    bool isEmpty(){ return front== nullptr; }

    void insertQ(Node* treeNode){
        NodeQ* newN = new NodeQ(treeNode);
        if (!front) {
            front = rear = newN;
        }
        else{
            rear->next = newN;
            rear = newN;
        }

    }



    Node* deleteQ(){
        Node* tmp = front->qnode;
        if(front == rear){
            front = rear = nullptr;
        }
        else{
            front = front->next;
        }
        return tmp;
    }

};



#endif //ASP_QUEUE_H
