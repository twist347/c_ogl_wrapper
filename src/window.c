#include "window.h"

#include <stdio.h>
#include <stdlib.h>

struct window_t {
    GLFWwindow *handle;
};

static void framebuffer_size_callback(GLFWwindow *handle, int width, int height) {
    (void) handle;
    glViewport(0, 0, width, height);
}

window_t *window_create(int width, int height, const char *title, int major_ver, int minor_ver) {
    if (!glfwInit()) {
        fprintf(stderr, "[ERROR::WINDOW] failed to initialize GLFW\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!handle) {
        fprintf(stderr, "[ERROR::WINDOW] failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(handle);

    glfwSwapInterval(1); // VSync

    int fbw = 0, fbh = 0;
    glfwGetFramebufferSize(handle, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);
    glfwSetFramebufferSizeCallback(handle, framebuffer_size_callback);

    window_t *window = malloc(sizeof(window_t));
    if (!window) {
        fprintf(stderr, "[ERROR::WINDOW] failed to allocate memory for window\n");
        glfwDestroyWindow(handle);
        glfwTerminate();
        return NULL;
    }

    window->handle = handle;

    return window;
}

void window_destroy(window_t *window) {
    if (!window) {
        return;
    }

    if (window->handle) {
        glfwDestroyWindow(window->handle);
        window->handle = NULL;
    }
    free(window);

    glfwTerminate();
}

GLFWwindow *window_get_handle(const window_t *window) {
    return window ? window->handle : NULL;
}

int window_should_close(const window_t *window) {
    if (!window || !window->handle) {
        return 1;
    }
    return glfwWindowShouldClose(window->handle);
}

void window_process_input(const window_t *window) {
    if (!window || !window->handle) {
        return;
    }
    if (glfwGetKey(window_get_handle(window), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_get_handle(window), GLFW_TRUE);
    }
}

void window_swap_buffers(window_t *window) {
    if (window && window->handle) {
        glfwSwapBuffers(window->handle);
    }
}

void window_poll_events(void) {
    glfwPollEvents();
}

void window_set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void window_clear(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

int window_get_width(const window_t *window) {
    if (!window || !window->handle) {
        return 0;
    }

    int width, height;
    glfwGetWindowSize(window->handle, &width, &height);
    return width;
}

int window_get_height(const window_t *window) {
    if (!window || !window->handle) {
        return 0;
    }

    int width, height;
    glfwGetWindowSize(window->handle, &width, &height);
    return height;
}
