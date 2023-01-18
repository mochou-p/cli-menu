//

#include "menu.hpp"

#include <iostream>

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

void Menu::render()
{
    for (MenuNode* p = m_data; p != nullptr; p = p->m_bro)
        std::cout << p->m_text.c_str() << std::endl;
}
