#include <ncurses.h>   
#include <boost/filesystem.hpp>
#include <iostream>
#include <cstdlib>

using namespace boost::filesystem;
using namespace std;
path ConfigDir (getenv("HOME"));

namespace cmdArgs{
    int startargs(int argc, char* argv[]){
        if (argc < 2){
            if (exists(ConfigDir/".config/alltodo/tasks")){
                return 0;
            }
            else{
                std::cout << "Making Data File...\n";
                create_directory(ConfigDir/"/.config/alltodo");  
                boost::filesystem::ofstream(ConfigDir/"/.config/alltodo/tasks");
                std::cout << "File Created. Press any key to continue";
                getch();
                return -1;
            }
        }
        if(argc == 2){
            if(argv[1] == "-removetasks"){
                char yn;
                std::cout << "Remove AllToDo's tasks [Y/n]";
                std::cin >> yn;
                if (yn == 'y'){
                    remove_all(ConfigDir / "/.config/alltodo/tasks");
                }
            }
        }
    }
}
