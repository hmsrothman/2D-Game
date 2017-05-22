#version 400 core

layout (location = 0) in vec2 vertexPos;
layout (location = 1) in vec4 vertexColor;
layout (location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform float time;
uniform mat4 P;

void main(){
	gl_Position.xy = (P*vec4(vertexPos,0,1)).xy;
	gl_Position.z = 0;
	gl_Position.w = 1;
	fragmentColor = vertexColor;
	fragmentUV = vertexUV;
}