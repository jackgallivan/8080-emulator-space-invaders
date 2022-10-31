void draw_video_ram() {
    uint32_t *pix = surf->pixels;

    int i = 0x2400;  // Start of Video RAM
    for (int col = 0; col < SCREEN_WIDTH; col ++) {
        for (int row = SCREEN_HEIGHT; row > 0; row -= 8) {
            for (int j = 0; j < 8; j++) {
                int idx = (row - j) * SCREEN_WIDTH + col;

                if (ram->mem[i] & 1 << j) {
                    pix[idx] = 0xFFFFFF;
                } else {
                    pix[idx] = 0x000000;
                }
            }

            i++;
        }
    }

    if (resizef) {
        winsurf = SDL_GetWindowSurface(win);
    }

    SDL_BlitScaled(surf, NULL, winsurf, NULL);

    // Update window
    if (SDL_UpdateWindowSurface(win)) {
        puts(SDL_GetError());
    }
}

int HandleResize(void *userdata, SDL_Event *ev) {
    if (ev->type == SDL_WINDOWEVENT) {
        if (ev->window.event == SDL_WINDOWEVENT_RESIZED) {
            resizef = 1;
        }
    }

    return 0;  // Ignored
}
}