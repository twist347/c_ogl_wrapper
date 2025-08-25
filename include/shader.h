#pragma once

#include "glad/glad.h"

typedef struct shader_t shader_t;

shader_t *shader_create(const char *vertex_shader_src, const char *fragment_shader_src);

void shader_destroy(shader_t *shader);

void shader_use(shader_t *shader);

GLuint shader_get_id(const shader_t *shader);

void shader_set_vec4(shader_t* shader, const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
