#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Function to set up ImGui and initialize the context with GLFW and OpenGL
void setup_imgui(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  ImGui::StyleColorsDark();

  // Initialize ImGui for GLFW and OpenGL
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

// Function to clean up ImGui when the app closes
void cleanup_imgui() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    return -1;
  }

  // Create a windowed mode window
  GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Click Counter App", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  // Initialize ImGui
  setup_imgui(window);

  // Click counter variable
  int click_count = 0;

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui UI code
    ImGui::Begin("Click Counter");

    // Display the number of times the button has been clicked
    ImGui::Text("Button clicked %d times", click_count);

    // Button logic: increment click_count when the button is clicked
    if (ImGui::Button("Click Me!")) {
      click_count++;
    }

    ImGui::End();

    // Rendering
    ImGui::Render();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // Clean up
  cleanup_imgui();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
