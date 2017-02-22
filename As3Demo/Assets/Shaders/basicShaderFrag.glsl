#version 130

varying vec2 textureCoords0;
varying vec3 normal0;
varying vec4 colourData0;

uniform sampler2D mySampler;

void main(void)
{
	gl_FragColor = texture(mySampler, textureCoords0);
}