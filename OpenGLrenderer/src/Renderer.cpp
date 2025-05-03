#include "Renderer.h"
#include <iostream>

float WindowSize::Width;
float WindowSize::Height;

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGl Error] (" << error << "): " << function << " contained in " << file << " " << "at " << line << '\n';
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr)); //call the binded index array draw call(because the IBO is already binded we put nullptr instead of the IBO)
}
