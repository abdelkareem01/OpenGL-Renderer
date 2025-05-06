#include "TestSquare.h"

namespace test
{
	TestSquare::TestSquare(VertexArray& va, Shader& shader, Renderer& renderer, int nTranslations)
		:m_Vb(m_Positions, 4 * 4 * sizeof(float)), m_Ib(m_Indices, 6), m_Va(va), m_Shader(shader), m_Renderer(renderer) //4 floats per vertex including texture edges
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

		for(int i = 0; i < nTranslations; i++)
		m_Translations.push_back(std::make_pair("Translation" + i, glm::vec3(100, 100, 0)));
		
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

	void TestSquare::OnImGuiRender()
	{
		
		glm::mat4 projMat = glm::ortho(0.0f, WindowSize::Width, 0.0f, WindowSize::Height, -1.0f, 1.0f); // -X, X, -Y, Y, -Z, Z ==> aspect ratio = X:Y
		glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		
		for (auto& translation : m_Translations)
		{
			glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translation.second);
			ImGui::SliderFloat3(translation.first.c_str(), &translation.second.x, 0.0f, WindowSize::Width);
			glm::mat4 mvp = projMat * viewMat * modelMat;
			m_Shader.SetUniformMat4f("u_MVP", mvp);
			m_Renderer.Draw(m_Va, m_Ib, m_Shader);
		}
	}

	void TestSquare::OnDelete()
	{
		m_Va.UnBind();
		m_Vb.Unbind();
		m_Ib.Unbind();
		m_Shader.Unbind();
	}

}

