/**
 * @file initapp.h
 * @author Elyas Asmad
 * @brief Initializes and contains some settings for the main.cpp file
 * @version 0.1
 * @date 2021-12-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef INITAPP_H
#define INITAPP_H

#include <windows.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

// Initialize console handler and cursor coordinates variable
HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

// A function to change the color of the output text
void Color (int color) {
    SetConsoleTextAttribute(wHnd, color);
}

// A function for the cursor to jump to a specific location
// in the console
void gotoXY(int x, int y) {
    cursorPos.X = x;
    cursorPos.Y = y;

    SetConsoleCursorPosition(wHnd, cursorPos);
}

// Function to hide or show the cursor in the console
void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Function to stylize the font in the console
void InitFont() {
    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(font);
    font.nFont = 0;
    font.dwFontSize.X = 0; // Font width
    font.dwFontSize.Y = 24; // Font height
    font.FontFamily = FF_DONTCARE; // Font Family
    font.FontWeight = FW_NORMAL; // Font Weight
    wcscpy(font.FaceName, L"Consolas"); // Font Facename
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
}

// A structure for declaring menu items and their callback function
struct MenuItems {
    std::string choice;
    void (*callbackFn)();
};

void RenderMenu(int menuSize, MenuItems menus[], std::string menuTitle, bool isBack) {

    using std::cout;
    using std::endl;

    // The starting coordinates to print menu items
    const int xCoord = 5;
    const int yCoord = 4;

    int menu_cursor = 0;
    // The menu_state saves the current state for the menu cursor position
    // Initializes to the starting y-coordinate of the menu
    int menu_state = yCoord;

    while(true) {

        // Print menu cursor
        gotoXY(2, menu_state); Color(9); cout << "\x1a"; Color(15);

        // Print menu title
        gotoXY(xCoord, yCoord - 2); cout << menuTitle << endl;

        for (int i = 0; i < menuSize; i++)
        {
            gotoXY(xCoord, yCoord + i);
            cout << menus[i].choice << endl;
        }

        gotoXY(xCoord, 15); cout << "\x18  - Up" << endl;
        gotoXY(xCoord, 16); cout << "\x19  - Down" << endl;
        gotoXY(xCoord, 17); cout << "[ENTER] - Select" << endl;
        gotoXY(xCoord, 18); cout << "[ESC] - Back" << endl;

        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) < 0 && menu_state != yCoord + menuSize) {
            gotoXY(xCoord - 3, menu_state); cout << "  ";
            menu_state++;
            menu_cursor++;
            continue;
        }
        else if (GetAsyncKeyState(VK_UP) < 0 && menu_state != yCoord) {
            gotoXY(xCoord - 3, menu_state); cout << "  ";
            menu_state--;
            menu_cursor--;
            continue;
        }

    }

}

#endif