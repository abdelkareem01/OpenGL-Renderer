#pragma once

#include "Test.h"

namespace test
{
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D(int nTranslations = 1);
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnDelete() override;

	private:

		std::vector<std::pair<std::string, glm::vec3>> m_Translations;

		float m_Positions[16] = {   //Define unique vertices of the square of whatever shape
		-50.0f, -50.0f, 0.0f, 0.0f, // 0
		-50.0f,  50.0f, 0.0f, 1.0f, // 1
		 50.0f, -50.0f, 1.0f, 0.0f, // 2
		 50.0f,  50.0f, 1.0f, 1.0f, // 3
		};

		unsigned int m_Indices[6]{ //set the indexes of those vertices in order, reusing already defined ones to make the shape
			0,1,2,
			2,1,3,
		};

		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr <VertexArray> m_Va;
		std::unique_ptr <VertexBuffer> m_Vb;
		std::unique_ptr <IndexBuffer> m_Ib;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Texture> m_Texture;

		glm::mat4 m_ProjMat;
		glm::mat4 m_ViewMat;

	};
}