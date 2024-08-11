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
# Classes 
## fge_window 
* fge_window(const char* title, int width, int height, int flags=0)
* title: the name of the window
* width, height: the dimensions of the window
* different window flags, that are derived from WIN32 WM_<FLAG_NAME>
### functions:
* set_viewport(float x, float y, float w, float h) Sets the viewport for OpenGL
* is_running() returns window running state as int.  if 0, then application enters exit mode
* poll_events() updates window messages
* get_delta_time() returns time between two frames in milliseconds
* get_fps() returns the current frame rate
* key_down(int key) returns true when a key represented by its ascii code is pressed the first time
* key_up(int key) returns true when a key represented by its ascii code is released
* get_width() returns the current window width
* get_height() returns the current window height
* get_cursor(int& x, int&y) puts into x and y the current mouse position in window coordinates
* swap() Swaps the window buffer
* left_click() returns true, if the left mouse button got clicked
* right_click() returns true if the right mouse button got clicked
* wheel_click() returns true if the wheel mouse button got clicked
* left_release() returns true if the left mouse button got released
* right_release() returns true if the right mouse button got released
* wheel_release() returns true if the wheel mouse button got released
* get_wheel_delta() returns an int every time the mouse wheel is rotated the describes the rotation orientation minus-> down, plus-> up
* show() tells WIN32 to show the window
