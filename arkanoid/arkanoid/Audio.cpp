#include "Audio.h"
#include <iostream>

void Audio::reproducirM(Mix_Music *music)
{
	Mix_PlayMusic(music, -1);
}

void Audio::reproducirS(Mix_Chunk *sound)
{
	Mix_PlayChannel(1, sound, 0);
}

void Audio::detener()
{
	Mix_PauseMusic();
}
