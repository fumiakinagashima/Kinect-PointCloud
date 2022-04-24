#pragma once

const char* srcVertexShader =
R"(
#version 430
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec4 col;

uniform mat4 mvp;

void main()
{
    vec3 pos = vec3(vertexPosition.x * 0.001, vertexPosition.y * -0.001, vertexPosition.z * -0.001);
    gl_Position = mvp * vec4(pos, 1.0f);
    col = vec4(vertexColor.b/255, vertexColor.g/255, vertexColor.r/255, vertexColor.a/255);
}
)";

const char* srcFragmentShader =
R"(
#version 430

out vec4 fragmentColor;
in vec4 col;

void main()
{
    if (col.a == 0.0f) discard;
    fragmentColor = col;
}
)";