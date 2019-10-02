#ifndef BANDOLIER_MOUSE_BUTTON_CODES_HH
#define BANDOLIER_MOUSE_BUTTON_CODES_HH

#include <GLFW/glfw3.h>

namespace Bandolier{

enum class MouseButtonCodes
{
  // From glfw3.h
_1      =  GLFW_MOUSE_BUTTON_1,
_2      =  GLFW_MOUSE_BUTTON_2,
_3      =  GLFW_MOUSE_BUTTON_3,
_4      =  GLFW_MOUSE_BUTTON_4,
_5      =  GLFW_MOUSE_BUTTON_5,
_6      =  GLFW_MOUSE_BUTTON_6,
_7      =  GLFW_MOUSE_BUTTON_7,
_8      =  GLFW_MOUSE_BUTTON_8,
_LAST   =  _8,
_LEFT   =  _1,
_RIGHT  =  _2,
_MIDDLE =  _3,
};

}

#endif //BANDOLIER_MOUSE_BUTTON_CODES_HH
