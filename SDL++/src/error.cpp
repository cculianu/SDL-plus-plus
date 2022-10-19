#include "error.hpp"

const char* SDL::GetError() { return SDL_GetError(); }
void SDL::ClearError() { SDL_ClearError(); }
