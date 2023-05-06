#include <iostream>
#include <ncurses.h>   
#include <string>
#include "selectcomponents.hpp"
#include "cmdargs.hpp"


int main(int argc, char* argv[]){

    cmdArgs::startargs(argc, argv);
    std::cin;
    getch();
    selectcomponents::selectTaskType();
}

