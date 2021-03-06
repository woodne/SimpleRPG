#include "RenderContext.h"

#include <iostream>

#ifdef SDL2_RENDERER_DEF
RenderContext::RenderContext(std::string title, int xpos, int ypos, int width, int height, int flags) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    return;
  }
  m_window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);

  if (m_window == nullptr) {
    SDL_Quit();
    return;
  }
  wWidth = width;
  wHeight = height;
  
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

RenderContext::RenderContext() {
  RenderContext(std::string(""), 0, 0, 10, 10, 0);
}

RenderContext::~RenderContext() {
  SDL_DestroyRenderer(m_renderer);
}
#endif

void RenderContext::checkFS(bool isFullscreen){
    #ifdef SDL2_RENDERER_DEF
    Uint32 flags = (SDL_GetWindowFlags(m_window) ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!isFullscreen){
        SDL_SetWindowSize(m_window,wWidth,wHeight);
    }
    else{
        SDL_SetWindowFullscreen(m_window,flags);
    }
    #endif
}

void RenderContext::clear() {
  #ifdef SDL2_RENDERER_DEF
  SDL_RenderClear(m_renderer);
  #endif
}

void RenderContext::render() {
  #ifdef SDL2_RENDERER_DEF
  SDL_RenderPresent(m_renderer);
  #endif
}
void RenderContext::load_image(std::string file, std::string id){

  #ifdef SDL2_RENDERER_DEF
  TEXTURE *texture = IMG_LoadTexture(m_renderer, file.c_str());


  if (texture != nullptr){
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    RECT texRect; 
    texRect.x = 0; texRect.y = 0;
    texRect.w = w; texRect.h = h;
    m_textureMap[id] = TextureDesc(texture, texRect);
  }
  #endif
}

#ifdef SDL2_RENDERER_DEF
void RenderContext::draw_image(std::string id, int x, int y){
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = m_textureMap[id].rect.w;
  srcRect.h = destRect.h = m_textureMap[id].rect.h;

  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(m_renderer, m_textureMap[id].texture, &srcRect,
    &destRect, 0, 0, SDL_FLIP_NONE);
}
#endif
