//

#include "menu.hpp"

#include <iostream>
#include <conio.h>

#define INVALID_KEY (-1)
#define END_SIG       3
#define UP           72
#define DOWN         80

MenuNode::MenuNode(std::string t_str)
{
    std::size_t pos = t_str.find(",");

    m_text = t_str.substr(0, pos);

    if (pos < t_str.length())
        m_bro = new MenuNode(t_str.substr(pos + 1));
}

MenuNode::~MenuNode()
{
    delete m_bro;
}

Menu::Menu(std::string t_str)
{
    m_data = new MenuNode(t_str);
}

Menu::~Menu()
{
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

void Menu::render()
{
    int last   =  0,
        key    =  INVALID_KEY,
        active =  0,
        i;

    for (auto p = m_data; p->m_bro != nullptr; p = p->m_bro)
        ++last;

    do
    {
        switch (key)
        {
        case UP:
            if (active == 0)
                continue;

            --active;
            break;
        case DOWN:
            if (active == last)
                continue;

            ++active;
            break;
        case INVALID_KEY:
            break;
        default:
            continue;
        }

        i = 0;
        system("cls");

        for (auto p = m_data; p != nullptr; p = p->m_bro)
        {
            active == i++
            ? active_text(p->m_text.c_str())
            : (void) (std::cout << p->m_text.c_str() << '\n');
        }
        std::cout << '\r';
    } while ((key = _getch()) != END_SIG);
}
