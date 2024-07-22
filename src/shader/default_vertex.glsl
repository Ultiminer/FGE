layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec2 windSize; 
uniform int coordMode; 

out vec2 texCoord; 

void main()
{

texCoord=vec2(aTexCoord.x,aTexCoord.y); 

/*DEFAULT CASE*/
if(coordMode==0)
gl_Position = vec4(aPos.x,aPos.y, 1.0, 1.0);
else
/*ABSOLUTE COORDINATES*/
if(coordMode==1)
gl_Position = vec4((aPos.x)/windSize.x,(aPos.y)/windSize.y, 1.0, 1.0); 


}