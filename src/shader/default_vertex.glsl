layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec2 windSize; 
uniform int coordMode; 
uniform mat2x3 transCoords; 
uniform int allowTrans; 
out vec2 texCoord; 


void main()
{

texCoord=vec2(aTexCoord.x,aTexCoord.y); 
/*Transformation of position coordinates*/
float tX=aPos.x;
float tY=aPos.y;
if(allowTrans==1){
tX=transCoords[0][0]*aPos.x+transCoords[0][1]*aPos.y+transCoords[0][2]; 
tY=transCoords[1][0]*aPos.x+transCoords[1][1]*aPos.y+transCoords[1][2]; 
}
/*DEFAULT CASE*/
if(coordMode==0)
gl_Position = vec4(tX,tY, 1.0, 1.0);
else
/*ABSOLUTE COORDINATES*/
if(coordMode==1)
gl_Position = vec4(2.f*tX/windSize.x,2.f*tY/windSize.y, 1.0, 1.0); 


}