#pragma once

struct SDL_Window;

class SDLWindow
{
public:
    SDLWindow();
    ~SDLWindow();

    void Update();

    bool GetShouldContinue() const;

private:
    SDL_Window* _window;
    bool _shouldContinue;
};