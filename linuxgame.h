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
#include "list.h"

using std::ifstream;
using std::stringstream;
using std::istringstream;
using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;



class Player {
public:
    Player(const string& name = "", int points = 0) : name(name), points(points) {}
    ~Player() {}

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
void parseData(const string& filename, List<Data>& dataList);

string getPlayername();
void start(List<Data> dataList, vector<Player> playerList, string playerName, int option);
Player loadGame(vector<Player> playerList, string playerName);
int checkPlayerExists(string playerName, vector<Player> playerList);
void removeCmd(List<Data> dataList);
void addCmd(List<Data> dataList);
void displayAll();
void saveAndExit(List<Data> dataList, vector<Player> playerList, string dataFilename, string stringFilename);

#endif