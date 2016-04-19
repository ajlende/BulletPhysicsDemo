//
//  cube.cpp
//  Glitter
//
//  Created by Alex Lende on 4/17/16.
//
//

#include "cube.hpp"

namespace ComS342 {

    GLfloat Cube::vertices[72] = {
        // Front face
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,

        // Back face
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
        1.0,  1.0, -1.0,
        1.0, -1.0, -1.0,

        // Top face
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
        1.0,  1.0,  1.0,
        1.0,  1.0, -1.0,

        // Bottom face
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,

        // Right face
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        1.0,  1.0,  1.0,
        1.0, -1.0,  1.0,

        // Left face
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0
    };

    GLuint Cube::indices[36] = {  // Note that we start from 0!
        0,  1,  2,      0,  2,  3,    // front
        4,  5,  6,      4,  6,  7,    // back
        8,  9,  10,     8,  10, 11,   // top
        12, 13, 14,     12, 14, 15,   // bottom
        16, 17, 18,     16, 18, 19,   // right
        20, 21, 22,     20, 22, 23    // left
    };

    GLfloat Cube::colors[6][4] = {
        {1.0,  1.0,  1.0,  1.0},    // Front face: white
        {1.0,  0.0,  0.0,  1.0},    // Back face: red
        {0.0,  1.0,  0.0,  1.0},    // Top face: green
        {0.0,  0.0,  1.0,  1.0},    // Bottom face: blue
        {1.0,  1.0,  0.0,  1.0},    // Right face: yellow
        {1.0,  0.0,  1.0,  1.0}     // Left face: purple
    };

    Cube::Cube(GLfloat size) {

    }

    Cube::~Cube() {

    }

    void Cube::draw() {

    }

    void Cube::update() {

    }

}
