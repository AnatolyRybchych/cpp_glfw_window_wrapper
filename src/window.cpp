#include "window.hpp"

#define ARG_DECLS(...) __VA_ARGS__
#define CLASS_ARGS(...) __VA_ARGS__

#define REDIRECT_TO_WINDOW_CLASS(event, declare_args, arg_names)\
static void on_window_##event(GLFWwindow *glfw_wnd declare_args){\
    for(window *wnd:window::windows){\
        if(wnd->get_glfw() == glfw_wnd){\
            wnd->prepare_event();\
            wnd->on_##event(arg_names);\
            break;\
        }\
    }\
}

static void on_window_move(GLFWwindow *glfw_wnd, int x, int y);
static void on_window_key(GLFWwindow *glfw_wnd, int key, int scan_code, int action, int modes);
static void on_window_char(GLFWwindow *glfw_wnd, unsigned int ch);
static void on_window_drop(GLFWwindow *glfw_wnd, int count, const char *paths[]);
static void on_window_scroll(GLFWwindow *glfw_wnd, double x, double y);
static void on_window_char_mods(GLFWwindow *glfw_wnd, unsigned int codepoint, int mods);
static void on_window_mouse_move(GLFWwindow *glfw_wnd, double x, double y);
static void on_window_resize(GLFWwindow *glfw_wnd, int width, int heigth);
static void on_window_focus(GLFWwindow *glfw_wnd, int has_focus);
static void on_window_mouse_enter(GLFWwindow *glfw_wnd, int is_enter);
static void on_window_mouse_button(GLFWwindow *glfw_wnd, int button, int status, int arg3);
static void on_window_close(GLFWwindow *glfw_wnd);
static void on_window_minimize(GLFWwindow *glfw_wnd, int is_minimized);
static void on_window_redraw(GLFWwindow *glfw_wnd);
static void on_window_maximize(GLFWwindow *glfw_wnd, int is_maximized);
static void on_window_frame_buffer_size(GLFWwindow *glfw_wnd, int width, int heigth);
static void on_window_scale(GLFWwindow *glfw_wnd, float x, float y);


std::vector<window*> window::windows;
bool window::is_init = false;

void window::init(){
    if(is_init == false){
        if(glfwInit() == false)
            throw std::runtime_error("ERROR: cannot init glfw\n");
        is_init = true;
    }
}

bool window::has_windows() noexcept{
    return windows.empty() == false;
}


glm::ivec2 window::get_size() const noexcept{
    glm::ivec2 res;
    glfwGetWindowSize(glfw, &res.x, &res.y);
    return res;
}

glm::ivec2 window::get_pos() const noexcept{
    glm::ivec2 res;
    glfwGetWindowPos(glfw, &res.x, &res.y);
    return res;
}

GLFWwindow *window::get_glfw() const noexcept{
    return glfw;
}

void window::wait_events(double seconds) const noexcept{
    glfwWaitEventsTimeout(seconds);
}

void window::wait_events() const noexcept{
    glfwWaitEvents();
}

void window::poll_events() const noexcept{
    glfwPollEvents();
}

bool window::is_should_be_closed() const noexcept{
    return glfwWindowShouldClose(glfw);
}

void window::set_size(glm::ivec2 size) noexcept{
    glfwSetWindowSize(glfw, size.x, size.y);
}

void window::set_pos(glm::ivec2 pos) noexcept{
    glfwSetWindowPos(glfw, pos.x, pos.y);
}

float window::get_opacity() const noexcept{
    return glfwGetWindowOpacity(glfw);
}

void window::set_opacity(float opacity) noexcept{
    glfwSetWindowOpacity(glfw, opacity);
}

void window::prepare_event() noexcept{}
void window::on_move(glm::ivec2 pos) noexcept{}
void window::on_key(int key, int scan_code, int action, int modes) noexcept{}
void window::on_char(unsigned int ch) noexcept{}
void window::on_drop(int count, const char *paths[]) noexcept{}
void window::on_scroll(glm::dvec2 direction) noexcept{}
void window::on_char_mods(unsigned int codepoint, int mods) noexcept{}
void window::on_mouse_move(glm::dvec2 pos) noexcept{}
void window::on_resize(glm::ivec2 size) noexcept{}
void window::on_focus(bool has_focus) noexcept{}
void window::on_mouse_enter(bool is_enter) noexcept{}
void window::on_mouse_button(int button, int status, int arg3) noexcept{}
void window::on_close() noexcept{}
void window::on_minimize(bool is_minimized) noexcept{}
void window::on_redraw() noexcept{}
void window::on_maximize(bool is_maximized) noexcept{}
void window::on_frame_buffer_size(glm::ivec2 size) noexcept{}
void window::on_scale(glm::vec2 scale) noexcept{}

window::window(glm::ivec2 size, std::string title){
    if(is_init == false)
        throw std::logic_error("ERROR: required call window::init() before create window\n");
    glfw = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if(glfw == nullptr)
        throw std::runtime_error("ERROR: cannot create glfw window\n");


    glfwSetKeyCallback(glfw, on_window_key);
    glfwSetCharCallback(glfw, on_window_char);
    glfwSetDropCallback(glfw, on_window_drop);
    glfwSetScrollCallback(glfw, on_window_scroll);
    glfwSetCharModsCallback(glfw, on_window_char_mods);
    glfwSetCursorPosCallback(glfw, on_window_mouse_move);
    glfwSetWindowPosCallback(glfw, on_window_move);
    glfwSetWindowSizeCallback(glfw, on_window_resize);
    glfwSetWindowFocusCallback(glfw, on_window_focus);
    glfwSetCursorEnterCallback(glfw, on_window_mouse_enter);
    glfwSetMouseButtonCallback(glfw, on_window_mouse_button);
    glfwSetWindowCloseCallback(glfw, on_window_close);
    glfwSetWindowIconifyCallback(glfw, on_window_minimize);
    glfwSetWindowRefreshCallback(glfw, on_window_redraw);
    glfwSetWindowMaximizeCallback(glfw, on_window_maximize);
    glfwSetFramebufferSizeCallback(glfw, on_window_frame_buffer_size);
    glfwSetWindowContentScaleCallback(glfw, on_window_scale);

    windows.push_back(this);
}

window::~window() noexcept{
    windows.erase(std::find(windows.begin(), windows.end(), this));
}

REDIRECT_TO_WINDOW_CLASS(move, ARG_DECLS(,int x, int y), CLASS_ARGS(glm::ivec2(x, y)));
REDIRECT_TO_WINDOW_CLASS(key, ARG_DECLS(,int key, int scan_code, int action, int modes), CLASS_ARGS(key, scan_code, action, modes));
REDIRECT_TO_WINDOW_CLASS(char, ARG_DECLS(,unsigned int ch), CLASS_ARGS(ch));
REDIRECT_TO_WINDOW_CLASS(drop, ARG_DECLS(,int count, const char *paths[]), CLASS_ARGS(count, paths));
REDIRECT_TO_WINDOW_CLASS(scroll, ARG_DECLS(,double x, double y), CLASS_ARGS(glm::dvec2(x, y)));
REDIRECT_TO_WINDOW_CLASS(char_mods, ARG_DECLS(,unsigned int codepoint, int mods), CLASS_ARGS(codepoint, mods));
REDIRECT_TO_WINDOW_CLASS(mouse_move, ARG_DECLS(,double x, double y), CLASS_ARGS(glm::dvec2(x, y)));
REDIRECT_TO_WINDOW_CLASS(resize, ARG_DECLS(,int width, int heigth), CLASS_ARGS(glm::ivec2(width, heigth)));
REDIRECT_TO_WINDOW_CLASS(focus, ARG_DECLS(,int has_focus), CLASS_ARGS(has_focus));
REDIRECT_TO_WINDOW_CLASS(mouse_enter, ARG_DECLS(,int is_enter), CLASS_ARGS(is_enter));
REDIRECT_TO_WINDOW_CLASS(mouse_button, ARG_DECLS(,int button, int status, int arg3), CLASS_ARGS(button, status, arg3));
REDIRECT_TO_WINDOW_CLASS(close, ARG_DECLS(), CLASS_ARGS());
REDIRECT_TO_WINDOW_CLASS(minimize, ARG_DECLS(,int is_minimized), CLASS_ARGS(is_minimized));
REDIRECT_TO_WINDOW_CLASS(redraw, ARG_DECLS(), CLASS_ARGS());
REDIRECT_TO_WINDOW_CLASS(maximize, ARG_DECLS(,int is_maximized), CLASS_ARGS(is_maximized));
REDIRECT_TO_WINDOW_CLASS(frame_buffer_size, ARG_DECLS(,int width, int heigth), CLASS_ARGS(glm::ivec2(width, heigth)));
REDIRECT_TO_WINDOW_CLASS(scale, ARG_DECLS(,float x, float y), CLASS_ARGS(glm::vec2(x, y)));