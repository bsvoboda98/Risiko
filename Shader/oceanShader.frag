
#version 120

uniform sampler2D texture;

uniform vec2 factor = vec2(10.0, 10.0);

uniform float time = 0;

uniform vec2 scale = vec2 (1.0, 1.0);

uniform vec2 amplitude = vec2(0.001, 0.04);

uniform vec4 colorChange = vec4(0.2, 0.2, 0.2, 0.0);

void main()
{

	vec2 coord = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
	vec2 position = coord * factor;

	vec2 offset;
	offset.x = cos(time + (position.x + position.y) * scale.x);
	offset.y = sin(time + (position.x + position.y) * scale.y);



	vec4 pixel = texture2D(texture, vec2 (gl_TexCoord[0].x * factor.x + offset.x * amplitude.x,
	 						 gl_TexCoord[0].y * factor.y * 1080/1920 + offset.y * amplitude.y));

	gl_FragColor =  gl_Color * pixel - colorChange;
}
