#pragma once

#include <GL/glew.h>
#include <string.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : \
     (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))  //macro used to filter the path of a file to just its name(by iterating 1+ the path)

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILENAME__, __LINE__))  //#x is the function and its params

//for GLCall macro the "\" makes it so that it ignores the newline character
//it calls GLClearError, then the function x, then calls ASSERT the GLLogCall() for debugging

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

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

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
