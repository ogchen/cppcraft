#version 330 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in float v_texId;

out vec3 f_texCoord;

void main() {
    gl_Position = vec4(v_position, 1.0);
    f_texCoord = vec3(v_position.xy, v_texId);
}
