#include <string>
#include <iostream>
#ifndef ASP_GRAPH_H
#define ASP_GRAPH_H
#include "Queue.h"
using namespace std;

struct nodeList{
    Node* node;
    nodeList* next;
    nodeList(Node* node, nodeList* next = nullptr) : node(node), next(next){}
};

struct List{
    nodeList* head;
    nodeList* tail;
    List(nodeList* head = nullptr, nodeList* tail = nullptr) : head(head), tail(tail){}

    nodeList* append(Node* node){
        nodeList* newN = new nodeList(node);
        if(!head){
            head = tail = newN;
        }
        else{
            tail->next = newN;
            tail = newN;
        }
        return head;
    }

    bool exists(Node* node){
        nodeList* tmp = head;
        while(tmp){
            if(tmp->node->info == node->info){
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    void clear() {
        if(!head){
            return;
        }
        else{
            nodeList* tmp = head;
            nodeList* old;
            while(tmp){
                old = tmp;
                tmp = tmp->next;
                delete old;
            }
            head = nullptr;
        }
    }
};

struct arrElem{
    string info;
    int cnt;
    arrElem* next;

    arrElem(string info, int cnt = 0, arrElem* next = nullptr) : info(info), cnt(cnt), next(next){}

};

struct Arr {
    arrElem *head;
    arrElem* tail;

    Arr(arrElem *head = nullptr, arrElem* tail = nullptr) : head(head), tail(tail) {}

    arrElem *add(arrElem* el) {
        if(!head){
            head = tail = el;
        }
        else{
            tail->next = el;
            tail = el;
        }
        return head;
    }

    arrElem* getInfo(string rootName){
        arrElem* tmp = head;
        while(tmp){
            if(tmp->info == rootName){
                break;
            }
            tmp = tmp->next;
        }
        return tmp;
    }
};
class Graph {
    int cnt=0;
    int cap;
    List** headers;

public:

    Graph() = default;

    Graph(int capacity) : cap(capacity){
        headers = new List*[capacity];
        for(int i = 0;i < capacity; i++){
            headers[i] = nullptr;
        }

    }

    int getCap() const {
        return cap;
    }

    List& getArr(int i) {
        return *this->headers[i];
    }

    List& getArrInfo(string rootName){
        int i;
        for(i = 0; i < cap; i++){
            if(headers[i]->head->node->info == rootName){
                break;
            }
        }
        return *this->headers[i];
    }

    void add(List* list){
        headers[cnt] = list;
        cnt++;
    }
};





#endif //ASP_GRAPH_H
