#include "stdafx.h"
#include "Audio.h"

using namespace std;

Mix_Chunk *Audio::sounds[SOUND_MAX];
Mix_Music *Audio::musics[MUSIC_MAX];
//music tiene plural en ingles? :D

Mix_Chunk *Audio::curr_sound;
Mix_Music *Audio::curr_music;

void Audio::init(){
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(22050, AUDIO_U8, 1, 1024);

	//Cargar el resto de la musica
	sounds[Sound::BRICK_BROKEN] = Mix_LoadWAV("ladrillo_roto.wav");
	sounds[Sound::PAUSE] = Mix_LoadWAV("PAUSE.wav");//SOLO UN SEGUNDO DE SILENCIO
	sounds[Sound::GAME_OVER] = Mix_LoadWAV("GAME_OVER.wav");
	musics[Music::MAIN_MUSIC] = Mix_LoadMUS("MUSIC.wav");
}

void Audio::playSound(Sound s)
{
	curr_sound = sounds[s];
	Mix_PlayChannel(-1, curr_sound, 1);
}

void Audio::playMusic(Music m)
{
	curr_music = musics[m];
	Mix_PlayMusic(curr_music, -1);
}

void Audio::pause()
{
	Mix_PauseMusic();
}

void Audio::resume()
{
	Mix_ResumeMusic();
}

void Audio::haltMusic()
{
	Mix_HaltMusic();
}

void Audio::haltSound()
{
	Mix_HaltChannel(0);
}

void Audio::release()
{
	for(int i = 0; i < Sound::SOUND_MAX; i++)
		Mix_FreeChunk(sounds[i]);

	for(int i = 1; i < Music::MUSIC_MAX; i++)
		Mix_FreeMusic(musics[i]);

	SDL_Quit();
}

void Audio::volumenMusic(int volumen)
{
	if (volumen > MIX_MAX_VOLUME)
		volumen = MIX_MAX_VOLUME;

	else if (volumen < 0)
		volumen = 0;

	Mix_VolumeMusic(volumen);
}