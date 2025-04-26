#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;   //tex coords gets outputed from vert shader

uniform mat4 u_MVP; //model view projection matrix

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord; //tex coords gets inputed into frag shader

uniform vec4 u_Color;
uniform sampler2D u_Texture;   //the sampler rasterized the image(pixelizes)

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = u_Color * texColor;
};