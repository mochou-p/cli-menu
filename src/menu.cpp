//

#include "menu.hpp"

MenuNode::MenuNode(std::string _str)
{
    std::size_t pos = _str.find(",");

    text = _str.substr(0, pos);

    if (pos < _str.length())
        next = new MenuNode(_str.substr(pos + 1));
}

MenuNode::~MenuNode()
{
    delete next;
}

Menu::Menu(std::string _str)
{
    data = new MenuNode(_str);
}

Menu::~Menu()
{
    delete data;
}

void Menu::render()
{
    for (MenuNode* p = data; p != nullptr; p = p->next)
        std::cout << p->text.c_str() << std::endl;
}
