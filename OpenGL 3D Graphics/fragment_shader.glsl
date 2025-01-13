#version 330

out vec4 FragColor;
in vec2 texcoord0;
in vec4 outcol;
uniform sampler2D tex0;



void main()
{
	vec4 color = texture(tex0, texcoord0); 
	color[3]=1.0;
   if(color.r>=0.9)		color[3]=0.0; //czerwony kawy nie jest "pelnym" czerwonym
   gl_FragColor = color;

} 

