#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "slot/reel_strip.h"
#include "slot/spin_evaluation.h"

// const char* vertexShaderSource = "#version 330 core\n"
// "layout (location = 0) in vec3 aPos;\n"
// "void main()\n"
// "{\n"
// "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "}\0";

// const char* fragmetnShaderSource = "#version 330 core\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
// "}\n\0";
// int main(void)
// {   
//     // initialise glfw
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window;

//     GLfloat vertices[] = {
//         -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
//         0.5f, 0.5f * float(sqrt(3)) / 3, 0.0f,
//         0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,

//     };

//     /* Initialize the library */
//     if (!glfwInit())
//         return -1;

//     /* Create a windowed mode window and its OpenGL context */
//     window = glfwCreateWindow(640, 480, "Slots", NULL, NULL);
//     if (!window)
//     {
//         glfwTerminate();
//         return -1;
//     }

//     /* Make the window's context current */
//     glfwMakeContextCurrent(window);

//     glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

//     /* Loop until the user closes the window */
//     while (!glfwWindowShouldClose(window))
//     {   

//         /* Poll for and process events */
//         glfwPollEvents();

//         /* Render here */
//         glClear(GL_COLOR_BUFFER_BIT);

//         /* Swap front and back buffers */
//         glfwSwapBuffers(window);

//     }

//     glfwTerminate();
//     return 0;
// }

int main() {
    ReelStrip strip = ReelStrip::fromConfig({{"Lemon", "Lemon", "Lemon"}});

    // 2. Create a reel
    Reel firstStrip(strip);
    Reel secondStrip(strip);
    Reel thirdStrip(strip);

    // 3. FIX THE SEED (This is your "Unit Test" mode)
    // no rng implemented yet

    // 4. Spin
    std::vector<std::array<Symbol, 3>> grid;
    grid.push_back(firstStrip.visibleSymbols());
    grid.push_back(secondStrip.visibleSymbols());
    grid.push_back(thirdStrip.visibleSymbols());
    
    // 5. Evaluate
    SpinEvaluator evaluator;
    int win = evaluator.evaluate(grid);
    
    // 6. Print out win
    std::cout << "Total payout based on the spin" << std:: endl << win << std::endl;

    return 0;
}