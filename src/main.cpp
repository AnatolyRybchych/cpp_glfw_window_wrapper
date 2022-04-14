#include <iostream>

#include "window.hpp"


int main(int argc, char const *argv[])
{

    window::init();
    window wnd(glm::ivec2(800, 600), "Window");


    while (wnd.is_should_be_closed() == false){
        wnd.wait_events();
    }
    return 0;
}
