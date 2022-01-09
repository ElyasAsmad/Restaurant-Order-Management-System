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
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "initapp.h"
#include "utils.h"

using namespace std;

void ShowOrderScreen(int);

void Test() {
    cout << "Hello World" << endl;
}

void ClearArrow(int stateX, int stateY) {
    gotoXY(stateX, stateY); cout << "  ";
    gotoXY(stateX, stateY + 2); cout << "  ";
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

    system("cls");

    gotoXY(xCoord, yCoord - 2); cout << "Choose A Table";

    while(true) {

        gotoXY(stateX, stateY); Color(9); cout << static_cast<char>(25); Color(15);
        gotoXY(stateX, stateY + 2); Color(9); cout << static_cast<char>(24); Color(15);

        gotoXY(xCoord, yCoord + 1);
        for (int i = 0; i < 5; i++)
        {
            gotoXY(xCoord, yCoord + 1 + (i * spacingY));
            for (int j = 0; j < 5; j++)
            {
                cout << setw(4) << right << ((i + 1) * 100) + j + 1;
                Spacer(spacingX); // Spacer (utils.h)
            }
            cout << endl << endl << endl;
        }
        
        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) < 0) {
            if (stateY != yCoord + (4 * 3)) {
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
                stateY = yCoord + (4 * 3);
                cursorY = 4;
                continue;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT) < 0) {
            if (stateX != xCoord + 2 + (4 * 13)) {
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
                stateX = xCoord + 2 + (4 * 13);
                cursorX = 4;
                continue;
            }
        }
        else if (GetAsyncKeyState(VK_RETURN) < 0) {
            ShowOrderScreen(10);
        }
        else if (GetAsyncKeyState(VK_ESCAPE) < 0) {
            system("cls");
            break;
        } 

    }

}

void ShowMenu() {

    // Define the structure
    struct CuisineItem {
        string cuisineId;
        string cuisineName;
        double price;
    };

    ifstream inputFile;
    string itemID, itemName, itemPrice, _token;
    vector<CuisineItem> cuisinesMenu;
    const int xCoord = 5, yCoord = 4;

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

        gotoXY(xCoord, yCoord - 2); cout << "Foods" << endl;

        for (int i = 0; i < cuisinesMenu.size(); i++)
        {
            gotoXY(xCoord, yCoord + i); cout << cuisinesMenu[i].cuisineId << " - " << cuisinesMenu[i].cuisineName << " - " << cuisinesMenu[i].price;
        }
    }

}

void About() {

    // string content = "EOP Sem 1 - 20/21\n\nElyas Asmad\nIrdina Batrisyia\nHafzlan Aideq\nIrdina Izzati\nMuhd Nurzahin\n\n2022";
    // string title = "CSCI 1300 - Final Group Project";

    // MessageBox(NULL, content, title, MB_OK);

}

int main() {

    InitFont();
    ShowConsoleCursor(false);

    MenuItems mainMenu[3] = {
                            {"Queue A New Order", TableMenu},
                            {"Payment", About}, 
                            {"About", About}
                            };

    RenderMenu(3, mainMenu, "Main Menu", false);

    return 0;
}

void ShowOrderScreen(int tableNumber) {

    system("cls");

    ShowMenu(); // Show Menus

    const int xCoord = 60, yCoord = 4;

    gotoXY(xCoord, yCoord); cout << "Orders For Table Number ----- " << tableNumber << " -----";

    system("pause>nul");

}