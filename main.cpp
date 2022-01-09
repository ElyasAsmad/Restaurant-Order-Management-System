/**
 * @file main.cpp
 * 
 * @brief Restaurant Order Management Retail System
 * @version 0.1
 * @date 2021-12-30
 * 
 * @authors
 * - Elyas bin Asmad 2116893
 * - 
 * - 
 * - 
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "initapp.h"
#include "utils.h"

using namespace std;

void ShowOrderScreen(string);

struct CustOrders {
    string tableNumber;
    string orderID;
    string orderName;
    double price;
};

// Define the structure
struct CuisineItem {
    string cuisineId;
    string cuisineName;
    double price;
};

vector<CustOrders> _mainOrders; // Underscore refers to the global variable

void ClearArrow(int stateX, int stateY) {
    gotoXY(stateX, stateY); cout << "  ";
    gotoXY(stateX, stateY + 2); cout << "  ";
}

vector<vector<string>> ReadTableLayout() {

    ifstream inputFile;
    vector<vector<string>> tableArr;
    string colA, colB, colC, colD, colE, colF;

    inputFile.open("TableLayout.csv");

    int i = 0;

    if (!inputFile.fail()) {

        do {

            vector<string> temp;

            getline(inputFile, colA, ','); // Table Col A
            getline(inputFile, colB, ','); // Table Col B
            getline(inputFile, colC, ','); // Table Col C
            getline(inputFile, colD, ','); // Table Col D
            getline(inputFile, colE, ','); // Table Col E
            getline(inputFile, colF, '\n'); // Table Col F

            temp.push_back(colA);
            temp.push_back(colB);
            temp.push_back(colC);
            temp.push_back(colD);
            temp.push_back(colE);
            temp.push_back(colF);

            tableArr.push_back(temp);

            i++;

        } while (inputFile.good());

        tableArr.pop_back();
    }

    return tableArr;
    
}

void TableMenu() {

    const int xCoord = 5;
    const int yCoord = 4;

    int cursorX = 0;
    int cursorY = 0;

    int stateX = xCoord + 2;
    int stateY = yCoord;

    const int spacingX = 9;
    const int spacingY = 3;

    vector<vector<string>> tableArr = ReadTableLayout();

    const int tableCol = 5;
    const int tableRow = tableArr.size() - 1;

    system("cls");

    while(true) {

        ShowConsoleCursor(false);

        gotoXY(xCoord, yCoord - 2); cout << "Choose A Table";

        gotoXY(stateX, stateY); Color(9); cout << static_cast<char>(25); Color(15);
        gotoXY(stateX, stateY + 2); Color(9); cout << static_cast<char>(24); Color(15);

        gotoXY(xCoord, yCoord + 1);
        for (int i = 0; i < tableArr.size(); i++)
        {
            gotoXY(xCoord, yCoord + 1 + (i * spacingY));
            for (int j = 0; j < tableArr.size(); j++)
            {
                cout << setw(4) << right << tableArr[i][j];
                Spacer(spacingX);
            }
            
            cout << endl << endl << endl;
        }
        
        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) < 0) {
            if (stateY != yCoord + (tableRow * 3)) {
                ClearArrow(stateX, stateY);
                stateY += 3;
                cursorY++;
                continue;
            } else {
                ClearArrow(stateX, stateY);
                stateY = yCoord;
                cursorY = 0;
                continue;
            }
        }
        else if (GetAsyncKeyState(VK_UP) < 0) {
            if (stateY != yCoord) {
                ClearArrow(stateX, stateY);
                stateY -= 3;
                cursorY--;
                continue;
            } else {
                ClearArrow(stateX, stateY);
                stateY = yCoord + (tableRow * 3);
                cursorY = 4;
                continue;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT) < 0) {
            if (stateX != xCoord + 2 + (tableCol * 13)) {
                ClearArrow(stateX, stateY);
                stateX += 13;
                cursorX++;
                continue;
            } else {
                ClearArrow(stateX, stateY);
                stateX = xCoord + 2;
                cursorX = 0;
                continue;
            }
        }
        else if (GetAsyncKeyState(VK_LEFT) < 0) {
            if (stateX > xCoord + 2) {
                ClearArrow(stateX, stateY);
                stateX -= 13;
                cursorX--;
                continue;
            } else {
                ClearArrow(stateX, stateY);
                stateX = xCoord + 2 + (tableCol * 13);
                cursorX = 4;
                continue;
            }
        }
        else if (GetAsyncKeyState(VK_RETURN) < 0) {
            ShowOrderScreen(tableArr[cursorY][cursorX]);
        }
        else if (GetAsyncKeyState(VK_ESCAPE) < 0) {
            system("cls");
            break;
        } 

    }

}

vector<CuisineItem> ReadMenu() {

    ifstream inputFile;
    string itemID, itemName, itemPrice, _token;
    vector<CuisineItem> cuisinesMenu;

    inputFile.open("Cuisines.csv"); // Open file

    if (!inputFile.fail()) {

        int i = 0;

        do {

            getline(inputFile, itemID, ','); // Item ID
            getline(inputFile, itemName, ','); // Item Name
            getline(inputFile, itemPrice, '\n'); // Redundant Token

            cuisinesMenu.push_back(CuisineItem());
            cuisinesMenu[i].cuisineId = itemID;
            cuisinesMenu[i].cuisineName = itemName;
            cuisinesMenu[i].price = stod(itemPrice);

            i++;

        } while (inputFile.good());

        inputFile.close();

    }
    return cuisinesMenu;
}

void ShowMenu() {

    vector<CuisineItem> cuisinesMenu = ReadMenu();

    const int xCoord = 5, yCoord = 4;

    gotoXY(xCoord, yCoord - 2); cout << "Foods" << endl;

    for (int i = 0; i < cuisinesMenu.size() - 1; i++)
    {
        gotoXY(xCoord, yCoord + i); 
        cout << setw(4) << left << cuisinesMenu[i].cuisineId << " "
                << setw(28) << left << cuisinesMenu[i].cuisineName << " "
                << "RM " << fixed << showpoint << setprecision(2) << cuisinesMenu[i].price;
    }

}

void About() {

    // string content = "EOP Sem 1 - 20/21\n\nElyas Asmad\nIrdina Batrisyia\nHafzlan Aideq\nIrdina Izzati\nMuhd Nurzahin\n\n2022";
    // string title = "CSCI 1300 - Final Group Project";

    // MessageBox(NULL, content, title, MB_OK);

}

void ShowOrders() {

    for (int i = 0; i < _mainOrders.size(); i++)
    {
        cout << _mainOrders[i].orderID << " " << _mainOrders[i].tableNumber << endl;
    }

}

int main() {

    InitFont();
    ShowConsoleCursor(false);

    MenuItems mainMenu[3] = {
                            {"Queue A New Order", TableMenu},
                            {"Payment", ShowOrders}, 
                            {"About", About}
                            };

    RenderMenu(3, mainMenu, "Main Menu", false);

    return 0;
}

void ShowOrderScreen(string tableNumber) {

    system("cls");
    const int xCoord = 60, yCoord = 4;
    vector<CuisineItem> menus = ReadMenu();

    ShowConsoleCursor(true);
    string idInput;
    int searchIndex = -1;

    while (true)
    {
        int orderIndex = _mainOrders.size();

        ShowMenu(); // Show Menus
        gotoXY(xCoord, yCoord - 2); cout << "(0 - Back To Table Menu)";
        gotoXY(xCoord, yCoord); cout << "Orders For Table Number: ";
        Color(9); cout << tableNumber; Color(15);

        gotoXY(xCoord, yCoord + 4);
        cout << setw(5) << left << "ID" << setw(35) << left << "Item Name" << setw(6) << left << "Price";

        gotoXY(xCoord, yCoord + 5); cout << "---------------------------------------------------";

        gotoXY(xCoord, yCoord + 2); cout << "Enter item ID: ";
        getline(cin, idInput);

        if (idInput == "0") break;

        // Searching algorithm
        for (int i = 0; i < menus.size(); i++)
        {
            if (idInput == menus[i].cuisineId) {
                searchIndex = i;
            }
        }

        if (searchIndex != -1) {
            _mainOrders.push_back(CustOrders());
            _mainOrders[orderIndex].tableNumber = tableNumber;
            _mainOrders[orderIndex].orderID = menus[searchIndex].cuisineId;
            _mainOrders[orderIndex].orderName = menus[searchIndex].cuisineName;
            _mainOrders[orderIndex].price = menus[searchIndex].price;
        }

    }

    system("cls");

}