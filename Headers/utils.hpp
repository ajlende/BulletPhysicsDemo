#ifndef UTILS_HPP
#define UTILS_HPP
#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

namespace ComS342 {
    // Define degree/radian conversion constants
    const float DEGS_TO_RADS = 3.141592654f / 180.0f;
    const float RADS_TO_DEGS = 180.0f / 3.141592654f;

    // Define our cardinal axes
    const glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);
    const glm::vec3 RIGHT   = X_AXIS; // Positive x-axis points directly to the right
    const glm::vec3 UP      = Y_AXIS; // Positive y-axis points directly up
    const glm::vec3 FORWARD = Z_AXIS; // Positive z-axis points directly out of the screen

    // Function to display the OpenGL error status
    void checkGLError(string errorLocation = "");

    // Function to display the OpenGL rendering context details
    void displayWindowProperties(GLFWwindow *window);

    // Function to get a keypress and exit - this allows us to see debug output in Code::Blocks
    // which we would miss if we called exit directly.
    void getKeypressThenExit();

    // Templated function convert a string into a float
    template<typename T>
    float stringToNumber(const std::string &numberAsString) {
        float number;
        std::stringstream stream(numberAsString);
        stream >> number;
        if (stream.fail()) {
            cerr << "Failed to convert the following to a number: " << numberAsString << endl;
            return 0.0f;
        }
        return number;
    }

    // Templated function to convert various types of data to string
    template<class T>
    std::string toString(const T& t) {
        std::ostringstream stream;
        stream << t;
        return stream.str();
    }
}

#endif /* UTILS_HPP */
