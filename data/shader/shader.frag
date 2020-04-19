#version 330 core
out vec4 o_colour;

in vec3 f_texCoord;

uniform sampler2DArray u_textureArray;

void main() {
    o_colour = texture(u_textureArray, f_texCoord);
}
