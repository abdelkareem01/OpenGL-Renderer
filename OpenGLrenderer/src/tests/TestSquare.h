#pragma once

#include "Test.h"

namespace test
{
	class TestSquare: public Test
	{
	public:
		TestSquare(VertexArray& va, Shader& shader, Renderer& renderer, int nTranslations);
		~TestSquare();
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
		Renderer m_Renderer;
		VertexArray m_Va;
		VertexBuffer m_Vb;
		IndexBuffer m_Ib;
		Shader m_Shader;
	};
}