#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <string.h>
using std::ifstream;
using std::stringstream;
using std::istringstream;
using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;


class Data {
public:
    Data(const string& cmd, const string& desc, const int points) : cmd(cmd), desc(desc), points(points) {}

    string getCmd() const { return cmd; }
    string getDesc() const { return desc; }
    int getPoints() const { return points; }

private:
    string cmd;
    string desc;
    int points;
};



template <class NODETYPE>
class Node {
public:
    Node(const NODETYPE& data) : data(data), pNext(nullptr) {}

    NODETYPE getData() const { return data; }
    Node<NODETYPE>* getNextPtr() const { return pNext; }

    void setNextPtr(Node<NODETYPE>* pNext) { pNext = pNext; }

private:
    NODETYPE data;
    Node<NODETYPE>* pNext;
};

template <class NODETYPE>
class List {
private:
    Node<NODETYPE>* pHead;
    Node<NODETYPE>* pTail;
    int nodecount;

    Node<NODETYPE>* getNewNode(const NODETYPE& data, Node<NODETYPE>* pNext = nullptr);
public:
    List() : pHead(nullptr), pTail(nullptr), nodecount(0) {}
    ~List() {};

    int getNodecount() const { return nodecount; }
    Node<NODETYPE>* getpHead() const { return *pHead; }

    // bool isEmpty() const;
    // void insertAtFront(const NODETYPE& data);
    // void insertAtBack(const NODETYPE& data);
    // bool remove(const string cmd);
    // void printList() const;
    // const NODETYPE* search(const string& cmd);

    Node<NODETYPE>* getNodeByIndex(int index) {
        if (index < 0 || index > nodecount) {
            return NULL;
        }

        Node<NODETYPE>* pCurr = pHead;

        for (int i = 0; i < nodecount; i++) {
            if (i == index) {
                return pCurr;
            }
            else {
                pCurr = pCurr->getNextPtr();
            }
        }
    }





bool isEmpty() const {
    return pHead == nullptr;
}

void insertAtFront(const NODETYPE& data) {
    Node<NODETYPE>* pNew = new Node<NODETYPE> (data);
    if (isEmpty()) {
        pTail = pNew;
    }
    pHead = pNew;
    nodecount += 1;
}

void insertAtBack(const NODETYPE& data) {
    Node<NODETYPE>* pNew = getNewNode(data);
    if (isEmpty()) {
        pHead = pNew;
    }
    else {
        pTail->setNextPtr(pTail);
    }
    pTail = pNew;
    nodecount += 1;
}

bool remove(const string cmd) {
    Node<NODETYPE>* pPrev = nullptr;
    Node<NODETYPE>* pCurr = pHead;

    while (pCurr != nullptr && cmd.compare(pCurr->getData().getCmd()) != 0) {
        pPrev = pCurr;
        pCurr = pCurr->getNextPtr();
    }

    // If cmd can't be found
    if (pCurr == nullptr) {
        return false;
    }

    // Removing the node
    if (pPrev == nullptr) {
        pHead = pHead->getNextPtr();
    }
    else {
        pPrev->setNextPtr(pCurr->getNextPtr());
    }

    // If necessary; Update pTail
    if (pCurr == pTail) {
        pTail = pPrev;
    }

    delete pCurr;
    return true;
}

void printList() const {
    Node<NODETYPE>* pCurr = pHead;
    int i = 1;

    while (pCurr != nullptr) {
        cout << i << "\t" << pCurr->getData().getCmd() << "\t\"" << pCurr->getData().getDesc() << "\"" << endl;
        pCurr = pCurr->getNextPtr;
    }

    cout << endl;
}

const NODETYPE* search(const string& cmd) {
    Node<NODETYPE>* pCurr = pHead;
    while (pCurr != nullptr) {
        if (pCurr->getData().getCmd() == cmd) {
            return &pCurr->data;
        }
        pCurr = pCurr->getNextPtr();
    }
    return false;
}

};
#endif