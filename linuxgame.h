#ifndef PA1
#define _CRT_SECURE_NO_WARNINGS

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
    Node(const Data& data) : data(data), pNext(nullptr) {}

    Data getData() const { return data; }
    Node<NODETYPE>* getNextPtr() const { return pNext; }

    void setNextPtr(Node<NODETYPE>* pNext) { pNext = pNext; }

private:
    Data data;
    Node<NODETYPE>* pNext;
};

template <class NODETYPE>
class List {
public:
    List() : pHead(nullptr), pTail(nullptr), nodecount(0) {}
    ~List();

    int getNodecount() const { return nodecount; }
    Node<NODETYPE>* getpHead() const { return *pHead; }

    bool isEmpty() const;
    void insertAtFront(const NODETYPE& data);
    void insertAtBack(const NODETYPE& data);
    bool remove(const string cmd);
    void printList() const;
    const NODETYPE* search(const string& cmd);

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

private:
    Node<NODETYPE>* pHead;
    Node<NODETYPE>* pTail;
    int nodecount;

    Node<NODETYPE>* getNewNode(const NODETYPE& data, Node<NODETYPE>* pNext = nullptr);
};

class Player {
public:
    Player(const string& name = "", int points = 0) : name(name), points(points) {}
    ~Player();

    string getName() const { return name; }
    int getPoints() const { return points; }

    void setPoints(int newPoints) { points = newPoints; }

private:
    string name;
    int points;
};

void printMenu();
void printRules();

vector<Player> parseProfiles(string& filename);
void parseData(const string& filename, List<Node<Data>>& dataList);

string getPlayername();
void start(List<Node<Data>> dataList, vector<Player> playerList, string playerName, int option);
Player loadGame(vector<Player> playerList, string playerName);
int checkPlayerExists(string playerName, vector<Player> playerList);
void removeCmd(List<Node<Data>> dataList);
void addCmd(List<Node<Data>> dataList);
void displayAll();
void saveAndExit(List<Node<Data>> dataList, vector<Player> playerList, string dataFilename, string stringFilename);

#endif