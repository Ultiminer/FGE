#ifndef fge_color_H_
#define fge_color_H_
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
constexpr fge_color operator|(const fge_color& a, const fge_color& b)
{
	const int R=(a.r+b.r);
	const int G=(a.g+b.g);
	const int B=(a.b+b.b);
	return {(uint8_t)(R>>1),(uint8_t)(G>>1),(uint8_t)(B>>1),255}; 
}
/*Computes the complementary color*/
constexpr fge_color operator~(const fge_color& a)
{
	const int R=(255-a.r);
	const int G=(255-a.g);
	const int B=(255-a.b);
	return {(uint8_t)R,(uint8_t)G,(uint8_t)B,255}; 
}
namespace fge{

	template<size_t S>
	constexpr std::array<fge_color, S> ColorInterpolationSet(const fge_color& a, const fge_color& b)
	{
		std::array<fge_color, S>retVal; 
		const fge_color diff{a.r-b.r, a.g-b.g,a.b-b.b, a.a-b.a};
		constexpr size_t SM{S-1};
		for(size_t i=0; i<S;++i)
		{
		const float t{(i/SM)};
		retVal.at(i)={a.r+diff.r*t,a.g+diff.g*t,a.b+diff.b*t,a.a+diff.a*t}; 
		}
		return retVal;
	}
	/*moves each RGB value closer to zero by a percentage of its distance, alpha MUST BE between zero and one*/
	constexpr fge_color darken(const fge_color& a, float alpha)
	{
	const float complAlpha{1-alpha};
	return {(uint8_t)(a.r*complAlpha),(uint8_t)(a.g*complAlpha),(uint8_t)(a.b*complAlpha),a.a};
	}
	/*moves each RGB value closer to 255 by a percentage of its distance, alpha MUST BE between zero and one*/
	constexpr fge_color lighten(const fge_color& a, float alpha)
	{
	const float rDist{255.f-a.r};
	const float gDist{255.f-a.g};
	const float bDist{255.f-a.b};

	return {(uint8_t)(a.r+rDist*alpha),(uint8_t)(a.g+gDist*alpha),(uint8_t)(a.b+bDist*alpha),a.a};
	}


	/*BASIC COLOR CODES: https://www.rapidtables.com/web/color/RGB_Color.html, last visited: 13.10.2023*/
    constexpr fge_color maroon		={128,0,0,255};
	constexpr fge_color darkred		={139,0,0,255};
	constexpr fge_color brown		={165,42,42,255};
	constexpr fge_color firebrick		={178,34,34,255};
	constexpr fge_color crimson		={220,20,60,255};
	constexpr fge_color red		={255,0,0,255};
	constexpr fge_color tomato		={255,99,71,255};
	constexpr fge_color coral		={255,127,80,255};
	constexpr fge_color indianred		={205,92,92,255};
	constexpr fge_color lightcoral		={240,128,128,255};
	constexpr fge_color darksalmon		={233,150,122,255};
	constexpr fge_color salmon		={250,128,114,255};
	constexpr fge_color lightsalmon		={255,160,122,255};
	constexpr fge_color orangered		={255,69,0,255};
	constexpr fge_color darkorange		={255,140,0,255};
	constexpr fge_color orange		={255,165,0,255};
	constexpr fge_color gold		={255,215,0,255};
	constexpr fge_color darkgoldenrod		={184,134,11,255};
	constexpr fge_color goldenrod		={218,165,32,255};
	constexpr fge_color palegoldenrod		={238,232,170,255};
	constexpr fge_color darkkhaki		={189,183,107,255};
	constexpr fge_color khaki		={240,230,140,255};
	constexpr fge_color olive		={128,128,0,255};
	constexpr fge_color yellow		={255,255,0,255};
	constexpr fge_color yellowgreen		={154,205,50,255};
	constexpr fge_color darkolivegreen		={85,107,47,255};
	constexpr fge_color olivedrab		={107,142,35,255};
	constexpr fge_color lawngreen		={124,252,0,255};
	constexpr fge_color chartreuse		={127,255,0,255};
	constexpr fge_color greenyellow		={173,255,47,255};
	constexpr fge_color darkgreen		={0,100,0,255};
	constexpr fge_color green		={0,128,0,255};
	constexpr fge_color forestgreen		={34,139,34,255};
	constexpr fge_color lime		={0,255,0,255};
	constexpr fge_color limegreen		={50,205,50,255};
	constexpr fge_color lightgreen		={144,238,144,255};
	constexpr fge_color palegreen		={152,251,152,255};
	constexpr fge_color darkseagreen		={143,188,143,255};
	constexpr fge_color mediumspringgreen		={0,250,154,255};
	constexpr fge_color springgreen		={0,255,127,255};
	constexpr fge_color seagreen		={46,139,87,255};
	constexpr fge_color mediumaquamarine		={102,205,170,255};
	constexpr fge_color mediumseagreen		={60,179,113,255};
	constexpr fge_color lightseagreen		={32,178,170,255};
	constexpr fge_color darkslategray		={47,79,79,255};
	constexpr fge_color teal		={0,128,128,255};
	constexpr fge_color darkcyan		={0,139,139,255};
	constexpr fge_color aqua		={0,255,255,255};
	constexpr fge_color cyan		={0,255,255,255};
	constexpr fge_color lightcyan		={224,255,255,255};
	constexpr fge_color darkturquoise		={0,206,209,255};
	constexpr fge_color turquoise		={64,224,208,255};
	constexpr fge_color mediumturquoise		={72,209,204,255};
	constexpr fge_color paleturquoise		={175,238,238,255};
	constexpr fge_color aquamarine		={127,255,212,255};
	constexpr fge_color powderblue		={176,224,230,255};
	constexpr fge_color cadetblue		={95,158,160,255};
	constexpr fge_color steelblue		={70,130,180,255};
	constexpr fge_color cornflowerblue		={100,149,237,255};
	constexpr fge_color deepskyblue		={0,191,255,255};
	constexpr fge_color dodgerblue		={30,144,255,255};
	constexpr fge_color lightblue		={173,216,230,255};
	constexpr fge_color skyblue		={135,206,235,255};
	constexpr fge_color lightskyblue		={135,206,250,255};
	constexpr fge_color midnightblue		={25,25,112,255};
	constexpr fge_color navy		={0,0,128,255};
	constexpr fge_color darkblue		={0,0,139,255};
	constexpr fge_color mediumblue		={0,0,205,255};
	constexpr fge_color blue		={0,0,255,255};
	constexpr fge_color royalblue		={65,105,225,255};
	constexpr fge_color blueviolet		={138,43,226,255};
	constexpr fge_color indigo		={75,0,130,255};
	constexpr fge_color darkslateblue		={72,61,139,255};
	constexpr fge_color slateblue		={106,90,205,255};
	constexpr fge_color mediumslateblue		={123,104,238,255};
	constexpr fge_color mediumpurple		={147,112,219,255};
	constexpr fge_color darkmagenta		={139,0,139,255};
	constexpr fge_color darkviolet		={148,0,211,255};
	constexpr fge_color darkorchid		={153,50,204,255};
	constexpr fge_color mediumorchid		={186,85,211,255};
	constexpr fge_color purple		={128,0,128,255};
	constexpr fge_color thistle		={216,191,216,255};
	constexpr fge_color plum		={221,160,221,255};
	constexpr fge_color violet		={238,130,238,255};
	constexpr fge_color magenta		={255,0,255,255};
	constexpr fge_color orchid		={218,112,214,255};
	constexpr fge_color mediumvioletred		={199,21,133,255};
	constexpr fge_color palevioletred		={219,112,147,255};
	constexpr fge_color deeppink		={255,20,147,255};
	constexpr fge_color hotpink		={255,105,180,255};
	constexpr fge_color lightpink		={255,182,193,255};
	constexpr fge_color pink		={255,192,203,255};
	constexpr fge_color antiquewhite		={250,235,215,255};
	constexpr fge_color beige		={245,245,220,255};
	constexpr fge_color bisque		={255,228,196,255};
	constexpr fge_color blanchedalmond		={255,235,205,255};
	constexpr fge_color wheat		={245,222,179,255};
	constexpr fge_color cornsilk		={255,248,220,255};
	constexpr fge_color lemonchiffon		={255,250,205,255};
	constexpr fge_color lightgoldenrodyellow		={250,250,210,255};
	constexpr fge_color lightyellow		={255,255,224,255};
	constexpr fge_color saddlebrown		={139,69,19,255};
	constexpr fge_color sienna		={160,82,45,255};
	constexpr fge_color chocolate		={210,105,30,255};
	constexpr fge_color peru		={205,133,63,255};
	constexpr fge_color sandybrown		={244,164,96,255};
	constexpr fge_color burlywood		={222,184,135,255};
	constexpr fge_color tanned		={210,180,140,255};
	constexpr fge_color rosybrown		={188,143,143,255};
	constexpr fge_color moccasin		={255,228,181,255};
	constexpr fge_color navajowhite		={255,222,173,255};
	constexpr fge_color peachpuff		={255,218,185,255};
	constexpr fge_color mistyrose		={255,228,225,255};
	constexpr fge_color lavenderblush		={255,240,245,255};
	constexpr fge_color linen		={250,240,230,255};
	constexpr fge_color oldlace		={253,245,230,255};
	constexpr fge_color papayawhip		={255,239,213,255};
	constexpr fge_color seashell		={255,245,238,255};
	constexpr fge_color mintcream		={245,255,250,255};
	constexpr fge_color slategray		={112,128,144,255};
	constexpr fge_color lightslategray		={119,136,153,255};
	constexpr fge_color lightsteelblue		={176,196,222,255};
	constexpr fge_color lavender		={230,230,250,255};
	constexpr fge_color floralwhite		={255,250,240,255};
	constexpr fge_color aliceblue		={240,248,255,255};
	constexpr fge_color ghostwhite		={248,248,255,255};
	constexpr fge_color honeydew		={240,255,240,255};
	constexpr fge_color ivory		={255,255,240,255};
	constexpr fge_color azure		={240,255,255,255};
	constexpr fge_color snow		={255,250,250,255};
	constexpr fge_color black		={0,0,0,255};
	constexpr fge_color dimgray		={105,105,105,255};
	constexpr fge_color gray		={128,128,128,255};
	constexpr fge_color darkgray		={169,169,169,255};
	constexpr fge_color silver		={192,192,192,255};
	constexpr fge_color lightgray		={211,211,211,255};
	constexpr fge_color gainsboro		={220,220,220,255};
	constexpr fge_color whitesmoke		={245,245,245,255};
	constexpr fge_color white		={255,255,255,255};





}
#endif