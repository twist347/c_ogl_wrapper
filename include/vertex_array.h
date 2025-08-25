#pragma once

#include "vertex_buffer.h"

typedef struct vertex_array_t vertex_array_t;

vertex_array_t *vertex_array_create(void);

void vertex_array_destroy(vertex_array_t *vao);

void vertex_array_bind(const vertex_array_t *vao);

void vertex_array_unbind(void);

void vertex_array_add_buffer(vertex_array_t *vao, vertex_buffer_t *vbo,
                             GLuint index, GLint size, GLenum type,
                             GLboolean normalized, GLsizei stride, const void *pointer);

GLuint vertex_array_get_id(const vertex_array_t *vao);
