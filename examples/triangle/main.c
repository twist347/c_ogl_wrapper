#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_ogl_wrapper.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_TITLE "triangle example"

const char *vertex_src =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "}\n";

const char *fragment_src =
        "#version 330 core\n"
        "out vec4 frag_color;\n"
        "void main() {\n"
        "    frag_color1 = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

int main() {
    int exit_code = EXIT_SUCCESS;
    window_t *window = NULL;
    shader_t *shader = NULL;
    vertex_buffer_t *vbo = NULL;
    vertex_array_t *vao = NULL;

    window = window_create(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, 4, 6);
    if (!window) {
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    if (!init_glad()) {
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    info_print();

    const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f // top
    };

    vbo = vertex_buffer_create(vertices, sizeof(vertices), GL_STATIC_DRAW);
    if (!vbo) {
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    vao = vertex_array_create();
    if (!vao) {
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    vertex_array_add_buffer(vao, vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);

    shader = shader_create(vertex_src, fragment_src);
    if (!shader) {
        exit_code = EXIT_FAILURE;
        goto cleanup;
    }

    window_set_clear_color(1.f, 1.f, 1.f, 1.f);

    while (!window_should_close(window)) {
        window_process_input(window);

        window_clear();

        shader_use(shader);
        vertex_array_bind(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vertex_array_unbind();

        window_swap_buffers(window);
        window_poll_events();
    }

cleanup:
    if (vao) {
        vertex_array_destroy(vao);
    }

    if (vbo) {
        vertex_buffer_destroy(vbo);
    }

    if (shader) {
        shader_destroy(shader);
    }

    if (window) {
        window_destroy(window);
    }

    return exit_code;
}
