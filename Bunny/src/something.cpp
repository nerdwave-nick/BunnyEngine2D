#include <iostream>

// GLAD
#include <glad/gl.h>

// GLFW (include after glad)
#include <GLFW/glfw3.h>

#include "bunny/core/key-codes.h"
#include "bunny/core/mouse-buttons.h"
#include "bunny/events/key-event.h"
#include "bunny/events/mouse-event.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void button_callback(GLFWwindow* window, int button, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


// The MAIN function, from here we start the application and run the game loop
int main() {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, button_callback);

  // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cout << "Failed to initialize OpenGL context" << std::endl;
    return -1;
  }

  // Successfully loaded OpenGL
  std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

  // Define the viewport dimensions
  glViewport(0, 0, WIDTH, HEIGHT);

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();

    // Render
    // Clear the colorbuffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }

  // Terminates GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}
bool doKeyCodeCheck(Bunny::KeyCode code) {
  return code == Bunny::KeyCode::Escape;
}
bool doButtonCodeCheck(Bunny::MouseButton code) {
  return code == Bunny::MouseButton::Left;
}
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  auto event = Bunny::KeyTypedEvent(key);
  std::cout << event << std::endl;
  if (doKeyCodeCheck(event.GetKeyCode()) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
// Is called whenever a key is pressed/released via GLFW
void button_callback(GLFWwindow* window, int button, int action, int mode) {
  auto event = Bunny::MouseButtonPressedEvent(button);
  std::cout << event << std::endl;
  if (doButtonCodeCheck(event.GetMouseButton()) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}