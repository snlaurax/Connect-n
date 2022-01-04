//
//  main.cpp
//  Project3
//
//  Created by Laura Lu on 2021-05-08.
//  Copyright © 2021 Laura Lu. All rights reserved.
//
#include "provided.h"
#include <iostream>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
    ~KeepWindowOpenUntilDismissed()
    {
        DWORD pids[1];
        if (GetConsoleProcessList(pids, 1) == 1)
        {
            std::cout << "Press any key to close this window . . . ";
            _getch();
        }
    }
} keepWindowOpenUntilDismissed;
#endif
#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
    SmartPlayer bp1("Bart");
    HumanPlayer bp2("Homer");
    Game g(3, 3, 3, &bp1, &bp2);
    g.play();
}

int main()
{
    doGameTests();
    cout << "Passed all tests" << endl;
}


