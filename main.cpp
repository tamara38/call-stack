#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Queue.h"
#include "Graph.h"
using namespace std;

Node* createNode(string data){
    Node* newN = new Node(data);
    newN->left = nullptr;
    newN->right = nullptr;
    return newN;
}

//ucitavanje stabla
Node* loadTree(Node* root){
    string line;
    string data;
    ifstream file;
    file.open("demo.txt");

    root= nullptr;
    Node* tmp;
    Node* prev = nullptr;
    bool found = false;

    while(getline(file,line)){
        stringstream i(line);
        tmp = root;
        while(getline(i,data,' ')){
            found = false;
            if(!root){
                root = createNode(data);
                tmp = root;
            }

            if(root->info==data){
                continue;
            }

            if(!(tmp->left)){
                Node* newN = createNode(data);
                tmp->left = newN;
                tmp = newN;
                continue;
            }
            else{
                if(tmp->left->info == data){
                    tmp = tmp->left;
                    continue;
                }
                else{
                    prev = tmp->left;
                    tmp = tmp->left->right;
                    while(tmp){
                        if(tmp->info == data){
                            found = true;
                            break;
                        }
                        prev = tmp;
                        tmp = tmp->right;
                    }
                    if(!found){
                        Node* newN = createNode(data);
                        prev->right = newN;
                        tmp = newN;
                    }
                    continue;
                }
            }
        }
    }
    file.close();
    return root;
}

//stampa
void print(Node* root, Queue& queue){

    if(!root){
        cout<<"Stablo je prazno!\n";
        return;
    }

    Node* prev = nullptr;
    queue.insertQ(root);
    queue.insertQ(nullptr);
    cout<<root->info<<"\n";
    string lvlord = "Level order: " + root->info+" ";
    while(!(queue.isEmpty())){
        Node* tmp = queue.deleteQ();
        if(!tmp){
            cout<<"\n";
            if(!(queue.isEmpty())){
                queue.insertQ(nullptr);
            }
        }
        else{
            if(tmp->left) {
                prev = tmp;
                tmp = tmp->left;
                while(tmp){
                    queue.insertQ(tmp);
                    cout<<tmp->info<<"(child of("<<prev->info<<"))\t";
                    lvlord += tmp->info + " ";
                    tmp = tmp->right;
                }

            }
        }
    }
    cout<<"\n";
    cout<<lvlord<<"\n";
}

//dodavanje
Node* add(Node* rootN){
    string line,data;
    int i = 0;
    cout<<"Unesite programski stek koji zelite da dodate:\n";
    getline(cin,line);
    stringstream input(line);
    Node* root =rootN,*tmp = rootN, *prev = nullptr;
    bool found = false;
    while(getline(input, data, ' ')){
        i++; found = false;
        if(i == 1 && root->info!=data){
            cout<<"Neispravan format programskog steka!\n";
            return root;
        }
        if(!root){
            root = createNode(data);
            tmp = root;
        }

        if(root->info==data){
            continue;
        }

        if(!(tmp->left)){
            Node* newN = createNode(data);
            tmp->left = newN;
            tmp = newN;
            continue;
        }
        else{
            if(tmp->left->info == data){
                tmp = tmp->left;
                continue;
            }else{
                prev = tmp->left;
                tmp = tmp->left->right;
                while(tmp){
                    if(tmp->info == data){
                        found = true;
                        break;
                    }
                    prev = tmp;
                    tmp = tmp->right;
                }
                if(!found){
                    Node* newN = createNode(data);
                    prev->right = newN;
                    tmp = newN;
                }
                continue;
            }
        }
    }
    return root;
}

Node* remove(Node* root) {
    if (!root) {
        cout << "Greska! Prazno stablo!\n";
        return nullptr;
    } else {
        Node *old = nullptr;
        Node *parent = nullptr;
        Node *prev = nullptr;
        Node *tmp = root;
        string line, data;
        bool left = false;
        bool right = false;
        bool changed = false;
        cout << "Unesite programski stek za uklanjanje:\n";
        getline(cin, line);
        stringstream input(line);

        while (getline(input, data, ' ')) {
            if(tmp->info == data){
                if(tmp->left && tmp->left->right){
                    parent = tmp;
                    left = true;
                    right = false;
                }
                tmp = tmp->left;
                continue;
            }
            else{
                parent = tmp;
                right = true;
                left = false;
                tmp = tmp->right;
                while(tmp){
                    if(tmp->info == data){
                        break;
                    }
                }
                tmp = tmp->left;
                continue;
            }
        }
        Node *deleteOld = nullptr;
        if(!parent){
            old = root;
            while(old){
                deleteOld = old;
                old = old->left;
                deleteOld->left = nullptr;
                delete deleteOld;
            }
            root = nullptr;
        }
        else{
            if(left){
                old = parent->left;
                parent->left = old->right;
                while(old){
                    deleteOld = old;
                    old = old->left;
                    deleteOld->left = nullptr;
                    delete deleteOld;
                }
            }else if(right){
                old = parent->right;
                parent->right = old->right;
                while(old){
                    deleteOld = old;
                    old = old->left;
                    deleteOld->left = nullptr;
                    delete deleteOld;
                }
            }
        }

    }
    return root;
}

void deleteTree(Node* &root, Queue& queue){
    if(root == nullptr) {
        cout<<"Greska! Prazno stablo!\n";
        return;
    }
    else{
        Node* tmp,*old = nullptr;
        queue.insertQ(root);
        while(!(queue.isEmpty())){
            tmp = queue.deleteQ();
            if(tmp->left){
                queue.insertQ(tmp->left);
            }
            if(tmp->right){
                queue.insertQ(tmp->right);
            }
            delete tmp;
        }
        root = nullptr;
    }
}

List& convert(Node* root,List& list){
    int i = 1;
    Node* tmp;
    nodeList* curr;
    if(!root){
        cout<<"Stablo je prazno!\n";
    }
    else{
        Queue queue;
        Node* nodeR = nullptr;
        queue.insertQ(root);
        Node* newN = new Node(root->info);
        newN->left = root->left;
        newN->right = root->left->right;
        list.append(newN);
        while(!(queue.isEmpty())){
            tmp = queue.deleteQ(); //*---------------------level order----------------------------*
            if(tmp->left){
                nodeR = tmp->left;
                while(nodeR){
                    Node* newNl = new Node(nodeR->info);
                    if(nodeR->left) {
                        newNl->left = nodeR->left;
                        if(nodeR->left->right){
                            newNl->right = nodeR->left->right;
                        }
                        else{
                            newNl->right = nullptr;
                        }
                    }
                    else{
                        newNl->left = nullptr;
                        newNl->right = nullptr;
                    }

                    queue.insertQ(newNl);
                    nodeR = nodeR->right;
                }

            }
            //*----------------------------------------------------------------------------------*
           if(list.exists(tmp)){
                curr = list.head;
                while(curr->node->info!=tmp->info){
                    curr = curr->next;
                }
                if(curr->node->left && curr->node->right){
                    continue;
                }
                else if(curr->node->left && !(curr->node->right)){
                    if(tmp->left){
                        if (curr->node->left->info != tmp->left->info) {
                            curr->node->right = tmp->left;
                        }
                        if(tmp->left->right) {
                            if (curr->node->left->info != tmp->left->right->info) {
                                curr->node->right = tmp->left->right;
                            }
                        }
                    }

                }
                else if(curr->node->right && !(curr->node->left)){
                    if(tmp->left) {
                        if ((curr->node->right->info != tmp->left->info)) {
                            curr->node->left = tmp->left;
                        }
                        if(tmp->left->right) {
                            if (curr->node->right->info != tmp->left->right->info) {
                                curr->node->left = tmp->left->right;
                            }
                        }
                    }

                }
           }
           else{
               list.append(tmp);
               i++;
           }
        }
    }
    return list;
}

int capacity(List& list){
    int i = 0;
    nodeList* tmp = list.head;
    while(tmp){
        i++;
        tmp = tmp->next;
    }
    return i;
}

Graph& graphLinkedRepresantation(int n, Graph& graph, List& list){
    nodeList* curr = list.head;
    for(int j = 0; j < n; j++) {
        List* list1 = new List;
        list1->append(curr->node);
        if (curr->node->left) {
            Node* newN = createNode(curr->node->left->info);
            list1->append(newN);
        }
        if (curr->node->right) {
            Node* newN = createNode(curr->node->right->info);
            list1->append(newN);
        }
        graph.add(list1);
        curr = curr->next;
    }
    return graph;
}

void printGraph(int n, Graph& graph){
    if(graph.getCap() == 0){
        cout<<"Graf je prazan\n";
    }
    else{
        nodeList *tmp;
        List l;
        int qn = graph.getCap();
        cout<<"Ulancana reprezentacija grafa => Lista susednosti:\n";
        for(int i = 0; i<n; i++){
            l = graph.getArr(i);
            tmp = l.head;
            while(tmp){
                cout<<tmp->node->info<<" -> ";
                tmp = tmp->next;
            }
            cout<<"NULL\n";
        }
    }
}

void printBFS(int n,Graph& graph){
    if(graph.getCap() == 0){
        cout<<"Graf je prazan\n";
    }
    else{
        Queue queue;
        Arr arr;
        Node* tmp = nullptr;
        arrElem* tmpArr = nullptr;
        nodeList* tmpNode = nullptr;
        bool posecen = false;
        n = graph.getCap();
        for(int i = 0; i < n; i++){
            arrElem* elem = new arrElem(graph.getArr(i).head->node->info);
            elem->cnt = 0;
            arr.add(elem);
        }
        string print = "BFS obilazak: ";
        queue.insertQ(graph.getArr(0).head->node);
        tmpArr = arr.getInfo(graph.getArr(0).head->node->info);
        tmpArr->cnt = 1;
        print+=tmpArr->info + " ";
        while(!(queue.isEmpty())){
            tmp = queue.deleteQ();
            tmpNode = graph.getArrInfo(tmp->info).head->next;
            while (tmpNode){
                tmpArr = arr.getInfo(tmpNode->node->info);
                if(!tmpArr->cnt){
                    tmpArr->cnt = 1;
                    posecen = true;
                }
                if(posecen){
                    print+= tmpNode->node->info + " ";
                    queue.insertQ(tmpNode->node);
                    posecen = false;
                }
                tmpNode = tmpNode->next;
            }
        }
        cout<<print<<"\n";
    }

}

bool cycle(Graph& graph, Queue& queue){
    int n = graph.getCap();
    nodeList* tmp,*tmpNext;
    Arr arr;
    for(int i = 0; i < n; i++){//-----------------------formiranje arr sa brojem ulaznih grana u cvorove--------*
        arrElem* element = new arrElem(graph.getArr(i).head->node->info);
        int cnt = 0;
        for(int i = 0; i < n; i++){
            tmp = graph.getArr(i).head->next;
            while(tmp){
                if(element->info == tmp->node->info) cnt++;
                tmp = tmp->next;
            }
        }
        element->cnt = cnt;
        arr.add(element);
    }//-------------------------------------------ubacivanje u red cvorova koji imaju 0 ulaznih grana----------------*
    int count = 0;
    arrElem* curr = arr.head;
    while(curr){
        if(curr->cnt == 0){
            for(int i = 0;i<n;i++){
                if(curr->info == graph.getArr(i).head->node->info){
                    queue.insertQ(graph.getArr(i).head->node);
                    count++;
                }
            }
        }
        curr = curr->next;
    }
    curr = arr.head;
    Node* nd;
    while(!queue.isEmpty()){
        nd = queue.deleteQ();
        for(int i = 0; graph.getArr(i).head->node->info!=nd->info; i++) {
            tmpNext = graph.getArr(i).head->next;
            while (curr) {
                if (curr->info == tmpNext->node->info) {
                    --curr->cnt;
                    if (!curr->cnt) {
                        for (int j = 0; graph.getArr(j).head->node->info != curr->info; j++) {
                            queue.insertQ(graph.getArr(j).head->node);
                        }
                        count++;
                    }
                }
                curr = curr->next;
            }
        }
    }
    if(count == n){
        return false;
    }
    else{
        return true;
    }
}


int main() {
    int choice;
    Node *root;
    Queue queue;
    List list;
    Graph graph;
    int x;
    cout << "0.Prekid programa\n"
            "1.Ucitavanje skupa programskih stekova iz tekstualnog fajla i formiranje stabla\n";
    cout << "2.Dodavanje novog programskog steka u stablo\n"
            "3.Uklanjanje programskog steka iz stabla\n"
            "4.Ispis stabla\n"
            "5.Brisanje stabla iz memorije\n"
            "6.Konverzija formiranog stabla u graf\n"
            "7.Ispis grafa\n"
            "8.Detekcija rekurzivnih poziva funkcija\n";
    while (true) {
        cout << "Unesite redni broj zeljene stavke radi njenog izvrsenja:";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            default:{
                cout<<"Pogresan broj! Pokusajte ponovo!\n";
            }
            case 0: {
                exit(0);
                break;
            }
            case 1: {
                root = loadTree(root);
                break;
            }
            case 2: {
                root = add(root);
                break;
            }
            case 3: {
                root = remove(root);
                break;
            }
            case 4: {
                print(root, queue);
                break;
            }
            case 5: {
                deleteTree(root, queue);
                break;
            }
            case 6: {
                list.clear();
                list = convert(root,list);
                x = capacity(list);
                graph = Graph(x);
                graph = graphLinkedRepresantation(x, graph, list);
                break;
            }
            case 7: {
                printGraph(x, graph);
                printBFS(x,graph);
                break;
            }
            case 8: {
                if (cycle(graph, queue)) {
                    cout << "Ciklus postoji\n";
                } else {
                    cout << "Ciklus ne postoji\n";
                }
                break;
            }
        }
    }
}




