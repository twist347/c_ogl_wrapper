#pragma once

#include "GLFW/glfw3.h"

typedef struct window_t window_t;

window_t *window_create(int width, int height, const char *title);

void window_destroy(window_t *window);

GLFWwindow *window_get_handle(const window_t *window);

int window_should_close(const window_t *window);

void window_swap_buffers(window_t *window);

void window_poll_events(void);

void window_set_clear_color(float r, float g, float b, float a);

void window_clear(void);

int window_get_width(const window_t *window);

int window_get_height(const window_t *window);
