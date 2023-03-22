#version 460 core
layout(location = 0) in vec2 vsi_vertexPosition;
uniform mat4 vsu_projMat;
void main(){
	gl_Position = vsu_projMat * vec4(vsi_vertexPosition.xy , 0.0f, 1.0f);
}