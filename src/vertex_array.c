#include "vertex_array.h"

#include <stdio.h>
#include <stdlib.h>

struct vertex_array_t {
    GLuint id;
};

vertex_array_t *vertex_array_create(void) {
    vertex_array_t *vao = malloc(sizeof(vertex_array_t));
    if (!vao) {
        fprintf(stderr, "[VAO] Failed to allocate memory\n");
        return NULL;
    }

    glGenVertexArrays(1, &vao->id);
    return vao;
}

void vertex_array_destroy(vertex_array_t *vao) {
    if (vao) {
        if (vao->id) {
            glDeleteVertexArrays(1, &vao->id);
        }
        free(vao);
    }
}

void vertex_array_bind(const vertex_array_t *vao) {
    if (vao && vao->id) {
        glBindVertexArray(vao->id);
    }
}

void vertex_array_unbind(void) {
    glBindVertexArray(0);
}

void vertex_array_add_buffer(vertex_array_t *vao, vertex_buffer_t *vbo,
                             GLuint index, GLint size, GLenum type,
                             GLboolean normalized, GLsizei stride, const void *pointer) {
    if (!vao || !vao->id || !vbo || !vertex_buffer_get_id(vbo)) {
        fprintf(stderr, "[VAO] Invalid parameters for add_buffer\n");
        return;
    }

    vertex_array_bind(vao);
    vertex_buffer_bind(vbo);

    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);

    vertex_buffer_unbind();
    vertex_array_unbind();
}

GLuint vertex_array_get_id(const vertex_array_t *vao) {
    return vao ? vao->id : 0;
}
