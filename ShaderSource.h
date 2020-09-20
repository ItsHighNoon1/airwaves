#pragma once

// I'm not in the mood to distribute shader files, so we're writing shaders in a header. Sorry.
const char* vertexSource = R"(
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vTex;

uniform mat4 u_modelViewProjectionMatrix;
uniform float u_xOffset;

void main() {
	vTex = vec2(aTex.x + u_xOffset, aTex.y);
	gl_Position = u_modelViewProjectionMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
)";
const char* fragmentSource = R"(
#version 330 core

in vec2 vTex;

out vec4 color;

uniform sampler2D u_tex;

void main() {
	color = texture(u_tex, vTex);
	if (color.r == 0.0 && color.g == 0.0 && color.b == 0.0) {
		discard;
	}
}
)";