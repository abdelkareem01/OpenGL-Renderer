#pragma once

#include "Test.h"
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
namespace test
{
	class TestSquare: public Test
	{
	public:
		TestSquare(VertexArray& va, Shader& shader);
		~TestSquare();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender(const char* label, glm::vec3& translation);

		VertexBuffer& GetVb(){return m_Vb;}
		IndexBuffer& GetIb(){return m_Ib;}

	private:
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
		VertexBuffer m_Vb;
		IndexBuffer m_Ib;
		Shader m_Shader;
	};
}