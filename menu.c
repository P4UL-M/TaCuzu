#include <stdio.h>
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
void print_menu2(WINDOW *menu_win, int choice);

int main()
{
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak(); /* Line buffering disabled. pass on everything */
    startx = 0;
    starty = 0;

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    print_menu(menu_win, highlight);
    while (1)
    {
        clear();
        c = wgetch(menu_win);
        if (choice == 0)
        {
            switch (c)
            {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                refresh();
                break;
            }
        }
        if (choice != 0) /* User did a choice come out of the infinite loop */
        {
            if (choice == 5)
                break;
            print_menu2(menu_win, choice);
        }
        else
            print_menu(menu_win, highlight);
    }
    clrtoeol();
    refresh();
    endwin();
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    wclear(menu_win);
    // box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1) /* High light the present choice */
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

void print_menu2(WINDOW *menu_win, int choice)
{
    int x, y, i;

    x = 2;
    y = 2;
    wclear(menu_win);
    // box(menu_win, 0, 0);
    mvwprintw(menu_win, y, x, "you choose %d", choice);
    wrefresh(menu_win);
}