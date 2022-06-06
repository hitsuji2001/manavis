#ifndef __MANAVIS_H__
#define __MANAVIS_H__

#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT (WINDOW_WIDTH / 16) * 9

#define BACKGROUND_COLOR 0x2EC4B6FF

// ff9f1c-ffbf69-ffffff-cbf3f0-2ec4b6

#define HEX_COLOR(hex)                  \
  ((hex) >> (3 * 8)) & 0xFF,		\
  ((hex) >> (2 * 8)) & 0xFF,		\
  ((hex) >> (1 * 8)) & 0xFF,		\
  ((hex) >> (0 * 8)) & 0xFF

void *scp(void *ptr);
int scc(int code);
void manavis_show_window(SDL_Window *window, SDL_Renderer *renderer, int width, int height);
void manavis_render_window(SDL_Renderer *renderer);

#endif // __MANAVIS_H__
