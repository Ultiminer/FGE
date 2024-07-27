out vec4 FragColor;
uniform vec4 myColor; 
uniform int drawImage; 
uniform sampler2D ourTexture;
in vec2 texCoord; 
const float conv=0.0039215686274509803921568627451;


void main()
{
if(drawImage==1){
vec4 imColor=texture(ourTexture,texCoord);
FragColor=vec4(imColor.x,imColor.y,imColor.z,imColor.w);
}
else if(drawImage==2)
{
vec4 imColor=texture(ourTexture,texCoord);
FragColor=vec4(myColor.x*conv,myColor.y*conv,myColor.z*conv,imColor.w);
}
else if(drawImage==0)
FragColor = vec4(myColor.x*conv,myColor.y*conv,myColor.z*conv,myColor.w*conv);

}
