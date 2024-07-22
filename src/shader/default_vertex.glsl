layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec2 windSize; 
uniform int coordMode; 
uniform vec4 transCoords; 
uniform int allowTrans; 
out vec2 texCoord; 

void main()
{

texCoord=vec2(aTexCoord.x,aTexCoord.y); 
/*Transformation of position coordinates*/
float tX=aPos.x;
float tY=aPos.y;
if(allowTrans==1){
tX=transCoords.x*aPos.x+transCoords.y*aPos.y; 
tY=transCoords.z*aPos.x+transCoords.w*aPos.y;
}
/*DEFAULT CASE*/
if(coordMode==0)
gl_Position = vec4(tX,tY, 1.0, 1.0);
else
/*ABSOLUTE COORDINATES*/
if(coordMode==1)
gl_Position = vec4(tX/windSize.x,tY/windSize.y, 1.0, 1.0); 


}