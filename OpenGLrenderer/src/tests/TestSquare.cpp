#include "TestSquare.h"

namespace test
{
	TestSquare::TestSquare(int nTranslations)
		:m_ProjMat(glm::ortho(0.0f, WindowSize::Width, 0.0f, WindowSize::Height, -1.0f, 1.0f)),
		m_ViewMat(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		m_Va = std::make_unique<VertexArray>();
		m_Vb = std::make_unique<VertexBuffer>(m_Positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);   //number of values per position
		m_Va->AddBuffer(*m_Vb, layout);
		m_Ib = std::make_unique<IndexBuffer>(m_Indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.3f, 0.4f, 0.8f, 1.0f);
		m_Shader->SetUniform1i("u_UseTexture", 0);
		for (int i = 0; i < nTranslations; i++)
		{
			m_Translations.push_back(std::make_pair("Translation: " + std::to_string(i + 1), glm::vec3(100 * (i + 1), 100 * (i + 1), 0)));
		}


	}

	TestSquare::~TestSquare()
	{

	}

	void TestSquare::OnUpdate(float deltaTime)
	{

	}

	void TestSquare::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_Renderer = std::make_unique<Renderer>();

		for (auto& translation : m_Translations)
		{
			glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translation.second);
			glm::mat4 mvp = m_ProjMat * m_ViewMat * modelMat;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Renderer->Draw(*m_Va, *m_Ib, *m_Shader);
		}
	}

	void TestSquare::OnImGuiRender()
	{
		for (auto& translation : m_Translations)
		{
			ImGui::SliderFloat3(translation.first.c_str(), &translation.second.x, 0.0f, WindowSize::Width);
		}
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void TestSquare::OnDelete()
	{
		m_Va->UnBind();
		m_Vb->Unbind();
		m_Ib->Unbind();
		m_Shader->Unbind();
	}

}

