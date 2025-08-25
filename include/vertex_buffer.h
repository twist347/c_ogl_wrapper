#pragma once

#include "glad/glad.h"

typedef struct vertex_buffer_t vertex_buffer_t;

vertex_buffer_t *vertex_buffer_create(const void *data, GLsizeiptr size, GLenum usage);

void vertex_buffer_destroy(vertex_buffer_t *buffer);

void vertex_buffer_bind(const vertex_buffer_t *buffer);

void vertex_buffer_unbind(void);

void vertex_buffer_set_data(vertex_buffer_t *buffer, const void *data, GLsizeiptr size);

GLuint vertex_buffer_get_id(const vertex_buffer_t *buffer);
