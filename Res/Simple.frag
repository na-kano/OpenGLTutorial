/*
*@file Simple.frag
*/

#version 410

layout(location=0) in vec4 inColor;
layout(location=1) in vec2 inTexCoord;
uniform sampler2D texColor; 
out vec4 fragColor; 

//�t���O�����g�V�F�[�_�[

void main() {
	fragColor = inColor * texture(texColor,inTexCoord); 
}