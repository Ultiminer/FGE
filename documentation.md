# The Documentation for FGE
# Primitives 
## fge_fpoint 
* fge_fpoint(float x, float y)
* A simple container for 2D points in floating point representation
## fge_point
* fge_point(int x, int y)
* A simple container for 2D points using integers
## fge_frect 
* fge_frect(float x, float y, float w, float h)
* A container representing a non-rotated rectangle with floating point numbers
* note: (x,y) specifies the lower-left point, since fge uses an intuitive coordinate system
## fge_rect 
* fge_rect(int x, int y, int w, int h)
* A container representing a non-rotated rectangle with integers
* note: (x,y) specifies the lower-left point, since fge uses an intuitive coordinate system
## fge_color 
* fge_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
* A 4 byte color struct in which the last byte represents the alpha channel
## fge_line 
* fge_line(float x1, float y1, float x2, float y2)
* A container of four floats and two points representing a straight line
