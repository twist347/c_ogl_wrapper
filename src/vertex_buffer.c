#include "vertex_buffer.h"

#include <stdio.h>
#include <stdlib.h>

struct vertex_buffer_t {
    GLuint id;
    GLsizeiptr size;
    GLenum usage;
};

vertex_buffer_t *vertex_buffer_create(const void *data, GLsizeiptr size, GLenum usage) {
    if (size <= 0) {
        fprintf(stderr, "[VBO] Invalid buffer size: %ld\n", size);
        return NULL;
    }

    vertex_buffer_t *buffer = malloc(sizeof(vertex_buffer_t));
    if (!buffer) {
        fprintf(stderr, "[VBO] Failed to allocate memory\n");
        return NULL;
    }

    glGenBuffers(1, &buffer->id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    buffer->size = size;
    buffer->usage = usage;

    return buffer;
}

void vertex_buffer_destroy(vertex_buffer_t *buffer) {
    if (buffer) {
        if (buffer->id) {
            glDeleteBuffers(1, &buffer->id);
        }
        free(buffer);
    }
}

void vertex_buffer_bind(const vertex_buffer_t *buffer) {
    if (buffer && buffer->id) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
    }
}

void vertex_buffer_unbind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertex_buffer_set_data(vertex_buffer_t *buffer, const void *data, GLsizeiptr size) {
    if (buffer && buffer->id && data && size > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
        glBufferData(GL_ARRAY_BUFFER, size, data, buffer->usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        buffer->size = size;
    }
}

GLuint vertex_buffer_get_id(const vertex_buffer_t *buffer) {
    return buffer ? buffer->id : 0;
}
