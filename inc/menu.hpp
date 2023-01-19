//

#pragma once

#ifndef __menu_hpp_
#define __menu_hpp_

#include <string>

class MenuNode
{
public:
    MenuNode
    (
        std::string,
        MenuNode* t_up   = nullptr,
        MenuNode* t_left = nullptr
    );
    ~MenuNode();

    std::string m_text;
    MenuNode*   m_up    = nullptr;
    MenuNode*   m_left  = nullptr;
    MenuNode*   m_right = nullptr;
    MenuNode*   m_down  = nullptr;
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
