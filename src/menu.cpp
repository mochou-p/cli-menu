//

#include "menu.hpp"

#include <iostream>
#include <conio.h>
#include <cstdlib>

#define SIG_CTRL_C       3

#define KEY_FIRST_PASS (-1)
#define KEY_BACKSPACE    8
#define KEY_ENTER       13
#define KEY_ESC         27
#define KEY_UP          72
#define KEY_DOWN        80

MenuNode::MenuNode(std::string t_text, MenuNode* t_up, MenuNode* t_left)
: m_up   {t_up}
, m_left {t_left}
{
    std::size_t len = t_text.length();
    std::size_t min = std::min(
        t_text.find(','), std::min(
            t_text.find(':'), std::min(
                t_text.find(';'), len
            )
        )
    );

    if (min == len)
    {
        m_text.assign(t_text);
        return;
    }

    m_text.assign(t_text.substr(0, min));
    std::string rest =   t_text.substr(min + 1);

    switch (t_text.at(min))
    {
    case ',':
        m_right = new MenuNode(rest, m_up ? m_up : nullptr, this);
        break;
    case ':':
        m_down  = new MenuNode(rest, this);
        break;
    case ';':
        {
        MenuNode* p = this;

        for (; rest.at(0) == ';'; p = p->m_up)
            rest = rest.substr(1);

        p          = p->m_up;
        p->m_right = new MenuNode(rest, p->m_up ? p->m_up : nullptr, p);
        break;
        }
    default:
        break;
    }
}

void MenuNode::destroy()
{
    if (m_right)
    {
        m_right->destroy();
        delete m_right;
    }

    if (m_down)
    {
        m_down->destroy();
        delete m_down;
    }
}

Menu::Menu(std::string t_str)
{
    m_data = new MenuNode(t_str);
}

Menu::~Menu()
{
    system("cls");

    m_data->destroy();
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

int recount(MenuNode t_p)
{
    int count = 0;

    for (; t_p.m_left;  t_p = *t_p.m_left)
        ;

    for (; t_p.m_right; t_p = *t_p.m_right)
        ++count;

    return count;
}

void Menu::render()
{
    MenuNode* p  = m_data;
    MenuNode* pp = m_data;
    MenuNode* ap = m_data;

    int count    = recount(*p);
    int key      = KEY_FIRST_PASS;
    int active   = 0;
    int i;

    do
    {
        switch (key)
        {
        case KEY_FIRST_PASS:
            break;
        case SIG_CTRL_C:
            exit(EXIT_FAILURE);
        case KEY_BACKSPACE:
            if (!ap->m_up)
                continue;

            for (pp = ap->m_up; pp->m_left; pp = pp->m_left)
                ;

            count  = recount(*pp);
            active > count && (active = count);
            break;
        case KEY_ENTER:
            if (!ap->m_down)
                continue;

            pp     = ap->m_down;
            count  = recount(*pp);
            active > count && (active = count);
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
                ap = p;
                active_text(p->m_text.c_str());
            }
            else
                std::cout << p->m_text.c_str() << std::endl;
        }
    } while ((key = _getch()) != KEY_ESC);
}
