#include <ncurses.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <locale.h>

namespace selectcomponents {
    #define WIDTH 30
    #define HEIGHT 10 

    char *choices[] = { 
        "Create Task",
        "Create Subtask",
        "Check Off",
        "Exit",
    };

    int n_choices = sizeof(choices) / sizeof(char *);
    int highlight = 1;
    int choice = 0;

    void print_menu(WINDOW *menu_win, int highlight);
    void writeToFile();

    int selectTaskType()
    {   
        WINDOW *menu_win;
        int c;
        std::string cheese;
        setlocale(LC_CTYPE, "en_US.UTF-8");
        initscr();
        clear();
        noecho();
        cbreak();    /* Line buffering disabled. pass on everything */
        int startx = (80 - WIDTH) / 2;
        int starty = (24 - HEIGHT) / 2;
            
        menu_win = newwin(HEIGHT, WIDTH, starty, startx);
        keypad(menu_win, TRUE);
        mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
        refresh();
        print_menu(menu_win, highlight);
        while(1){

            while(1){   
                c = wgetch(menu_win);
                switch(c){   
                    case KEY_UP:
                        if(highlight == 1)
                            highlight = n_choices;
                        else
                            --highlight;
                        break;
                    case KEY_DOWN:
                        if(highlight == n_choices)
                            highlight = 1;
                        else 
                            ++highlight;
                        break;
                    case 10:
                        choice = highlight;
                        break;
                    default:
                        mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                        refresh();
                        break;
                }

                print_menu(menu_win, highlight);
                if(choice != 0){ // Enter choice elif
                    break;
                }
            }
            if(choice[choices - 1] == "Create Task"){
                char taskname[100];
                std::string home_dir = getenv("HOME");
                std::ofstream ofs(home_dir+"/.config/alltodo", std::ios_base::app); // Open taskfile
                mvprintw(24, 0, "What will this task be called? eg. Read Documentation on examplelib: ");
                echo();
                getstr(taskname);
                ofs << "node:" << taskname << "\n"; // Write to taskfile
                printw("\U00002714"); // Print the Unicode character
                getch();
            }
        }
        getch();
        clrtoeol();
        refresh();
        return 0;
    }
    

    void print_menu(WINDOW *menu_win, int highlight)
    {
        int x, y, i;    

        x = 2;
        y = 2;
        box(menu_win, 0, 0);

        for(i = 0; i < n_choices; ++i)
        {   
            if(highlight == i + 1) /* Highlight the present choice */
            {   
                wattron(menu_win, A_REVERSE); 
                mvwprintw(menu_win, y, x, "%s", choices[i]);
                wattroff(menu_win, A_REVERSE);
            }
            else
                mvwprintw(menu_win, y, x, "%s", choices[i]);

            ++y;
            }
    wrefresh(menu_win);
    }
}
