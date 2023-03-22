#version 460 core
uniform vec3 fsu_color;
uniform float fsu_alpha;
out vec4 fso_fragColor;

void main(){
	fso_fragColor = vec4(fsu_color.xyz, fsu_alpha);
}