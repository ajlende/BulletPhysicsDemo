/***
 Project: GLFW3 Basecode
 Version: 0.5
 Author : r3dux
 Date   : 21/1/2014
 Purpose: Basecode to setup an OpenGL context with FPS camera controls and draw some grids.
 ***/

#define STB_IMAGE_IMPLEMENTATION

// Local Headers
#include "glitter.hpp"
#include "camera.hpp"
#include "grid.hpp"
#include "utils.hpp"
#include "physics.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace ComS342;

// Save ourselves some typing...
using std::cout;
using std::endl;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

// ---------- Global variables ----------

// Window and projection settings
GLsizei windowWidth       = 800;
GLsizei windowHeight      = 600;
float vertFieldOfViewDegs = 45.0f;
float nearClipDistance    = 1.0f;
float farClipDistance     = 2000.0f;

// Misc
int  frameCount = 0;              // How many frames we've drawn
int  frameRate  = 60;             // Target frame rate -we'll assume a 60Hz refresh for now
bool leftMouseButtonDown = false; // We'll only look around when the left mouse button is down
double currentTime = 0;
double lastTime = 0;
double deltaTime = 0;

// Matricies
mat4 projectionMatrix; // The projection matrix is used to perform the 3D to 2D conversion i.e. it maps from eye space to clip space.
mat4 viewMatrix;       // The view matrix maps the world coordinate system into eye cordinates (i.e. world space to eye space)
mat4 modelMatrix;      // The model matrix maps an object's local coordinate system into world coordinates (i.e. model space to world space)

// Pointers to two grids
Grid *upperGrid, *lowerGrid;

// Camera. Params: location, rotation (degrees), window width & height
Camera camera(vec3(0.0f), vec3(0.0f), windowWidth, windowHeight);

// Create a physics world with gravity of 9.8 m/s^2 (default is 10.0)
Physics physics(9.8);

// Callback function to resize the window and set the viewport to the correct size
void resizeWindow(GLFWwindow *window, GLsizei newWidth, GLsizei newHeight) {
    // Keep track of the new width and height of the window
    windowWidth  = float(newWidth);
    windowHeight = float(newHeight);

    // Recalculate the projection matrix
    projectionMatrix = glm::perspective(vertFieldOfViewDegs, GLfloat(windowWidth) / GLfloat(windowHeight), nearClipDistance, farClipDistance);

    // Viewport is the entire window
    glViewport(0, 0, windowWidth, windowHeight);

    // Update the midpoint location in the camera class because it uses these values, too
    camera.updateWindowMidpoint(windowWidth, windowHeight);
}

// Callback function to handle keypresses
void handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // User hit ESC? Set the window to close
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    } else {
        camera.handleKeypress(key, action);
    }
}

// Callback function to handle mouse movement
void handleMouseMove(GLFWwindow *window, double mouseX, double mouseY) {
    // We'll only look around when the left mouse button is down
    if (leftMouseButtonDown) {
        camera.handleMouseMove(window, mouseX, mouseY);
    }
}

// Callback function to handle mouse button presses
void handleMouseButton(GLFWwindow *window, int button, int action, int mods) {
    // Button press involves left mouse button?
    if (button == GLFW_MOUSE_BUTTON_1) {
        if (action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            leftMouseButtonDown = true;
        } else {
            // Action must be GLFW_RELEASE
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            leftMouseButtonDown = false;
        }
    }
}

// Function to set up our OpenGL rendering context
void initGL(GLFWwindow *window) {
    // ---------- Initialise glad ----------

    glfwMakeContextCurrent(window);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // ---------- Setup OpenGL Options ----------

    glViewport( 0, 0, GLsizei(windowWidth), GLsizei(windowHeight) ); // Viewport is entire window
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                            // Clear to black with full alpha
    glEnable(GL_DEPTH_TEST);                                         // Enable depth testing
    glDepthFunc(GL_LEQUAL);                                          // Specify depth testing function
    glClearDepth(1.0);                                               // Clear the full extent of the depth buffer (default)
    glEnable(GL_CULL_FACE);                                          // Enable face culling
    glCullFace(GL_BACK);                                             // Cull back faces of polygons
    glFrontFace(GL_CCW);                                             // Counter-clockwise winding indicates a forward facing polygon (default)

    // ---------- Setup GLFW Callback Functions ----------

    glfwSetWindowSizeCallback(window, resizeWindow);                 // Register window resize functiom
    glfwSetKeyCallback(window, handleKeypress);                      // Register keyboard handler function
    glfwSetCursorPosCallback(window, handleMouseMove);               // Register mouse movement handler function
    glfwSetMouseButtonCallback(window, handleMouseButton);           // Register mouse button handler function

    // ---------- Setup GLFW Options ----------

    glfwSwapInterval(1);                                             // Swap buffers every frame (i.e. lock to VSync)
    glfwSetInputMode(window, GLFW_CURSOR_DISABLED, GL_FALSE);        // Do not hide the mouse cursor
    glfwSetWindowPos(window, 200, 200);                              // Push the top-left of the window out from the top-left corner of the screen
    glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);     // Move the mouse cursor to the centre of the window

    // checkGLError("InitGL");
}

// Function to perform our drawing
void drawFrame(double deltaTime) {
    // Move the camera
    camera.move(deltaTime);

    // ---------- Matrix operations ----------

    // Reset our View matrix
    viewMatrix = mat4(1.0f);

    // Perform camera rotation
    viewMatrix = glm::rotate(viewMatrix, camera.getXRotationRads(), X_AXIS);
    viewMatrix = glm::rotate(viewMatrix, camera.getYRotationRads(), Y_AXIS);

    // Translate to our camera position
    viewMatrix = glm::translate(viewMatrix, -camera.getLocation() );

    // Create an identity matrix for the model matrix
    modelMatrix = mat4(1.0f);

    // ---------- Drawing operations ----------

    mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    upperGrid->draw(mvpMatrix);
    lowerGrid->draw(mvpMatrix);
}

int main() {
    // ----- Initialiise GLFW, specify window hints & open a context -----

    // IMPORTANT: glfwInit resets all window hints, so we must call glfwInit FIRST and THEN we supply window hints!
    if (!glfwInit()) {
        cout << "glfwInit failed!" << endl;
        exit(-1);
    }

    // Further reading on GLFW window hints: http://www.glfw.org/docs/latest/window.html#window_hints

    // If we want to use a a core profile (i.e. no legacy fixed-pipeline functionality) or if we want to
    // use forward compatible mode (i.e. only non-deprecated features of a given OpenGL version available)
    // then we MUST specify the MAJOR.MINOR context version we want to use FIRST!
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Ask for 4x Anti-Aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a window. Params: width, height, title, *monitor, *share
    GLFWwindow* window = glfwCreateWindow(GLsizei(windowWidth), GLsizei(windowHeight), "GLFW3 Basecode | Use WSAD to move & LMB to look around - Nov 2014 | r3dux.org ", NULL, NULL);
    if (!window) {
        cout << "Failed to create window - bad context MAJOR.MINOR version?" << endl;
        getKeypressThenExit();
    }

    // Make the current OpenGL context active
    glfwMakeContextCurrent(window);

    // Display the details of our OpenGL window
    displayWindowProperties(window);

    // -------------- Set up our OpenGL settings ---------------

    initGL(window);

    // ---------- Set up our grids ----------

    // Instantiate our grids. Params: Width, Depth, level (i.e. location of y-axis), number of grid lines
    upperGrid = new Grid(1000.0f, 1000.0f,  200.0f, 20);
    lowerGrid = new Grid(1000.0f, 1000.0f, -200.0f, 20);

    // ---------- Set up our matricies ----------

    // Specify the projection matrix
    projectionMatrix = glm::perspective(vertFieldOfViewDegs, GLfloat(windowWidth) / GLfloat(windowHeight), nearClipDistance, farClipDistance);

    // Reset the view and model and view matrices to identity
    viewMatrix  = mat4(1.0f);
    modelMatrix = mat4(1.0f);

    // ---------- Main loop ----------

    while (!glfwWindowShouldClose(window)) {
        // Update the time
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        
        // Update framecount (mostly for debug)
        frameCount++;
        
        // ---------- Update section ----------
        
        camera.update(deltaTime);
        physics.update(deltaTime);
        
        // ---------- Draw section ----------

        // Clear the screen and depth buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Draw our frame with the time delta
        drawFrame(currentTime - lastTime);

        // Swap the back and front buffers to display the frame we just rendered
        glfwSwapBuffers(window);

        // Poll for input
        glfwPollEvents();
        
        // Update to calculate the delta
        lastTime = currentTime;
    }

    // Check the final error state
    // NOTE: This MUST be called while we still have a valid rendering context (i.e. before we call glfwTerminate() )
    checkGLError("End");

    // Destroy the window and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
