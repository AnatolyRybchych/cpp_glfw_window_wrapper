#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "glm/vec2.hpp"



class window
{
private:
    static bool is_init;

    GLFWwindow *glfw;
public: 
    static std::vector<window*> windows;
    static bool has_windows() noexcept;
    static void init();

    glm::ivec2 get_size() const noexcept;
    glm::ivec2 get_pos() const noexcept;
    GLFWwindow *get_glfw() const noexcept; 
    float get_opacity() const noexcept;

    void set_opacity(float opacity) noexcept;
    void set_size(glm::ivec2 size) noexcept;
    void set_pos(glm::ivec2 pos) noexcept;

    void wait_events() const noexcept;
    void wait_events(double seconds) const noexcept;
    void poll_events() const noexcept;

    bool is_should_be_closed() const noexcept;

    virtual void prepare_event() noexcept;
    virtual void on_move(glm::ivec2 pos) noexcept;
    virtual void on_key(int key, int scan_code, int action, int modes) noexcept;
    virtual void on_char(unsigned int ch) noexcept;
    virtual void on_drop(int count, const char *paths[]) noexcept;
    virtual void on_scroll(glm::dvec2 direction) noexcept;
    virtual void on_char_mods(unsigned int codepoint, int mods) noexcept;
    virtual void on_mouse_move(glm::dvec2 pos) noexcept;
    virtual void on_resize(glm::ivec2 size) noexcept;
    virtual void on_focus(bool has_focus) noexcept;
    virtual void on_mouse_enter(bool is_enter) noexcept;
    virtual void on_mouse_button(int button, int status, int arg3) noexcept;
    virtual void on_close() noexcept;
    virtual void on_minimize(bool is_minimized) noexcept;
    virtual void on_redraw() noexcept;
    virtual void on_maximize(bool is_maximized) noexcept;
    virtual void on_frame_buffer_size(glm::ivec2 size) noexcept;
    virtual void on_scale(glm::vec2 scale) noexcept;

    window(glm::ivec2 size, std::string title);
    virtual ~window() noexcept;
};
