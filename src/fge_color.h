#ifndef FGE_COLOR_H_
#define FGE_COLOR_H_
#include "fge_types.h"
#include <array>
#include "ext/quick_math.h"

/*
The mantra of this header is that colors should come out of the box with zero mental overhead.
This goes against the general design philosophy of this library, but colors should always be hands on imo
and I do not really care about them and do not want to. 
*/
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
/*Mixes colors together*/
constexpr FGE_Color operator|(const FGE_Color& a, const FGE_Color& b)
{
	const int R=(a.r+b.r);
	const int G=(a.g+b.g);
	const int B=(a.b+b.b);
	return {(uint8_t)(R>>1),(uint8_t)(G>>1),(uint8_t)(B>>1),255}; 
}
/*Computes the complementary color*/
constexpr FGE_Color operator~(const FGE_Color& a)
{
	const int R=(255-a.r);
	const int G=(255-a.g);
	const int B=(255-a.b);
	return {(uint8_t)R,(uint8_t)G,(uint8_t)B,255}; 
}
namespace FGE{

	template<size_t S>
	constexpr std::array<FGE_Color, S> ColorInterpolationSet(const FGE_Color& a, const FGE_Color& b)
	{
		std::array<FGE_Color, S>retVal; 
		const FGE_Color diff{a.r-b.r, a.g-b.g,a.b-b.b, a.a-b.a};
		constexpr size_t SM{S-1};
		for(size_t i=0; i<S;++i)
		{
		const float t{(i/SM)};
		retVal.at(i)={a.r+diff.r*t,a.g+diff.g*t,a.b+diff.b*t,a.a+diff.a*t}; 
		}
		return retVal;
	}
	/*moves each RGB value closer to zero by a percentage of its distance, alpha MUST BE between zero and one*/
	constexpr FGE_Color darken(const FGE_Color& a, float alpha)
	{
	const float complAlpha{1-alpha};
	return {(uint8_t)(a.r*complAlpha),(uint8_t)(a.g*complAlpha),(uint8_t)(a.b*complAlpha),a.a};
	}
	/*moves each RGB value closer to 255 by a percentage of its distance, alpha MUST BE between zero and one*/
	constexpr FGE_Color lighten(const FGE_Color& a, float alpha)
	{
	const float rDist{255.f-a.r};
	const float gDist{255.f-a.g};
	const float bDist{255.f-a.b};

	return {(uint8_t)(a.r+rDist*alpha),(uint8_t)(a.g+gDist*alpha),(uint8_t)(a.b+bDist*alpha),a.a};
	}


	/*BASIC COLOR CODES: https://www.rapidtables.com/web/color/RGB_Color.html, last visited: 13.10.2023*/
    constexpr FGE_Color maroon		={128,0,0,255};
	constexpr FGE_Color darkred		={139,0,0,255};
	constexpr FGE_Color brown		={165,42,42,255};
	constexpr FGE_Color firebrick		={178,34,34,255};
	constexpr FGE_Color crimson		={220,20,60,255};
	constexpr FGE_Color red		={255,0,0,255};
	constexpr FGE_Color tomato		={255,99,71,255};
	constexpr FGE_Color coral		={255,127,80,255};
	constexpr FGE_Color indianred		={205,92,92,255};
	constexpr FGE_Color lightcoral		={240,128,128,255};
	constexpr FGE_Color darksalmon		={233,150,122,255};
	constexpr FGE_Color salmon		={250,128,114,255};
	constexpr FGE_Color lightsalmon		={255,160,122,255};
	constexpr FGE_Color orangered		={255,69,0,255};
	constexpr FGE_Color darkorange		={255,140,0,255};
	constexpr FGE_Color orange		={255,165,0,255};
	constexpr FGE_Color gold		={255,215,0,255};
	constexpr FGE_Color darkgoldenrod		={184,134,11,255};
	constexpr FGE_Color goldenrod		={218,165,32,255};
	constexpr FGE_Color palegoldenrod		={238,232,170,255};
	constexpr FGE_Color darkkhaki		={189,183,107,255};
	constexpr FGE_Color khaki		={240,230,140,255};
	constexpr FGE_Color olive		={128,128,0,255};
	constexpr FGE_Color yellow		={255,255,0,255};
	constexpr FGE_Color yellowgreen		={154,205,50,255};
	constexpr FGE_Color darkolivegreen		={85,107,47,255};
	constexpr FGE_Color olivedrab		={107,142,35,255};
	constexpr FGE_Color lawngreen		={124,252,0,255};
	constexpr FGE_Color chartreuse		={127,255,0,255};
	constexpr FGE_Color greenyellow		={173,255,47,255};
	constexpr FGE_Color darkgreen		={0,100,0,255};
	constexpr FGE_Color green		={0,128,0,255};
	constexpr FGE_Color forestgreen		={34,139,34,255};
	constexpr FGE_Color lime		={0,255,0,255};
	constexpr FGE_Color limegreen		={50,205,50,255};
	constexpr FGE_Color lightgreen		={144,238,144,255};
	constexpr FGE_Color palegreen		={152,251,152,255};
	constexpr FGE_Color darkseagreen		={143,188,143,255};
	constexpr FGE_Color mediumspringgreen		={0,250,154,255};
	constexpr FGE_Color springgreen		={0,255,127,255};
	constexpr FGE_Color seagreen		={46,139,87,255};
	constexpr FGE_Color mediumaquamarine		={102,205,170,255};
	constexpr FGE_Color mediumseagreen		={60,179,113,255};
	constexpr FGE_Color lightseagreen		={32,178,170,255};
	constexpr FGE_Color darkslategray		={47,79,79,255};
	constexpr FGE_Color teal		={0,128,128,255};
	constexpr FGE_Color darkcyan		={0,139,139,255};
	constexpr FGE_Color aqua		={0,255,255,255};
	constexpr FGE_Color cyan		={0,255,255,255};
	constexpr FGE_Color lightcyan		={224,255,255,255};
	constexpr FGE_Color darkturquoise		={0,206,209,255};
	constexpr FGE_Color turquoise		={64,224,208,255};
	constexpr FGE_Color mediumturquoise		={72,209,204,255};
	constexpr FGE_Color paleturquoise		={175,238,238,255};
	constexpr FGE_Color aquamarine		={127,255,212,255};
	constexpr FGE_Color powderblue		={176,224,230,255};
	constexpr FGE_Color cadetblue		={95,158,160,255};
	constexpr FGE_Color steelblue		={70,130,180,255};
	constexpr FGE_Color cornflowerblue		={100,149,237,255};
	constexpr FGE_Color deepskyblue		={0,191,255,255};
	constexpr FGE_Color dodgerblue		={30,144,255,255};
	constexpr FGE_Color lightblue		={173,216,230,255};
	constexpr FGE_Color skyblue		={135,206,235,255};
	constexpr FGE_Color lightskyblue		={135,206,250,255};
	constexpr FGE_Color midnightblue		={25,25,112,255};
	constexpr FGE_Color navy		={0,0,128,255};
	constexpr FGE_Color darkblue		={0,0,139,255};
	constexpr FGE_Color mediumblue		={0,0,205,255};
	constexpr FGE_Color blue		={0,0,255,255};
	constexpr FGE_Color royalblue		={65,105,225,255};
	constexpr FGE_Color blueviolet		={138,43,226,255};
	constexpr FGE_Color indigo		={75,0,130,255};
	constexpr FGE_Color darkslateblue		={72,61,139,255};
	constexpr FGE_Color slateblue		={106,90,205,255};
	constexpr FGE_Color mediumslateblue		={123,104,238,255};
	constexpr FGE_Color mediumpurple		={147,112,219,255};
	constexpr FGE_Color darkmagenta		={139,0,139,255};
	constexpr FGE_Color darkviolet		={148,0,211,255};
	constexpr FGE_Color darkorchid		={153,50,204,255};
	constexpr FGE_Color mediumorchid		={186,85,211,255};
	constexpr FGE_Color purple		={128,0,128,255};
	constexpr FGE_Color thistle		={216,191,216,255};
	constexpr FGE_Color plum		={221,160,221,255};
	constexpr FGE_Color violet		={238,130,238,255};
	constexpr FGE_Color magenta		={255,0,255,255};
	constexpr FGE_Color orchid		={218,112,214,255};
	constexpr FGE_Color mediumvioletred		={199,21,133,255};
	constexpr FGE_Color palevioletred		={219,112,147,255};
	constexpr FGE_Color deeppink		={255,20,147,255};
	constexpr FGE_Color hotpink		={255,105,180,255};
	constexpr FGE_Color lightpink		={255,182,193,255};
	constexpr FGE_Color pink		={255,192,203,255};
	constexpr FGE_Color antiquewhite		={250,235,215,255};
	constexpr FGE_Color beige		={245,245,220,255};
	constexpr FGE_Color bisque		={255,228,196,255};
	constexpr FGE_Color blanchedalmond		={255,235,205,255};
	constexpr FGE_Color wheat		={245,222,179,255};
	constexpr FGE_Color cornsilk		={255,248,220,255};
	constexpr FGE_Color lemonchiffon		={255,250,205,255};
	constexpr FGE_Color lightgoldenrodyellow		={250,250,210,255};
	constexpr FGE_Color lightyellow		={255,255,224,255};
	constexpr FGE_Color saddlebrown		={139,69,19,255};
	constexpr FGE_Color sienna		={160,82,45,255};
	constexpr FGE_Color chocolate		={210,105,30,255};
	constexpr FGE_Color peru		={205,133,63,255};
	constexpr FGE_Color sandybrown		={244,164,96,255};
	constexpr FGE_Color burlywood		={222,184,135,255};
	constexpr FGE_Color tanned		={210,180,140,255};
	constexpr FGE_Color rosybrown		={188,143,143,255};
	constexpr FGE_Color moccasin		={255,228,181,255};
	constexpr FGE_Color navajowhite		={255,222,173,255};
	constexpr FGE_Color peachpuff		={255,218,185,255};
	constexpr FGE_Color mistyrose		={255,228,225,255};
	constexpr FGE_Color lavenderblush		={255,240,245,255};
	constexpr FGE_Color linen		={250,240,230,255};
	constexpr FGE_Color oldlace		={253,245,230,255};
	constexpr FGE_Color papayawhip		={255,239,213,255};
	constexpr FGE_Color seashell		={255,245,238,255};
	constexpr FGE_Color mintcream		={245,255,250,255};
	constexpr FGE_Color slategray		={112,128,144,255};
	constexpr FGE_Color lightslategray		={119,136,153,255};
	constexpr FGE_Color lightsteelblue		={176,196,222,255};
	constexpr FGE_Color lavender		={230,230,250,255};
	constexpr FGE_Color floralwhite		={255,250,240,255};
	constexpr FGE_Color aliceblue		={240,248,255,255};
	constexpr FGE_Color ghostwhite		={248,248,255,255};
	constexpr FGE_Color honeydew		={240,255,240,255};
	constexpr FGE_Color ivory		={255,255,240,255};
	constexpr FGE_Color azure		={240,255,255,255};
	constexpr FGE_Color snow		={255,250,250,255};
	constexpr FGE_Color black		={0,0,0,255};
	constexpr FGE_Color dimgray		={105,105,105,255};
	constexpr FGE_Color gray		={128,128,128,255};
	constexpr FGE_Color darkgray		={169,169,169,255};
	constexpr FGE_Color silver		={192,192,192,255};
	constexpr FGE_Color lightgray		={211,211,211,255};
	constexpr FGE_Color gainsboro		={220,220,220,255};
	constexpr FGE_Color whitesmoke		={245,245,245,255};
	constexpr FGE_Color white		={255,255,255,255};





}
#endif