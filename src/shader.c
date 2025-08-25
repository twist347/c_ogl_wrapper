#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

#define LOG_LEN 1024

struct shader_t {
    GLuint id;
};

static GLuint shader_compile(GLenum type, const char *src);

static GLboolean check_compile_errors(GLuint shader, const char *type);

static GLboolean check_link_errors(GLuint program);

shader_t *shader_create(const char *vertex_shader_src, const char *fragment_shader_src) {
    if (!vertex_shader_src || !fragment_shader_src) {
        fprintf(stderr, "[ERROR] null shader sources.\n");
        return NULL;
    }

    shader_t *shader = malloc(sizeof(shader_t));
    if (!shader) {
        fprintf(stderr, "[ERROR] failed to allocate shader_t.\n");
        return NULL;
    }

    const GLuint vertex_shader = shader_compile(GL_VERTEX_SHADER, vertex_shader_src);
    if (!vertex_shader) {
        free(shader);
        return NULL;
    }

    const GLuint fragment_shader = shader_compile(GL_FRAGMENT_SHADER, fragment_shader_src);
    if (!fragment_shader) {
        glDeleteShader(vertex_shader);
        free(shader);
        return NULL;
    }

    shader->id = glCreateProgram();
    glAttachShader(shader->id, vertex_shader);
    glAttachShader(shader->id, fragment_shader);
    glLinkProgram(shader->id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (!check_link_errors(shader->id)) {
        glDeleteProgram(shader->id);
        free(shader);
        return NULL;
    }

    return shader;
}

void shader_destroy(shader_t *shader) {
    if (shader) {
        if (shader->id) {
            glDeleteProgram(shader->id);
        }
        free(shader);
    }
}

GLuint shader_compile(GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    const char *type_name = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
    if (!check_compile_errors(shader, type_name)) {
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void shader_use(shader_t *shader) {
    if (shader && shader->id) {
        glUseProgram(shader->id);
    }
}

GLuint shader_get_id(const shader_t *shader) {
    return shader ? shader->id : 0;
}

void shader_set_vec4(shader_t *shader, const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    if (shader && shader->id && name) {
        const GLint location = glGetUniformLocation(shader->id, name);
        if (location != -1) {
            glUniform4f(location, x, y, z, w);
        }
    }
}

static GLboolean check_compile_errors(GLuint shader, const char *type) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char info_log[LOG_LEN];
        glGetShaderInfoLog(shader, LOG_LEN, NULL, info_log);
        fprintf(stderr, "[SHADER] %s compilation failed:\n%s\n", type, info_log);
        return GL_FALSE;
    }

    return GL_TRUE;
}

static GLboolean check_link_errors(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char info_log[LOG_LEN];
        glGetProgramInfoLog(program, LOG_LEN, NULL, info_log);
        fprintf(stderr, "[SHADER] Program linking failed:\n%s\n", info_log);
        return GL_FALSE;
    }

    return GL_TRUE;
}
