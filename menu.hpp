//

#pragma once

#ifndef __menu_hpp_
#define __menu_hpp_

#include <iostream>
#include <string>

class MenuNode
{
public:

    MenuNode(std::string);
    ~MenuNode();

    std::string text;
    MenuNode*   next = nullptr;
};

class Menu
{
public:
    Menu(std::string);
    ~Menu();

    void render();

private:
    MenuNode* data = nullptr;
};

#endif  // __menu_hpp_
