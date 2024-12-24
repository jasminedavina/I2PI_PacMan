// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
#include "scene_menu.h"
#include "scene_settings.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_SAMPLE* themeMusic1 = NULL;
ALLEGRO_SAMPLE* themeMusic2 = NULL;
ALLEGRO_SAMPLE* themeMusic3 = NULL;
ALLEGRO_SAMPLE* themeMusic4 = NULL;
ALLEGRO_SAMPLE* PACMAN_MOVESOUND = NULL;
ALLEGRO_SAMPLE* GAMEOVER = NULL;
ALLEGRO_SAMPLE* WINSOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND = NULL;
ALLEGRO_SAMPLE* blackbean = NULL;
ALLEGRO_SAMPLE* powerbean = NULL;
ALLEGRO_SAMPLE* slowbean = NULL;
ALLEGRO_SAMPLE* speedbean = NULL;
ALLEGRO_FONT* menuFont = NULL;
ALLEGRO_SAMPLE* winSound = NULL;
int fontSize = 30;
float music_volume = 1;
float effect_volume = 1;
bool gameDone = false;

/*
	A way to accelerate is load assets once.
	And delete them at the end.
	This method does provide you better management of memory.
	
*/
void shared_init(void) {
	
	menuFont = load_font("Assets/Minecraft.ttf", fontSize);
	themeMusic1 = load_audio("Assets/Music/Power.mp3");
	themeMusic2 = load_audio("Assets/Music/original_theme.mp3");
	themeMusic3 = load_audio("Assets/Music/original_themeDu.mp3");
	PACMAN_MOVESOUND = load_audio("Assets/Music/pacman_chompOld.ogg");
	GAMEOVER = load_audio("Assets/Music/gameover.ogg");
	WINSOUND = load_audio("Assets/Music/win.ogg");
	blackbean = load_audio("Assets/Music/blacksound.mp3");
	powerbean = load_audio("Assets/Music/pacman_eatfruit.ogg");
	slowbean = load_audio("Assets/Music/pacman_eatghost.ogg");
	speedbean = load_audio("Assets/Music/speed.mp3");
	PACMAN_DEATH_SOUND = load_audio("Assets/Music/pacman_death.ogg");
	themeMusic4 = load_audio("Assets/Music/pacman_intermission.ogg");
}

void shared_destroy(void) {

	al_destroy_font(menuFont);
	al_destroy_sample(themeMusic1);
	al_destroy_sample(themeMusic2);
	al_destroy_sample(themeMusic3);
	al_destroy_sample(PACMAN_MOVESOUND);
	al_destroy_sample(PACMAN_DEATH_SOUND);
}