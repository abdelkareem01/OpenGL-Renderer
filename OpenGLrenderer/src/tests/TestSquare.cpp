#include "TestSquare.h"

namespace test
{
	TestSquare::TestSquare(VertexArray& va, Shader& shader)
		:m_Vb(m_Positions, 4 * 4 * sizeof(float)), m_Ib(m_Indices, 6), m_Shader(shader) //4 floats per vertex including texture edges
	{
		VertexBufferLayout layout;
		layout.Push<float>(2);   //number of values per position
		layout.Push<float>(2);   //edges for the textures
		va.AddBuffer(m_Vb, layout);
		
		shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		va.UnBind();
		m_Vb.Unbind();
		m_Ib.Unbind();
		shader.Unbind();

	}

	TestSquare::~TestSquare()
	{

	}

	void TestSquare::OnUpdate(float deltaTime)
	{

	}

	void TestSquare::OnRender()
	{

	}

	void TestSquare::OnImGuiRender(const char* label, glm::vec3& translation)
	{
		glm::mat4 projMat = glm::ortho(0.0f, WindowSize::Width, 0.0f, WindowSize::Height, -1.0f, 1.0f); // -X, X, -Y, Y, -Z, Z ==> aspect ratio = X:Y
		glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translation);

		glm::mat4 mvp = projMat * viewMat * modelMat;

		ImGui::SliderFloat3(label, &translation.x, 0.0f, WindowSize::Width);

		m_Shader.SetUniformMat4f("u_MVP", mvp);
	}

}

