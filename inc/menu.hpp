//

#pragma once

#ifndef __menu_hpp_
#define __menu_hpp_

#include <string>

class MenuNode
{
public:
    MenuNode(std::string, MenuNode* t_dad = nullptr);
    ~MenuNode();

    std::string m_text;
    MenuNode*   m_dad = nullptr;
    MenuNode*   m_bro = nullptr;
    MenuNode*   m_son = nullptr;
};

class Menu
{
public:
    Menu(std::string);
    ~Menu();

    void render();

private:
    MenuNode* m_data = nullptr;
};

#endif  // __menu_hpp_
