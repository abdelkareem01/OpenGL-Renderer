#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>

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
	class Test
	{
	public:
		Test(){}
		virtual ~Test(){}

		virtual void OnUpdate(float deltaTime){}
		virtual void OnRender(){}
		virtual void OnImGuiRender(){}
		virtual void OnDelete(){};
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu();

		void OnImGuiRender() override;

		struct always_false : std::false_type {};
		template<typename T>
		void RegisterTest(const std::string& name, VertexArray* va = nullptr, Shader* shader = nullptr, Renderer* renderer = nullptr, int nTranslations = 0)
		{
			m_Tests.push_back(std::make_pair(name, [=]()-> test::Test*
			{
			
				if constexpr (std::is_constructible_v<T, VertexArray&, Shader&, Renderer&, int>)
				{
					return new T(*va, *shader, *renderer, nTranslations);
				}
				else if constexpr (std::is_default_constructible_v<T>)
				{
					return new T();
				}
				else
				{
					std::cout << "Test must be constructible with (VertexArray*, Shader*, Renderer*, int) or be default-constructible." << std::endl;
					return nullptr;
				}

			}));

		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

	};
}
