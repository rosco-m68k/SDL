/*
  rosco_m68k driver for SDL (Simple DirectMedia Layer) 2
  Copyright (C) 2024 The Really Old-School Company Limited <info@rosco-m68k.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_rosco_m68kframebuffer_c_h_
#define SDL_rosco_m68kframebuffer_c_h_

#include "../../SDL_internal.h"

extern int SDL_ROSCO_M68K_CreateWindowFramebuffer(_THIS, SDL_Window *window, Uint32 *format, void **pixels, int *pitch);
extern int SDL_ROSCO_M68K_UpdateWindowFramebuffer(_THIS, SDL_Window *window, const SDL_Rect *rects, int numrects);
extern void SDL_ROSCO_M68K_DestroyWindowFramebuffer(_THIS, SDL_Window *window);

#endif /* SDL_rosco_m68kframebuffer_c_h_ */

/* vi: set ts=4 sw=4 expandtab: */
