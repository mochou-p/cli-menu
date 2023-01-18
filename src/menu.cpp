//

#include "menu.hpp"

#include <iostream>
#include <conio.h>
#include <cstdlib>

#define INVALID_KEY (-1)
#define SIG_CTRLC     3
#define KEY_ESC      27
#define UP           72
#define DOWN         80

MenuNode::MenuNode(std::string t_text, MenuNode* t_dad)
: m_dad(t_dad)
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
        m_bro = new MenuNode(rest, m_dad ? m_dad : nullptr);
    else if (min == colon)
        m_son = new MenuNode(rest, this);
    else if (min == semic)
        m_dad->m_bro = new MenuNode(rest);
}

MenuNode::~MenuNode()
{
    delete m_bro;
    delete m_son;
}

Menu::Menu(std::string t_str)
{
    m_data = new MenuNode(t_str);
}

Menu::~Menu()
{
    delete m_data;
    system("cls");
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

    for (auto p = m_data; p->m_bro; p = p->m_bro)
        ++last;

    do
    {
        switch (key)
        {
        case SIG_CTRLC:
            exit(EXIT_FAILURE);
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

        for (auto p = m_data; p; p = p->m_bro)
        {
            active == i++
            ? active_text(p->m_text.c_str())
            : (void) (std::cout << p->m_text.c_str() << '\n');
        }
        std::cout << '\r';
    } while ((key = _getch()) != KEY_ESC);
}
