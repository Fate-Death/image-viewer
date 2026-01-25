#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fill_colorP6(SDL_Surface *, int, int, FILE *);
void fill_colorP3(SDL_Surface *, int, int, FILE *);
void skip_comments(FILE *f);

int main(int argc, char **args) {

  if (argc < 2) {
    fprintf(stderr, "Please enter one file name of '.ppm' format\n");
    return 1;
  }
  FILE *in = fopen(args[1], "rb");
  if (!in) {
    perror("fopen");
    return 1;
  }
  char *pthroway = calloc(1000, sizeof(char));
  // FIRST line(p3 or p6)
  char *pversion = calloc(4, sizeof(char));
  fgets(pversion, 4, in);
  printf("%s\n", pversion);
  // fgets(pthroway, 1000, in);
  //  Second Line
  skip_comments(in);
  // fgets(pthroway, 1000, in);
  //  Third Line(Dimension)
  char *pdimensions = calloc(1000, sizeof(char));
  fgets(pdimensions, 1000, in);
  // Fourth line
  fgets(pthroway, 1000, in);
  free(pthroway);

  int width = -1;
  int height = -1;
  sscanf(pdimensions, "%d %d\n", &width, &height);
  free(pdimensions);

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window =
      SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, 0);
  printf("Width = %d, Height = %d\n", width, height);

  SDL_Surface *psurface = SDL_GetWindowSurface(window);
  // comparing
  if (strcmp(pversion, "P6\n") == 0) {
    fill_colorP6(psurface, width, height, in);
  } else {
    fill_colorP3(psurface, width, height, in);
  }

  SDL_UpdateWindowSurface(window);
  int quit = 0;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      }
    }
    SDL_Delay(100);
  }

  return 0;
}
void fill_colorP6(SDL_Surface *psurface, int width, int height, FILE *in) {

  printf("Using P6");
  Uint8 r, g, b;
  Uint32 color = 0; // single pixel
  SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      r = fgetc(in);
      g = fgetc(in);
      b = fgetc(in);
      color = SDL_MapRGB(psurface->format, r, g, b);
      pixel.x = x;
      pixel.y = y;
      SDL_FillRect(psurface, &pixel, color);
    }
  }
}
void fill_colorP3(SDL_Surface *psurface, int width, int height, FILE *in) {

  printf("Using P3");
  Uint8 r, g, b;
  Uint32 color = 0; // single pixel
  SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
  int ri, gi, bi;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      fscanf(in, "%d %d %d", &ri, &gi, &bi);
      r = ri;
      g = gi;
      b = bi;
      color = SDL_MapRGB(psurface->format, r, g, b);
      pixel.x = x;
      pixel.y = y;
      SDL_FillRect(psurface, &pixel, color);
    }
  }
}

void skip_comments(FILE *f) {
  int c;
  while (1) {
    c = fgetc(f);

    // Skip whitespace
    while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
      c = fgetc(f);
    }

    // If comment, skip entire line
    if (c == '#') {
      while (c != '\n' && c != EOF) {
        c = fgetc(f);
      }
    } else {
      // Not a comment → put it back
      ungetc(c, f);
      break;
    }
  }
}
