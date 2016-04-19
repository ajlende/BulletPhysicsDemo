#include "utils.hpp"

// Function to check if OpenGL is having issues - pass it a unique string of some kind to track down where in the code it's moaning
void checkGLError(string errorLocation) {
    GLenum gle = glGetError();

    if (gle != GL_NO_ERROR) {
        // If we've provided a location where we were called from then spit it out
        if (errorLocation != "") {
            cout << "GL Error discovered from location " << errorLocation << ": ";
        } else {
            cout << "OpenGL error status: ";
        }

        // Get a human friendly error from the GL_ENUM returned to us
        switch (gle) {
            case GL_INVALID_ENUM:
                cout << "Invalid enum." << endl;
                break;
            case GL_INVALID_VALUE:
                cout << "Invalid value." << endl;
                break;
            case GL_INVALID_OPERATION:
                cout << "Invalid Operation." << endl;
                break;
            case GL_STACK_OVERFLOW:
                cout << "Stack overflow." << endl;
                break;
            case GL_STACK_UNDERFLOW:
                cout << "Stack underflow." << endl;
                break;
            case GL_OUT_OF_MEMORY:
                cout << "Out of memory." <<  endl;
                break;
            default:
                cout << "Unknown error! Enum code is: " << gle << endl;
                break;
        } // End of switch

    } // End of if error detected
}

// Function to display details about our OpenGL rendering context
void displayWindowProperties(GLFWwindow *window) {
    cout << "----- GLFW Window Properties -----" << endl;

    // Get profile version
    int openGLProfileVersion = glfwGetWindowAttrib(window, GLFW_OPENGL_PROFILE);

    // Get a friendly string version of the profile
    string profileString = "";
    switch (openGLProfileVersion) {
        case 0:
            profileString = "Default (0)";
            break;

        case GLFW_OPENGL_CORE_PROFILE:
            profileString = "Core";
            break;

        case GLFW_OPENGL_COMPAT_PROFILE:
            profileString = "Compatability";
            break;

        default:
            profileString = &"Unknown profile enumeration: " [ openGLProfileVersion];
            break;
    }

    // Get the context major and minor version
    int openGLMajorVersion = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int openGLMinorVersion = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);

    // Get whether we're in forward compatible mode
    int forwardCompatibleMode  = glfwGetWindowAttrib(window, GLFW_OPENGL_FORWARD_COMPAT);
    string forwardCompatibleModeString = forwardCompatibleMode ? "Yes" : "No";

    // Display our human readable profile/context/forward-compatability details
    cout << "OpenGL profile: " << profileString << " (Context: " << openGLMajorVersion << "." << openGLMinorVersion << ") -  Forward compatible mode: " << forwardCompatibleModeString << endl;

    // Check video refresh
    // Note: This will be 0 as default rather than a specific value like 60, 75, 90, 120 etc.
    int refresh = glfwGetWindowAttrib(window, GLFW_REFRESH_RATE);
    cout << "Refresh rate: " << refresh << " Hz" << endl;

    // Check buffer bit depths
    // Note: 0 means current desktop default
    int redBits        = glfwGetWindowAttrib(window, GLFW_RED_BITS);
    int greenBits      = glfwGetWindowAttrib(window, GLFW_GREEN_BITS);
    int blueBits       = glfwGetWindowAttrib(window, GLFW_BLUE_BITS);
    int alphaBits      = glfwGetWindowAttrib(window, GLFW_ALPHA_BITS);
    int depthBits      = glfwGetWindowAttrib(window, GLFW_DEPTH_BITS);
    int stencilBits    = glfwGetWindowAttrib(window, GLFW_STENCIL_BITS);
    int accumRedBits   = glfwGetWindowAttrib(window, GLFW_ACCUM_RED_BITS);
    int accumGreenBits = glfwGetWindowAttrib(window, GLFW_ACCUM_BLUE_BITS);
    int accumBlueBits  = glfwGetWindowAttrib(window, GLFW_ACCUM_GREEN_BITS);
    int accumAlphaBits = glfwGetWindowAttrib(window, GLFW_ACCUM_ALPHA_BITS);

    cout << "RGB buffer bits                : " << redBits << "\t" << greenBits << "\t" << blueBits << std::endl;
    cout << "Alpha buffer bits              : " << alphaBits << std::endl;
    cout << "Depth buffer bits              : " << depthBits << std::endl;
    cout << "Stencil buffer bits            : " << stencilBits << std::endl;
    cout << "Accumulation buffer bits (RGBA): " << accumRedBits << "\t" << accumGreenBits << "\t" << accumBlueBits << "\t" << accumAlphaBits << endl;

    // Check anti-aliasing
    // Note: Although this can come back as zero, anti-aliasing samples asked for via window hints can actually still be applied
    int antiAliasingSamples = glfwGetWindowAttrib(window, GLFW_SAMPLES);
    cout << "Anti-Aliasing Samples: " << antiAliasingSamples << endl;
    cout << "----------------------------------" << endl << endl;
}

// Function to make the user press enter and then exit the program - called when we hit an unrecoverable error
// so that debug output can be displayed in the console before we kill the application.
void getKeypressThenExit() {
    cout << "Press <Enter> to continue... " << endl;
    cin.get();
    exit(-1);
}