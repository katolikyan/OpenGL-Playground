#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLlogCall(#x, __FILE__, __LINE__))

void GLclearError(); 
bool GLLogCall(const char * function, const char *file, int  line);