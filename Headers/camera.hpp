#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h> // Include GL Framework. Note: This pulls in GL.h for us.
#include <glm/glm.hpp>  // Include GL Mathematics library

using glm::vec3;

namespace ComS342 {
    
    // Class to act as a camera that can respond to mouse movements to look around and
    // keypresses to move forward/back/left/right relative to the direction we're facing.
    class Camera {
    private:
        vec3 location;             // Camera location
        vec3 rotation;             // Camera rotation
        vec3 speed;                // Camera speed (currently unused)

        float movementSpeedFactor; // Controls how fast the camera moves
        float pitchSensitivity;    // Controls how sensitive mouse movements affects pitchs (i.e. looking up and down)
        float yawSensitivity;      // Controls how sensitive mouse movements affects yaw (i.e. looking left and right)

        // Window midpoint locations
        int windowMidX;
        int windowMidY;

        // Boolean flags to keep track of which movement keys are being held
        bool holdingForward;
        bool holdingBackward;
        bool holdingLeftStrafe;
        bool holdingRightStrafe;

        // Inline function to convert degrees to radians
        // Note: Although we suggest that the compiler should inline the method, it'll
        // make up its own mind about whether this actually occurs.
        inline float toRads(const float &angleDegs) const {
            return angleDegs * DEGS_TO_RADS;
        }

    public:
        // We'll provide static constants to convert between radians and degrees because
        // the sin() and cos() methods work with radians, but as humans it's more natural
        // to work in degrees.
        static const float DEGS_TO_RADS;
        static const float RADS_TO_DEGS;

        // Constructor
        Camera(vec3 initialPosition, vec3 initialRotation, GLsizei windowWidth, GLsizei windowHeight);

        //  Specify our keyboard handling method
        void handleKeypress(GLint key, GLint action);

        // Keyboard and mouse handlers
        void handleMouseMove(GLFWwindow *window, double mouseX, double mouseY);

        // Method to convert an angle in degress to radians
        //const float toRads(const float &angleInDegrees) const;

        // Method to move the camera based on the current direction
        void move(double deltaTime);

        // To be called each frame
        void update(double deltaTime);

        // --------------------------------- Inline methods ----------------------------------------------

        // Window midpoint setter
        void updateWindowMidpoint(GLsizei windowWidth, GLsizei windowHeight) {
            windowMidX = windowWidth  / 2;
            windowMidY = windowHeight / 2;
        }

        // Pitch and yaw sensitivity getters and setters
        float getPitchSensitivity()            { return pitchSensitivity;  }
        void  setPitchSensitivity(float value) { pitchSensitivity = value; }
        float getYawSensitivity()              { return yawSensitivity;    }
        void  setYawSensitivity(float value)   { yawSensitivity   = value; }

        // Position setters and getters
        void  setLocation(vec3 l)  { location = l;      }
        vec3  getLocation()  const { return location;   }
        float getXLocation() const { return location.x; }
        float getYLocation() const { return location.y; }
        float getZLocation() const { return location.z; }

        // Rotation setters and getters
        void  setRotationDegs(vec3 r)  { rotation = r;      }
        vec3  getRotationDegs()  const { return rotation;   }
        float getXRotationDegs() const { return rotation.x;	}
        float getYRotationDegs() const { return rotation.y; }
        float getZRotationDegs() const { return rotation.z; }

        float getXRotationRads() const { return rotation.x * DEGS_TO_RADS; }
        float getYRotationRads() const { return rotation.y * DEGS_TO_RADS; }
        float getZRotationRads() const { return rotation.z * DEGS_TO_RADS; }
    };
    
}

#endif /* CAMERA_HPP */
