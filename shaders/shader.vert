#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBuffer {
    mat4 MVP;
};

layout(location = 0) in vec3 xyz;
layout(location = 1) in vec3 rgb;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = MVP * vec4(xyz, 1.0);
    fragColor = rgb;
}