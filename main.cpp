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

        int flag = 0;

        ShowConsoleCursor(false);

        gotoXY(xCoord, yCoord - 2); cout << "Choose A Table";

        gotoXY(stateX, stateY); Color(9); cout << static_cast<char>(25); Color(15);
        gotoXY(stateX, stateY + 2); Color(9); cout << static_cast<char>(24); Color(15);

        gotoXY(xCoord, yCoord + 1);
        for (int i = 0; i < tableArr.size(); i++)
        {
            gotoXY(xCoord, yCoord + 1 + (i * spacingY));
            for (int j = 0; j < tableArr[i].size(); j++)
            {
                flag = 0; // Reset the flag

                // Search for available table
                // 0 - Available
                // 1 - Not available
                for (int k = 0; k < _mainOrders.size(); k++)
                {
                    if (tableArr[i][j] == _mainOrders[k].tableNumber) {
                        flag = 1;
                    }
                }
                // Set color of each table green or red, depending on the availability of the table
                if (flag == 1) 
                    Color(12);
                else 
                    Color(10);

                cout << setw(4) << right << tableArr[i][j];
                Color(15); // Reset the color back to white
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

void PrintReceipt(string tableNum, vector<CuisineItem> orders, double subtotal, double payment)
{
    const string receiptFile = "Receipt.txt";

    ofstream outputFile;

    outputFile.open(receiptFile);

    if (!outputFile.fail()) {

        cout << "\n\t\t\t\tTHANK YOU FOR YOUR ORDER :) GENERATING BILL ";
        for (int a = 1; a < 7; a++) // Change 'a<?' to how many * you want
        {
            sleep(1);
            cout << "...";
        }
        system("cls");

        double change = payment - subtotal;

        outputFile << "\n\t\t\t\t ================================================" << endl;
        outputFile << "\t\t\t\t|        Welcome to Group 2 Restaurant           |" << endl;
        outputFile << "\t\t\t\t ================================================" << endl;
        outputFile << endl;
        outputFile << endl;

        outputFile << "\t\t\t\t------------------------------------------------" << endl;
        outputFile << "\t\t\t\tBill No : C123 | Order : MN123 | Date: 10/1/2022 |" << endl;
        outputFile << endl;
        outputFile << endl;
        outputFile << "\t\t\t\tCashier :  Hafzlan" << endl;
        outputFile << endl;
        outputFile << endl;
        outputFile << "\t\t\t\t------------------------------------------------" << endl;
        outputFile << "\t\t\t\tItem" << "                   " << "Price" << endl;
        outputFile << "\t\t\t\t------------------------------------------------" << endl;
        for (int i = 0; i < orders.size(); i++)
        {
            outputFile << "\t\t\t\t" << setw(23) << left << orders[i].cuisineName
                << "RM " << fixed << showpoint << setprecision(2) << orders[i].price << endl;
            outputFile << "                  " << endl;
        }
        outputFile << "\t\t\t\t================================================" << endl;
        outputFile << "\t\t\t\tTotal                  :RM " << fixed << showpoint << setprecision(2) << subtotal << endl;
        outputFile << "\t\t\t\tAmount tendered        :RM " << fixed << showpoint << setprecision(2) << payment << endl;
        outputFile << "\t\t\t\tChange                 :RM " << fixed << showpoint << setprecision(2) << change << endl;
        outputFile << endl;
        outputFile << "\t\t\t\tThank you for visiting" << endl;
        outputFile << "\t\t\t\tGROUP 2: Yatch Bay Restaurant" << endl;
        outputFile << "\t\t\t\t ";
        outputFile << "\n\t\t\t\t================================================" << endl;

        cout << "\n\t\t\t\tBILL GENERATED SUCCESSFULLY :)" << endl;
        cout << "\t\t\t\tPlease check receipt.txt for your bill!" << endl;
        cout << endl;
        cout << "\t\t\t\t[ANY KEY] - Payment Page" << endl;

    }
    else {
        cout << "Error opening file: " << receiptFile << endl;
        system("pause>nul");
    }

    outputFile.close();

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

void Payment() {

    system("cls");

    string tableNum;
    const int xCoord = 5, yCoord = 4;
    vector<CuisineItem> orders;
    double subtotal = 0.00, payment, change = 0.00;

    while (true) {

        ShowConsoleCursor(true);
        gotoXY(xCoord, yCoord - 2); cout << "Order Summary";

        gotoXY(xCoord, yCoord + 2);
        cout << setw(5) << left << "ID" << setw(35) << left << "Item Name" << setw(6) << left << "Price";
        gotoXY(xCoord, yCoord + 3); cout << "---------------------------------------------------";

        gotoXY(xCoord + 70, yCoord + 16); cout << "0 - Back to Main Menu";

        gotoXY(xCoord, yCoord); 
        cout << "Enter a table number: ";
        cin >> tableNum;

        if (tableNum == "0") {
            system("cls");
            return;
        }

        // Searching algorithm
        int idx = 0;
        for (int i = 0; i < _mainOrders.size(); i++)
        {
            if (tableNum == _mainOrders[i].tableNumber) {
                orders.push_back(CuisineItem());
                orders[idx].cuisineId = _mainOrders[i].orderID;
                orders[idx].cuisineName = _mainOrders[i].orderName;
                orders[idx].price = _mainOrders[i].price;
                subtotal += _mainOrders[i].price;
                idx++;
            }
        }

        for (int i = 0; i < orders.size(); i++)
        {
            gotoXY(xCoord, yCoord + 4 + (i * 2));
            cout << setw(5) << left << orders[i].cuisineId
                    << setw(35) << left << orders[i].cuisineName
                    << "RM " << setw(6) << left << orders[i].price;
        }

        gotoXY(xCoord + 70, yCoord + 8); cout << "Subtotal: RM " << subtotal;
        gotoXY(xCoord + 70, yCoord + 12); cout << "Change: RM " << change;
        gotoXY(xCoord + 70, yCoord + 16); cout << "0 - Back to Main Menu";

        gotoXY(xCoord + 70, yCoord + 10); cout << "Your Payment: RM ";
        cin >> payment;

        ShowConsoleCursor(false);

        if (payment == 0) {
            system("cls"); break;
        }

        change = payment - subtotal;

        // Clear Previous Table Orders
        for (int i = _mainOrders.size(); i >= 0; i--)
        {
            if (_mainOrders[i].tableNumber == tableNum) {
                _mainOrders.erase(_mainOrders.begin() + i);
            }
        }
        
        gotoXY(xCoord + 70, yCoord + 12); cout << "Change: RM " << change; // Re-renders Change

        gotoXY(xCoord + 70, yCoord + 15); cout << "[SPACE] - Print Receipt";
        gotoXY(xCoord + 70, yCoord + 16); cout << "[ESC] - Back to Main Menu";
        gotoXY(xCoord + 70, yCoord + 17); cout << "[ENTER] - Make Another Payment";

        system("pause>nul");

        if (GetAsyncKeyState(VK_ESCAPE) < 0) {
            system("cls"); break;
        }
        else if (GetAsyncKeyState(VK_RETURN) < 0) {
            system("cls"); continue;
        }
        else if (GetAsyncKeyState(VK_SPACE) < 0) {
            system("cls");
            PrintReceipt(tableNum, orders, subtotal, payment);
            system("pause>nul");
            system("cls");
        }

    }

}

void About() {

    LPCSTR content = "EOP Sem 1 - 20/21\n\nElyas Asmad\nIrdina Batrisyia\nHafzlan Aideq\nIrdina Izzati\nMuhd Nurzahin\n\n2022";
    LPCSTR title = "Restaurant Order Management System";

    MessageBox(NULL, content, title, MB_OK);

}

int main() {

    InitFont();
    ShowConsoleCursor(false);

    MenuItems mainMenu[3] = {
                            {"Queue A New Order", TableMenu},
                            {"Payment", Payment}, 
                            {"About", About}
                            };

    RenderMenu(3, mainMenu, "Main Menu", false);

    return 0;
}

void ShowOrderScreen(string tableNumber) {

    system("cls");
    const int xCoord = 60, yCoord = 4;
    vector<CuisineItem> menus = ReadMenu();
    string tempID = "";

    ShowConsoleCursor(true);
    string idInput;
    int searchIndex = -1;

    while (true)
    {
        int orderIndex = _mainOrders.size();
        vector<CuisineItem> tableOrders;
        double subtotal = 0.00;

        int idx = 0;
        for (int i = 0; i < _mainOrders.size(); i++)
        {
            if (_mainOrders[i].tableNumber == tableNumber) {
                tableOrders.push_back(CuisineItem());
                tableOrders[idx].cuisineId = _mainOrders[i].orderID;
                tableOrders[idx].cuisineName = _mainOrders[i].orderName;
                tableOrders[idx].price = _mainOrders[i].price;
                subtotal += _mainOrders[i].price;
                idx++;
            }
        }

        ShowMenu(); // Show Menus
        gotoXY(xCoord, yCoord - 2); cout << "(0 - Back To Table Menu)";
        gotoXY(xCoord, yCoord); cout << "Orders For Table Number: ";
        Color(9); cout << tableNumber; Color(15);

        gotoXY(xCoord + 32, yCoord); cout << "(Subtotal: RM " << subtotal << ")";

        gotoXY(xCoord, yCoord + 4);
        cout << setw(5) << left << "ID" << setw(35) << left << "Item Name" << setw(6) << left << "Price";

        gotoXY(xCoord, yCoord + 5); cout << "---------------------------------------------------";

        for (int i = 0; i < tableOrders.size(); i++)
        {
            gotoXY(xCoord, yCoord + 6 + (i * 2));
            cout << setw(5) << left << tableOrders[i].cuisineId
                 << setw(35) << left << tableOrders[i].cuisineName
                 << "RM " << setw(6) << left << tableOrders[i].price;
        }

        gotoXY(xCoord, yCoord + 2); cout << "Enter item ID: ";
        fflush(stdin);
        getline(cin, idInput);

        gotoXY(xCoord, yCoord + 2); Spacer(18); // Clear

        if (idInput == "0") break; // Back to table menu

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