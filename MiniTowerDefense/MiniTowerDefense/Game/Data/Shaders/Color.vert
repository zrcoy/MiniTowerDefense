#version 120

attribute vec2 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

uniform vec2 u_ObjectScale;
uniform float u_ObjectAngleRadians;
uniform vec2 u_ObjectPosition;

uniform vec2 u_CameraTranslation;
uniform vec2 u_ProjectionScale;

varying vec4 v_Color;

uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

varying vec2 v_UVCoord;


void main()
{
	// Object space
    vec2 finalPos = a_Position;

	// world space
	// scale
    finalPos *= u_ObjectScale;
	// rotate
    finalPos = vec2( finalPos.x*cos(u_ObjectAngleRadians) - finalPos.y*sin(u_ObjectAngleRadians),
                     finalPos.x*sin(u_ObjectAngleRadians) + finalPos.y*cos(u_ObjectAngleRadians) );
	// translate
    finalPos += u_ObjectPosition;

	// view space
    finalPos += u_CameraTranslation;
	// clip space
    finalPos *= u_ProjectionScale;

    gl_Position = vec4( finalPos, 0, 1 );

   

	v_UVCoord=a_UVCoord;

	v_UVCoord*=u_UVScale;
	v_UVCoord+=u_UVOffset;


	 v_Color = a_Color;

}
