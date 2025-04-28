#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

struct WindowSize
{
	static float Width;
    static float Height;

    inline static void SetDimensions(float W, float H)
    {
        Width = W;
        Height = H;
    }
};

float WindowSize::Width;
float WindowSize::Height;

int main(void)
{
    
    GLFWwindow* window;

    WindowSize::SetDimensions(960, 540);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow((int)(WindowSize::Width), (int)(WindowSize::Height), "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "error" << std::endl;

    std::cout << glGetString(GL_VERSION) << '\n';

    {
        //values 0.5 and -0.5 are vertex related, and values from 0.0 to 1.0f are texture related
        float positions[] = {   //Define unique vertices of the square of whatever shape
        100.0f, 100.0f, 0.0f, 0.0f, // 0
        100.0f, 200.0f, 0.0f, 1.0f, // 1
        200.0f, 100.0f, 1.0f, 0.0f, // 2
        200.0f, 200.0f, 1.0f, 1.0f, // 3
        };

        unsigned int indices[]{ //set the indexes of those vertices in order, reusing already defined ones to make the shape
            0,1,2,
            2,1,3,
        };
        
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));  //4 floats per vertex including texture edges
        VertexBufferLayout layout;
        layout.Push<float>(2);   //number of values per position
        layout.Push<float>(2);   //edges for the textures
        va.AddBuffer(vb, layout);
        
        IndexBuffer ib(indices, 6);
        
		glm::mat4 projMat = glm::ortho(0.0f, WindowSize::Width, 0.0f, WindowSize::Height, -1.0f, 1.0f); // -X, X, -Y, Y, -Z, Z ==> aspect ratio = X:Y
        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(200,0,0));
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));

        //projection matrix ==> scale of view
        //model matrix      ==> transform of the objects
        //view matrix       ==> transform of the camera pointing to objects
        
        //multiplication of these matrices results in our Model View Projection Matrix(MVP):
        glm::mat4 mvp = projMat * viewMat * modelMat;

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);

        Texture texture("res/textures/testTexture.png");
        texture.Bind();   //texture slot 0
        shader.SetUniform1i("u_Texture", 0);  //0 here refers to the texture slot, which in this case is 0

        va.UnBind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::StyleColorsClassic();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.2f, 1.0f, 1.0f);
            
            renderer.Draw(va, ib, shader);
            
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            {
				ImGui::SliderFloat("float", &increment, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}