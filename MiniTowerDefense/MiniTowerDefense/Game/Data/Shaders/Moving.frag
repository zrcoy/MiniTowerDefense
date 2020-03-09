#version 120

varying vec4 v_Color;
varying vec2 v_UVCoord;

// texture unit, default is 0
uniform sampler2D u_TextureSampler;

void main()
{
    gl_FragColor = v_Color;
	//Sample the texture at the interpolated UV coordinate
	vec4 color= texture2D( u_TextureSampler,v_UVCoord );
	gl_FragColor=color;
}
