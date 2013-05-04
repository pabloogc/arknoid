#pragma once

#ifndef _AUDIO_H_
#define _AUDIO_H_

class Audio
{
public:

	enum Sound{
		GAME_START, GAME_WON, GAME_OVER, LIVE_LOST,
		BRICK_BROKEN, BRICK_HIT, PADDLE_HIT, WALL_HIT,
		SOUND_MAX
	};

	enum Music{
		MAIN_MUSIC, MENU_MUSIC, MUSIC_MAX
	};

	static Mix_Chunk *sounds[];
	static Mix_Music *musics[];
	//music tiene plural en ingles? :D

	static Mix_Chunk *curr_sound;
	static Mix_Music *curr_music;

	static void init();
	static void release();

	static void playMusic(Music);
	static void playSound(Sound);

	static void pause();
	static void resume();
	static void haltMusic();
	static void haltSound();
	static void volumenMusic(int);

private:

	Audio();
};

#endif _AUDIO_H_
