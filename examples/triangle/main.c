#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "window.h"

int main() {
    window_t *window = window_create(1920, 1080, "triangle example");
    if (!window) {
        return EXIT_FAILURE;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        window_destroy(window);
        return EXIT_FAILURE;
    }

    window_set_clear_color(1.f, 1.f, 1.f, 1.f);

    while (!window_should_close(window)) {
        window_clear(window);

        window_swap_buffers(window);
        window_poll_events();
    }

    window_destroy(window);
    return EXIT_SUCCESS;
}
