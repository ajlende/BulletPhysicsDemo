//
//  cube.hpp
//  Glitter
//
//  Created by Alex Lende on 4/17/16.
//
//

#ifndef CUBE_HPP
#define CUBE_HPP
#pragma once

#include <stdio.h>
#include <glad/glad.h>

namespace ComS342 {
    
    class Cube {
    private:
        static GLfloat vertices[72];
        static GLuint indices[36];
        static GLfloat colors[6][4];

    public:
        Cube(GLfloat size);
        ~Cube();
        void draw();
        void update();
    };
    
}

#endif /* CUBE_HPP */
