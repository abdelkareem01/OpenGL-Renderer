#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

//#include "Texture.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestSquare.h"

int main(void)
{
    GLFWwindow* window;

    WindowSize::SetDimensions(1920, 1080);

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
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		//Texture texture("res/textures/testTexture.png");
		//texture.Bind();   //texture slot 0
		//shader.SetUniform1i("u_Texture", 0);  //0 here refers to the texture slot, which in this case is 0

        Renderer renderer;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::StyleColorsDark();

        test::TestClearColor testColor;
        test::TestSquare testSquare(va, shader);

		glm::vec3 SquareOne(100, 100, 0);
		glm::vec3 SquareTwo(300, 100, 0);
         /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();

			testColor.OnUpdate(0.0f);
            testSquare.OnUpdate(0.0f);
			testColor.OnRender();
            testSquare.OnRender();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
            
			testColor.OnImGuiRender();
			testSquare.OnImGuiRender("SquareOne", SquareOne);
            renderer.Draw(va, testSquare.GetIb(), shader);
            testSquare.OnImGuiRender("SquareTwo", SquareTwo);
            renderer.Draw(va, testSquare.GetIb(), shader);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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