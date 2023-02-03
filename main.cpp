/***********
 * NOTE:    I tried to finish as much as possible, but due to my VirtualBox being wiped clean twice
 *          (once on the 26th, another time on the 30th) and losing my data and the amount of work I
 *          have to complete and midterms for all my other classes as well, I wasn't able to prioritize completing
 *          this as much as I would have preferred. In the future, I'll do my best to ensure
 *          I have a failsafe for these situations. I should also note that the program does not compile currently.
 *
 * Using a linked list for the data structure involved with storing the commands and descriptions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Advantage:        A linked list has a dynamic size. A linked list can grow or shrink as needed, as nodes can be added
 *                   or removed as necessary. In the case of its application for this PA, it is great as we don't know
 *                   ahead of time exactly how many commands (and their respective descriptions) will be stored for the
 *                   game. Using a linked list eliminates that worry.
 *
 * Disadvantage:    Linked lists have a slower access time compared to arrays. This is because they need to traverse the
 *                  list in order to find a specific element, whereas elements in an array can be accessed through
 *                  indexing. This means it would take more time to find a specific command (and its respective description)
 *                  when attempting to delete or edit it.
************/

#include "linuxgame.h"

int main(void) {
    int input;
    string fProfiles = "profiles.csv", fData = "commands.csv", playerName;
    vector<Player> playerList = parseProfiles(fProfiles);
    List<Node<Data>> dataList;
    parseData(fData, dataList);

    do {
        printMenu();
        cout << ">> ";
        cin >> input;

        do {
            cout << "Invalid option selected. Please select an option from the menu." << endl;
            cout << ">> ";
            cin >> input;
        } while (input < 1 || input > 7);

        switch (input) {
        case 1:
            printRules();
            break;
        case 2:
            system("cls");
            playerName = getPlayername();
            start(dataList, playerList, playerName, 2);
            break;
        case 3:
            system("cls");
            playerName = getPlayername();
            start(dataList, playerList, playerName, 3);
            break;
        case 4:
            addCmd(dataList);
        case 5:
            removeCmd(dataList);
        case 6:
            displayAll();
        case 7:
            saveAndExit(dataList, playerList, fData, fProfiles);
        }

    } while (input != 7);
}