#version 410 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture1;
uniform vec4 tint;

void main() {
	color = tint * texture(texture1, TexCoords);
}