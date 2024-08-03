#ifndef FGE_PRIM_RENDERER_H_
#define FGE_PRIM_RENDERER_H_
/*
BSD 3-Clause License

Copyright (c) 2024, FloDev

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "ext/simple_loader.h"
#include "fge_types.h"
#include "fge_prim_geometry.h"
#include "fge_debug.h"

#ifdef VERTEX_PATH
#define __VERTEX_PATH VERTEX_PATH
#else 
#define __VERTEX_PATH "shader/default_vertex.glsl"
#endif
#ifdef FRAGMENT_PATH
#define __FRAGMENT_PATH FRAGMENT_PATH
#else 
#define __FRAGMENT_PATH "shader/default_fragment.glsl"
#endif



#define __FGE_EXPAND_COLOR_STRUCT(__COLOR_STRUCT__)(float)__COLOR_STRUCT__.r,(float)__COLOR_STRUCT__.g,(float)__COLOR_STRUCT__.b,(float)__COLOR_STRUCT__.a
#define FGE_START_RENDER() glClear(GL_COLOR_BUFFER_BIT)



inline struct __FGE_PRIMITIVE_RENDERER{unsigned int vertexBuffer; unsigned int vertexArray; unsigned int elementBuffer;
 unsigned int shaderProgram;}
__fge_primitive_renderer;
inline class __FGE_PRIMITIVE_GlUniformSystem
{
private:
std::unordered_map<const char*, int> uniformMap;
public:
inline __FGE_PRIMITIVE_GlUniformSystem() {};
inline __FGE_PRIMITIVE_GlUniformSystem& add(const char* uniform)
{
    int location=glGetUniformLocation(__fge_primitive_renderer.shaderProgram,uniform);
    uniformMap.insert({uniform,location});
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val)
{
    glUniform1f(uniformMap.at(uniform),val);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2)
{
    glUniform2f(uniformMap.at(uniform),val1,val2);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3)
{
    glUniform3f(uniformMap.at(uniform),val1,val2,val3);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3, float val4)
{
    glUniform4f(uniformMap.at(uniform),val1,val2,val3, val4);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& setf(const char* uniform,float val1, float val2, float val3, float val4, float val5, float val6)
{
    float buffer[]={val1,  val2,  val3,  val4,  val5,  val6};
    glUniformMatrix2x3fv(uniformMap.at(uniform),1,GL_FALSE, buffer);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1)
{
    glUniform1i(uniformMap.at(uniform),val1);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1, int val2)
{
    glUniform2i(uniformMap.at(uniform),val1,val2);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1, int val2, int val3)
{
    glUniform3i(uniformMap.at(uniform),val1,val2,val3);
    return *this;
}
inline __FGE_PRIMITIVE_GlUniformSystem& seti(const char* uniform,int val1, int val2, int val3, int val4)
{
    glUniform4i(uniformMap.at(uniform),val1,val2,val3, val4);
    return *this;
}


} __fge_primitive_uniform_sys;



constexpr std::string_view ShaderVersion{"#version 330 core\n"};

inline std::vector<unsigned int> __FGE_PRIMITIVE_INDICES(size_t S)noexcept
{  
    std::vector<unsigned int> retVal;
    retVal.reserve(3*(S-1));

    for(size_t i=1; i<S-1; ++i){retVal.push_back(0);retVal.push_back(i);retVal.push_back(i+1); }
    return retVal;
}

inline std::string __FGE_PRIMITIVE_GetShaderSrc(const char* src)noexcept
{
    std::ifstream file(src,std::ios::binary);
    std::string shaderSource;
    shaderSource+=ShaderVersion;
    {
    std::string line="";
    while(std::getline(file,line))shaderSource+=line+"\n";
    shaderSource+="\0";
    }

    return shaderSource;
}

constexpr void __FGE_PRIMITIVE_SetAttributes(int dimensions=2,int index= 0,int stride=0  )noexcept
{
if(!stride)stride=dimensions; 
glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, stride * sizeof(float),
(void*)(index*dimensions*sizeof(float)));
glEnableVertexAttribArray(index);
}

inline void __FGE_PRIM_RENDER_INIT(const char* vertexSrc, const char* fragmentSrc, const std::vector<const char*>& uniformArgs )noexcept
{
    glGenBuffers(1,&__fge_primitive_renderer.vertexBuffer);
    glGenBuffers(1,&__fge_primitive_renderer.elementBuffer);
    glGenVertexArrays(1,&__fge_primitive_renderer.vertexArray);

    unsigned int vertexId=glCreateShader(GL_VERTEX_SHADER);
    std::string retVal=__FGE_PRIMITIVE_GetShaderSrc(vertexSrc);
    const char* Ssource=retVal.c_str();
    glShaderSource(vertexId, 1, &Ssource, NULL);
    glCompileShader(vertexId);

    #ifndef FGE_Active
    int success;
    char infoLog[512];
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
    glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
    FGE_EXIT("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog);
    
    }
    #endif

    unsigned int fragmentId=glCreateShader(GL_FRAGMENT_SHADER);
    retVal=__FGE_PRIMITIVE_GetShaderSrc(fragmentSrc);
    Ssource=retVal.c_str();
    glShaderSource(fragmentId, 1, &Ssource, NULL);
    glCompileShader(fragmentId);

    #ifndef FGE_Active
    
    if(!success)
    {    
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    glGetShaderInfoLog(fragmentId, 512, NULL, infoLog);
    FGE_EXIT("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<infoLog ) ;
    }
    #endif

    __fge_primitive_renderer.shaderProgram=glCreateProgram();
    glAttachShader(__fge_primitive_renderer.shaderProgram,vertexId);
    glAttachShader(__fge_primitive_renderer.shaderProgram,fragmentId);
    glLinkProgram(__fge_primitive_renderer.shaderProgram);
    
    glDeleteShader(vertexId); glDeleteShader(fragmentId);

    #ifndef FGE_Active
  
    glGetProgramiv(__fge_primitive_renderer.shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
    glGetProgramInfoLog(__fge_primitive_renderer.shaderProgram, 512, NULL, infoLog);
    FGE_EXIT("ERROR::PROGRAM::COMPILATION_FAILED\n" <<infoLog );
    }
    #endif

    glUseProgram(__fge_primitive_renderer.shaderProgram);

    for(auto& el: uniformArgs)__fge_primitive_uniform_sys.add(el);
}
inline void __FGE_PRIM_RENDER_DELETE()noexcept
{
    glDeleteProgram(__fge_primitive_renderer.shaderProgram);
    glDeleteBuffers(1,&__fge_primitive_renderer.vertexBuffer);
    glDeleteBuffers(1,&__fge_primitive_renderer.elementBuffer);
    glDeleteVertexArrays(1,&__fge_primitive_renderer.vertexArray);
}
#define FGE_PRIM_RENDER_DELETE() __FGE_PRIM_RENDER_DELETE()
inline int __FGE_PRIM_RENDER_UNIFORM_LOCATION(const char* uniform)noexcept
{
    return glGetUniformLocation(__fge_primitive_renderer.shaderProgram,uniform);
} 


inline void __FGE_PRIM_RENDER_FILL_SHAPE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    const size_t indicesSize{3*(Size-1)};

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indicesSize,__FGE_PRIMITIVE_PRELOAD_INDICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,indicesSize,GL_UNSIGNED_INT,0);
}
inline void __FGE_PRIM_RENDER_DRAW_SHAPE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,Size);
}
inline void __FGE_PRIM_RENDER_DRAW_LINE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINES,0,Size);
}
inline void __FGE_PRIM_RENDER_FILL_TRIANGLE(float* data, size_t Size,GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*2*Size,data,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_TRIANGLES,0,Size);
}
inline void __FGE_PRIM_RENDER_FILL_SIMPLE_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
  

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*14,(float*)__FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_VERTICES,usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*9,(unsigned int*)__FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_INDICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
}

inline void __FGE_PRIM_RENDER_DRAW_SIMPLE_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,__FGE_PRIMITIVE_PRELOAD_SIMPLE_ARROW_VERTICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,8);
}

/*FIX DRAW CODE, DEPRECATED*/
inline void __FGE_PRIM_RENDER_FILL_FANCY_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
  

    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,(float*)__FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_VERTICES,usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,__fge_primitive_renderer.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*12,(unsigned int*)__FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_INDICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);

    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);
}
/*FIX DRAW CODE, DEPRECATED*/
inline void __FGE_PRIM_RENDER_DRAW_FANCY_ARROW(GLenum usage=GL_DYNAMIC_DRAW)noexcept 
{
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER,__fge_primitive_renderer.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*16,__FGE_PRIMITIVE_PRELOAD_FANCY_ARROW_VERTICES,usage);
    
    __FGE_PRIMITIVE_SetAttributes(2);
    glBindVertexArray(__fge_primitive_renderer.vertexArray);
    glUseProgram(__fge_primitive_renderer.shaderProgram);
    glDrawArrays(GL_LINE_STRIP,0,8);
}


inline void FGE_RENDER_SMOOTH()
{
    glEnable( GL_LINE_SMOOTH );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


inline void FGE_INIT_RENDER_DEFAULT()
{
    __FGE_PRIM_RENDER_INIT(__VERTEX_PATH,__FRAGMENT_PATH,{"myColor","windSize","coordMode","drawImage","ourTexture","transCoords","allowTrans"});
    __fge_primitive_uniform_sys.setf("myColor",0,0,0,0)
    .setf("windSize",800,600).seti("coordMode",0).seti("drawImage",0).seti("ourTexture",0).seti("allowTrans",0)
    .setf("transCoords",1,0,0,0,1,0);

    FGE_RENDER_SMOOTH();
}
inline void FGE_SetPosTransMatrix(float a11, float a12, float a13, float a21, float a22, float a23)noexcept
{
    __fge_primitive_uniform_sys.setf("transCoords",a11,a12,a13, a21,a22,a23);
}
inline void FGE_AllowTransform()noexcept
{
__fge_primitive_uniform_sys.seti("allowTrans",1);
}
inline void FGE_DisallowTransform()noexcept
{
__fge_primitive_uniform_sys.seti("allowTrans",0);
}
inline void FGE_UseRelativeCoords()noexcept
{
   __fge_primitive_uniform_sys.seti("coordMode",0);
}
inline void FGE_SendWindowSize(float winWidth, float winHeight)
{
    glViewport(0,0,winWidth,winHeight);
    __fge_primitive_uniform_sys.setf("windSize",winWidth,winHeight);
}
inline void FGE_UseAbsoluteCoords()noexcept
{
   __fge_primitive_uniform_sys.seti("coordMode",1);
}
inline void FGE_SetColor(const FGE_Color& col)noexcept
{
 __fge_primitive_uniform_sys.setf("myColor",__FGE_EXPAND_COLOR_STRUCT(col));
}
inline void FGE_SetColor(float r, float g, float b, float a)noexcept
{
 __fge_primitive_uniform_sys.setf("myColor",r,g,b,a);
}
inline void FGE_SetClearColor(const FGE_Color& col)noexcept
{
    glClearColor(col.r/255.0f,col.g/255.0f,col.b/255.0f,col.a/255.0f);
}

#endif