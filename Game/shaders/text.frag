#version 400 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D sampler;

void main(){
	vec4 texColor = texture(sampler,fragmentUV);
	if(texColor.a==0){
		discard;
	}
	color = vec4(fragmentColor.rgb,texColor.r);
}