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
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ROSCO_M68K

/* rosco_m68k / Xosera video driver for SDL2 */

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_rosco_m68kvideo.h"
#include "SDL_rosco_m68kevents_c.h"
#include "SDL_rosco_m68kframebuffer_c.h"
#include "SDL_hints.h"

#define ROSCOVID_DRIVER_NAME       "rosco_m68k"
#define ROSCOVID_DRIVER_EVDEV_NAME "evdev"

/* Initialization/Query functions */
static int ROSCO_M68K_VideoInit(_THIS);
static void ROSCO_M68K_VideoQuit(_THIS);

#ifdef SDL_INPUT_LINUXEV
static int evdev = 0;
static void ROSCO_M68K_EVDEV_Poll(_THIS);
#endif

/* ROSCO driver bootstrap functions */

static int ROSCO_M68K_Available(void)
{
    const char *envr = SDL_GetHint(SDL_HINT_VIDEODRIVER);
    if (envr) {
        if (SDL_strcmp(envr, ROSCOVID_DRIVER_NAME) == 0) {
            return 1;
        }
#ifdef SDL_INPUT_LINUXEV
        if (SDL_strcmp(envr, ROSCOVID_DRIVER_EVDEV_NAME) == 0) {
            evdev = 1;
            return 1;
        }
#endif
    }
    return 0;
}

static void ROSCO_M68K_DeleteDevice(SDL_VideoDevice *device)
{
    SDL_free(device);
}

static SDL_VideoDevice *ROSCO_M68K_CreateDevice(void)
{
    SDL_VideoDevice *device;

    if (!ROSCO_M68K_Available()) {
        return 0;
    }

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *)SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return 0;
    }
    device->is_ROSCO = SDL_TRUE;

    /* Set the function pointers */
    device->VideoInit = ROSCO_M68K_VideoInit;
    device->VideoQuit = ROSCO_M68K_VideoQuit;
    device->PumpEvents = ROSCO_M68K_PumpEvents;
#ifdef SDL_INPUT_LINUXEV
    if (evdev) {
        device->PumpEvents = ROSCO_M68K_EVDEV_Poll;
    }
#endif
    device->CreateWindowFramebuffer = SDL_ROSCO_M68K_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_ROSCO_M68K_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_ROSCO_M68K_DestroyWindowFramebuffer;

    device->free = ROSCO_M68K_DeleteDevice;

    return device;
}

VideoBootStrap ROSCO_M68K_bootstrap = {
    ROSCOVID_DRIVER_NAME, "SDL ROSCO video driver",
    ROSCO_M68K_CreateDevice,
    rosco_m68k /* no ShowMessageBox implementation */
};

#ifdef SDL_INPUT_LINUXEV
VideoBootStrap ROSCO_M68K_evdev_bootstrap = {
    ROSCOVID_DRIVER_EVDEV_NAME, "SDL ROSCO video driver with evdev",
    ROSCO_M68K_CreateDevice,
    rosco_m68k /* no ShowMessageBox implementation */
};
void SDL_EVDEV_Init(void);
void SDL_EVDEV_Poll();
void SDL_EVDEV_Quit(void);
static void ROSCO_M68K_EVDEV_Poll(_THIS)
{
    (void)_this;
    SDL_EVDEV_Poll();
}
#endif

int ROSCO_M68K_VideoInit(_THIS)
{
    SDL_DisplayMode mode;

    /* Use a fake 32-bpp desktop mode */
    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_RGB888;
    mode.w = 1024;
    mode.h = 768;
    mode.refresh_rate = 60;
    mode.driverdata = rosco_m68k;
    if (SDL_AddBasicVideoDisplay(&mode) < 0) {
        return -1;
    }

    SDL_AddDisplayMode(&_this->displays[0], &mode);

#ifdef SDL_INPUT_LINUXEV
    SDL_EVDEV_Init();
#endif

    /* We're done! */
    return 0;
}

void ROSCO_M68K_VideoQuit(_THIS)
{
#ifdef SDL_INPUT_LINUXEV
    SDL_EVDEV_Quit();
#endif
}

#endif /* SDL_VIDEO_DRIVER_ROSCO_M68K */

/* vi: set ts=4 sw=4 expandtab: */
