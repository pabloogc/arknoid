#include "Audio.h"
#include <iostream>

void static Audio::reproducirM(Mix_Music *music)
{
	Mix_PlayMusic(music, -1);
}

void static Audio::reproducirS(Mix_Chunk *sound)
{
	Mix_PlayChannel(1, sound, 0);
}

void static Audio::detener()
{
	Mix_PauseMusic();
}

