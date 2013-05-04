#pragma once
#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
class Audio
{
public:
	Audio;
	static void reproducirM(Mix_Music *);
	static void reproducirS(Mix_Chunk *);
	static void detener();
};

#endif _AUDIO_H_