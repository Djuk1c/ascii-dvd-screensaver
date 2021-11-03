#include <ncurses.h>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>

#define HEIGHT  64
#define WIDTH   35

std::vector<std::string> readAscii()
{
    std::vector<std::string> vec;
    std::ifstream input("ascii");
    for(std::string line;getline( input, line );)
    {
        vec.push_back(line);
    }
    return vec;
}

int main()
{
    srand(time(0));
    using namespace std;
    
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    
    std::vector<std::string> logo = readAscii();

    int y = (rand() % 30) + 1;
    int x = (rand() % 60) + 1;
    bool up = false;
    bool right = true;
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(35));

        if (y == 0 || y == WIDTH)
            up = !up;
        if (x == 0 || x == HEIGHT)
            right = !right;

        up ? y-- : y++;
        right ? x-- : x++;

        clear();
        for (int line = 0; line < logo.size(); line++)
        {
            move(y+line, x*2);
            printw(logo[line].c_str());
        }
        refresh();
    }

    endwin();
    return 0;
}
