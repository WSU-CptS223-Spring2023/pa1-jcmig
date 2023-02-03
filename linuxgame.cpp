#include "linuxgame.h"

template <typename NODETYPE>
bool List<NODETYPE>::isEmpty() const {
    return pHead == nullptr;
}

template <typename NODETYPE>
void List<NODETYPE>::insertAtFront(const NODETYPE& data) {
    Node<NODETYPE>* pNew = getNewNode(data, pHead);
    if (isEmpty()) {
        pTail = pNew;
    }
    pHead = pNew;
    nodecount += 1;
}

template <typename NODETYPE>
void List<NODETYPE>::insertAtBack(const NODETYPE& data) {
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

template <typename NODETYPE>
bool List<NODETYPE>::remove(const string cmd) {
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

template <typename NODETYPE>
void List<NODETYPE>::printList() const {
    Node<NODETYPE>* pCurr = pHead;
    int i = 1;

    while (pCurr != nullptr) {
        cout << i << "\t" << pCurr->getData().getCmd() << "\t\"" << pCurr->getData().getDesc() << "\"" << endl;
        pCurr = pCurr->getNextPtr;
    }

    cout << endl;
}

template <typename NODETYPE>
const NODETYPE* List<NODETYPE>::search(const string& cmd) {
    Node<NODETYPE>* pCurr = pHead;
    while (pCurr != nullptr) {
        if (pCurr->getData().getCmd() == cmd) {
            return &pCurr->data;
        }
        pCurr = pCurr->getNextPtr();
    }
    return false;
}

void printMenu() {
    cout << "Please select an option listed below:" << endl;
    cout << "1. Game Rules" << endl;
    cout << "2. Play New Game" << endl;
    cout << "3. Load Previous Game" << endl;
    cout << "4. Add Command" << endl;
    cout << "5. Remove Command" << endl;
    cout << "6. Display All Commands" << endl;
    cout << "7. Save and Exit" << endl;
}

void printRules() {
    system("cls");
    cout << "R U L E S   O F   T H E   G A M E" << endl;
    cout << "This is a interactive text-based single-player matching game." << endl;
    cout << "The objective of the game is to match Linux commands to appropriate" << endl;
    cout << "descriptions of those commands. " << endl;
    cout << "You decide how many questions you'd like to be asked." << endl;
    cout << "If you get it right, the points corresponding to that command" << endl;
    cout << "to your total score. Get it wrong and it'll be deducted from" << endl;
    cout << "your total score." << endl;
    char input;
    cin >> input;
    if (input) {
        system("cls");
    }
}

vector<Player> parseProfiles(string& filename) {
    vector<Player> players;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream linestream(line);
        string name;
        int points;

        getline(linestream, name, ',');
        linestream >> points;

        players.push_back(Player(name, points));
    }

    return players;
}


void parseData(const string& filename, List<Node<Data>>& dataList) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string cmd, desc;
        int points;

        getline(ss, cmd, ',');
        getline(ss, desc, ',');
        ss >> points;

        desc = desc.substr(1, desc.length() - 2);

        Data data(cmd, desc, points);
        dataList.insertAtFront(data);
    }
}

string getPlayername() {
    string playerName;
    cout << "Enter player name: ";
    cin >> playerName;
    return playerName;
}

// start() will be used for new game and load game, difference being 
void start(List<Node<Data>> dataList, vector<Player> playerList, string playerName, int option) {
    int numQuestions;
    int totalPoints = 0;

    if (option == 2) {
        int checkPlayer = checkPlayerExists(playerName, playerList);
        int resetSelect;
        if (checkPlayer) {
            cout << "Profile for " << playerName << " already exists!" << endl;
            cout << "Press 1 to load your profile or press 2 to restart >> ";
            cin >> resetSelect;

            do {
                cout << "Invalid option selected. Please select either 1 or 2  >> ";
                cin >> resetSelect;
            } while (resetSelect < 1 || resetSelect > 2);

            if (resetSelect == 1) {
                option = 3;
            }
            else {
                cout << "Resetting stats!" << endl;
                playerList[checkPlayer].setPoints(0);
            }
        }
    }

    if (option == 3) {
        Player currPlayer = loadGame(playerList, playerName);
        totalPoints = currPlayer.getPoints();
        cout << "Welcome back, " << currPlayer.getName() << "!" << endl;
        cout << "Current total points: " << currPlayer.getPoints() << endl;
    }

    cout << "Enter number of questions (5 - 30): ";
    cin >> numQuestions;

    srand(time(NULL));

    for (int i = 0; i < numQuestions; i++) {

        int randomIndex = rand() % dataList.getNodecount();
        Data selectedData = dataList.getNodeByIndex(randomIndex)->getData();
        int pointsAwarded = selectedData.getPoints();

        cout << "Command: " << selectedData.getCmd() << endl;

        vector<string> descList;
        descList.push_back(selectedData.getDesc());

        for (int j = 0; j < 2; j++) {
            int randomDescIndex = rand() % dataList.getNodecount();
            Data randomData = dataList.getNodeByIndex(randomDescIndex)->getData();
            descList.push_back(randomData.getDesc());
        }

        for (int j = 0; j < 3; j++) {
            int randomIndex = rand() % descList.size();
            string selectedDesc = descList[randomIndex];
            cout << j + 1 << ": " << selectedDesc << endl;

            for (int k = randomIndex; k < descList.size() - 1; k++) {
                descList[k] = descList[k + 1];
            }

            descList.pop_back();
        }

        int userSelection;
        cout << "Enter your selection: ";
        cin >> userSelection;

        if (descList[userSelection - 1] == selectedData.getDesc()) {
            cout << "Correct!" << endl;
            cout << "Points Awarded: " << pointsAwarded << endl;
        }
        else {
            cout << "Incorrect!" << endl;
            cout << "Points Deducted: " << (pointsAwarded *= -1) << endl;
        }

        cout << "Current total points: " << (totalPoints += pointsAwarded) << endl;
        cout << "- - - - - - - - - - - - - - - - - - - -" << endl;
    }
}

Player loadGame(vector<Player> playerList, string playerName) {
    int playerIndex = checkPlayerExists(playerName, playerList);
    if (playerIndex) {
        return playerList[playerIndex];
    }
}

int checkPlayerExists(string playerName, vector<Player> playerList) {
    for (int i = 0; i < playerList.size(); i++) {
        if (playerName == playerList[i].getName()) {
            return i;
        }
        else {
            // If player does not exist, they are "added" to the end of the list and that index is returned.
            return NULL;
        }
    }
}

void removeCmd(List<Node<Data>> dataList) {
    string cmdRemove;
    int exists;

    cout << "Enter the command to be removed: ";
    cin >> cmdRemove;
    dataList.remove(cmdRemove);
}

void addCmd(List<Node<Data>> dataList) {
    string cmdAdd, descAdd;
    int pointsAdd;

    cout << "Please enter the command name: ";
    cin >> cmdAdd;

    cout << "Please enter the command description: " << endl;
    cout << ">> ";
    cin >> descAdd;

    cout << "Please enter the points for this command: ";
    cin >> pointsAdd;


}

