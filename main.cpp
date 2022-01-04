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
#include "initapp.h"

using namespace std;

int main() {

    int menuItem = 0, x = 3;

    while(true) {
        
        Color(9); gotoXY(5, x); cout << ">"; Color(15);
        gotoXY(7, 3); cout << "Take An Order" << endl;
        gotoXY(7, 4); cout << "Payment" << endl;
        gotoXY(7, 5); cout << "Exit" << endl;
        
        Color(9); 
        switch (x)
        {
            case 3:
                gotoXY(7, 3); cout << "Take An Order" << endl;
                break;
            case 4:
                gotoXY(7, 4); cout << "Payment" << endl;
                break;
            case 5:
                gotoXY(7, 5); cout << "Exit" << endl;
                break;
            default:
                break;
        }
        Color(15);

        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) && x != 5) {
            gotoXY(5, x); cout << " ";
            x++;
            menuItem++;
            continue;
        }

        if (GetAsyncKeyState(VK_UP) && x != 3) {
            gotoXY(5, x); cout << " ";
            x--;
            menuItem--;
            continue;
        }

        if (GetAsyncKeyState(VK_RETURN)) {
            switch (menuItem)
            {
                case 0: gotoXY(7, 12); cout << "Item 1" << endl; break;
                case 1: gotoXY(7, 12); cout << "Item 2" << endl; break;
                case 2: system("pause"); return 0;
                default:
                    break;
            }
        }

    }

    return 0;
}