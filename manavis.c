#include "./manavis.h"

void *scp(void *ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "Oh no! SDL pooped itself, %s\n", SDL_GetError());
    exit(1);
  }
  return ptr;
}

int scc(int code) {
  if (code < 0) {
    fprintf(stderr, "Oh no! SDL pooped itself, %s\n", SDL_GetError());
    exit(1);
  }
  return code;
}

void manavis_show_window(SDL_Window *window, SDL_Renderer *renderer, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);

  window = (SDL_Window*)scp(SDL_CreateWindow("Manavis",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				width,
				height,
				SDL_WINDOW_RESIZABLE));
  renderer = (SDL_Renderer*)scp(SDL_CreateRenderer(window,
				    -1,
				    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
  manavis_render_window(renderer);
}

void manavis_render_window(SDL_Renderer *renderer) {
  int quit = 0;

  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	quit = true;
	break;
      case SDL_KEYDOWN: {
	switch (event.key.keysym.sym) {
	case SDLK_q:
	  quit = true;
	  break;
	}
      }
      }
    }
    SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR));
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
  }
}
