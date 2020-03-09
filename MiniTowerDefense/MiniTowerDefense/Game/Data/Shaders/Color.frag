#version 120

varying vec4 v_Color;
varying vec2 v_UVCoord;

uniform float u_HealthPercentage;

// texture unit, default is 0
uniform sampler2D u_TextureSampler;

void main()
{
	vec4 color=v_Color;

//	color.r=u_HealthPercentage;
//	color.g=u_HealthPercentage;
//	color.b=u_HealthPercentage;

    gl_FragColor = color;
	//Sample the texture at the interpolated UV coordinate
	//vec4 color= texture2D( u_TextureSampler,v_UVCoord );
	//gl_FragColor=color;
}
