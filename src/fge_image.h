#ifndef FGE_IMAGE_H_
#define FGE_IMAGE_H_
#define STB_IMAGE_IMPLEMENTATION

#include "ext/stb_image.h"
#include "fge_debug.h"
#include <iostream>
#include "fge_types.h"
#include "fge_shape.h"

struct fge_texture
{
unsigned int id=0; 
int width=0;
int height=0; 
int channelNum=0; 
fge_texture(){}
fge_texture(const char* path)
{
glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);

// set the texture wrapping/filtering options (on the currently bound texture object)

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

stbi_set_flip_vertically_on_load(true);  
unsigned char *data= stbi_load((path), &width, &height, &channelNum, 0);

if (data==nullptr) FGE_EXIT("Image path"<<path<<"was nonexistent-> exit!");
const GLint format= (channelNum==4)?GL_RGBA:GL_RGB;
glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);

}
fge_texture(const char* path,GLint formatA,GLint formatB)
{
glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);
// set the texture wrapping/filtering options (on the currently bound texture object)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

stbi_set_flip_vertically_on_load(true);  
unsigned char *data= stbi_load((path), &width, &height, &channelNum, 0);
if (data==nullptr) FGE_EXIT("Image path"<<path<<"was nonexistent-> exit!");
glTexImage2D(GL_TEXTURE_2D, 0, formatA, width, height, 0, formatB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);

}

inline void bind()const 
{
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,id);
}
~fge_texture()
{
    glDeleteTextures(1,&id);    
}

};

constexpr std::array<float,16> __MakeImageVerticies(const fge_frect& rect,float widthPercentage=1,float heightPercentage=1, float xOffset=0,float yOffset=0)
{
    return {rect.x,rect.y+rect.h,xOffset,yOffset+heightPercentage,rect.x+rect.w,rect.y+rect.h,xOffset+widthPercentage,yOffset+heightPercentage,rect.x+rect.w,rect.y,xOffset+widthPercentage,yOffset,rect.x,rect.y,xOffset,yOffset};
}
constexpr std::array<float,16> __MakeImageVerticies(const fge::rect_s& rect,float widthPercentage=1,float heightPercentage=1, float xOffset=0,float yOffset=0)
{
    const auto el=rect.vertices; 
    return {el[0],el[1],xOffset,yOffset+heightPercentage,el[2],el[3],xOffset+widthPercentage,yOffset+heightPercentage,el[4],el[5],xOffset+widthPercentage,yOffset,el[6],el[7],xOffset,yOffset};
}
namespace fge{
inline void draw_image(const fge_frect& rect,  const fge_texture& texture,float widthPercentage=1,float heightPercentage=1, float xOffset=0,float yOffset=0)
{

    __fge_primitive_uniform_sys.seti("ourTexture",0).seti("drawImage",1);
    const size_t indicesSize{6};
    const auto verticies=__MakeImageVerticies(rect,widthPercentage,heightPercentage,xOffset,yOffset);

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*4*4,&verticies,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indicesSize,__FGE_PRIMITIVE_PRELOAD_INDICES,GL_DYNAMIC_DRAW);
   
    __FGE_PRIMITIVE_SetAttributes(2,1,4);
    __FGE_PRIMITIVE_SetAttributes(2,0,4);

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    texture.bind();

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,indicesSize,GL_UNSIGNED_INT,0);
    __fge_primitive_uniform_sys.seti("drawImage",0);
    glDisableVertexAttribArray(1);
}

inline void draw_image(float x, float y, float w , float h,  fge_texture& texture,float widthPercentage=1,float heightPercentage=1, float xOffset=0,float yOffset=0)
{
const fge_frect dummy{x,y,w,h};
draw_image(dummy,texture,widthPercentage,heightPercentage,xOffset,yOffset);
}


inline void draw_alpha(const fge_frect& rect,  const fge_texture& texture,float widthPercentage=1,float heightPercentage=1, float xOffset=0,float yOffset=0)
{

    __fge_primitive_uniform_sys.seti("ourTexture",0).seti("drawImage",2);
    const size_t indicesSize{6};
    const auto verticies=__MakeImageVerticies(rect,widthPercentage,heightPercentage,xOffset,yOffset);

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*4*4,&verticies,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indicesSize,__FGE_PRIMITIVE_PRELOAD_INDICES,GL_DYNAMIC_DRAW);
   
    __FGE_PRIMITIVE_SetAttributes(2,1,4);
    __FGE_PRIMITIVE_SetAttributes(2,0,4);

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    texture.bind();

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,indicesSize,GL_UNSIGNED_INT,0);
    __fge_primitive_uniform_sys.seti("drawImage",0);
    glDisableVertexAttribArray(1);
}


}
#endif