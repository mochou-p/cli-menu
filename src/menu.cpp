//

#include "menu.hpp"

#include <iostream>
#include <conio.h>
#include <cstdlib>

#define SIG_CTRL_C      3

#define KEY_INVALID   (-1)
#define KEY_BACKSPACE   8
#define KEY_ENTER      13
#define KEY_ESC        27
#define KEY_UP         72
#define KEY_DOWN       80

MenuNode::MenuNode(std::string t_text, MenuNode* t_up, MenuNode* t_left)
: m_up   {t_up}
, m_left {t_left}
{
    auto comma = t_text.find(",");
    auto colon = t_text.find(":");
    auto semic = t_text.find(";");

    if (comma == -1llu && colon == -1llu && semic == -1llu)
    {
        m_text.assign(t_text);
        return;
    }

    auto min  = std::min(comma, std::min(colon, semic));
    auto rest = t_text.substr(min + 1);

    m_text.assign(t_text.substr(0, min));

    if (min == comma)
        m_right       = new MenuNode(rest, m_up ? m_up : nullptr, this);
    else if (min == colon)
        m_down        = new MenuNode(rest, this);
    else
        m_up->m_right = new MenuNode(rest);
}

MenuNode::~MenuNode()
{
    delete m_right;
    delete m_down;
}

Menu::Menu(std::string t_str)
{
    m_data = new MenuNode(t_str);
}

Menu::~Menu()
{
    system("cls");
    delete m_data;
}

inline void active_text(std::string t_str)
{
    std::string output = "\x1B[30m\x1B[47m" + t_str;

    for (int i = t_str.length(); i < 20; ++i)
        output += ' ';

    output += "\033[0m";

    std::cout << output << std::endl;
}

int recount(MenuNode* t_p)
{
    auto p      = *t_p;
    auto count  = 0;

    for (; p.m_left;  p = *p.m_left)
        ;

    for (; p.m_right; p = *p.m_right)
        ++count;

    return count;
}

void Menu::render()
{
    auto p      = m_data;
    auto pp     = m_data;
    auto ap     = m_data;

    auto count  = recount(p);

    auto key    =  KEY_INVALID;
    auto active =  0;
    int i;

    do
    {
        switch (key)
        {
        case KEY_INVALID:
            break;
        case SIG_CTRL_C:
            exit(EXIT_FAILURE);
        case KEY_BACKSPACE:
            if (!ap->m_up)
                continue;

            for (pp = ap->m_up; pp->m_left; pp = pp->m_left)
                ;

            count = recount(pp);
            break;
        case KEY_ENTER:
            if (!ap->m_down)
                continue;

            pp    = ap->m_down;
            count = recount(pp);
            break;
        case KEY_UP:
            if (active == 0)
                continue;

            --active;
            break;
        case KEY_DOWN:
            if (active == count)
                continue;

            ++active;
            break;
        default:
            continue;
        }

        system("cls");
        p = pp;

        for (i = 0; p; p = p->m_right)
        {
            if (active == i++)
            {
                active_text(p->m_text.c_str());
                ap = p;
            }
            else
                std::cout << p->m_text.c_str() << std::endl;
        }
    } while ((key = _getch()) != KEY_ESC);
}
