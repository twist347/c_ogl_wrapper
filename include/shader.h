#pragma once

#include "glad/glad.h"

typedef struct shader_t shader_t;

shader_t *shader_create(const char *vertex_shader_src, const char *fragment_shader_src);

void shader_destroy(shader_t *shader);

void shader_use(const shader_t *shader);

GLuint shader_get_id(const shader_t *shader);

void shader_set_int(shader_t *shader, const char *name, GLint value);

void shader_set_int_loc(shader_t *shader, GLint loc, GLint value);

void shader_set_vec4(const shader_t* shader, const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

void shader_set_vec4_loс(const shader_t* shader, GLint loc, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
