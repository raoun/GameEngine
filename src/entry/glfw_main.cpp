#include "GLFW/glfw3.h"

void increment(float &f)
{
	f += 0.01f;
	if (f > 1.0f)
		f = -1.0f;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    float x1 = -0.5, y1 = -0.5, x2 = 0., y2 = 0.5, x3 = 0.5, y3 = -0.5;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		increment(x1);
		increment(y1);
		increment(x2);
		increment(y2);
		increment(x3);
		increment(y3);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
        glVertex2f(x3, y3);
		glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}