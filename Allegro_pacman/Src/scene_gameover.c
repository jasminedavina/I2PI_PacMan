#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_game.h"
#include "scene_gameover.h"
#include "scene_settings.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

static ALLEGRO_BITMAP* gameover = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
static int gameoverW;
static int gameoverH;
static Button btn_backMenu;
static Button btn_yes;
static Button btn_no;
int cont = 0;
char score[15];
char topscore[15];
FILE* highscore;

static void init() {
	play_audio(GAMEOVER, music_volume);
	stop_bgm(menuBGM);
	menuBGM = play_bgm(GAMEOVER, music_volume);
	gameover = load_bitmap("Assets/gameover.png");
	gameoverW = al_get_bitmap_width(gameover);
	gameoverH = al_get_bitmap_height(gameover);
	btn_backMenu = button_create(710, SCREEN_H - 175, 50, 50, "Assets/back.png", "Assets/back2.png");
	btn_yes = button_create(SCREEN_W / 2-300, SCREEN_H / 2 , 300, 100, "Assets/yes.png", "Assets/yes2.png");
	btn_no = button_create(SCREEN_W / 2 + 50, SCREEN_H / 2 , 300, 100, "Assets/no.png", "Assets/no2.png");
}
static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	const float scale = 1;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameoverW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameoverH;

	//draw title image
	al_draw_scaled_bitmap(
		gameover,
		0, 0,
		gameoverW, gameoverH,
		offset_w, offset_h,
		gameoverW * scale, gameoverH * scale,
		0
	);
	
	drawButton(btn_backMenu);
	drawButton(btn_yes);
	drawButton(btn_no);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btn_backMenu.hovered = buttonHover(btn_backMenu, mouse_x, mouse_y);
	
	btn_yes.hovered = buttonHover(btn_yes, mouse_x, mouse_y);
	btn_no.hovered = buttonHover(btn_no, mouse_x, mouse_y);
}

static void on_mouse_down() {
	if (btn_backMenu.hovered);
	game_change_scene(scene_menu_create(btn_backMenu));
	if (btn_no.hovered)
	{
		game_change_scene(scene_menu_create(btn_no));
	}
	if (btn_yes.hovered && ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		game_change_scene(scene_main_create(btn_yes));
	}
}

static void destroy() {
	stop_bgm(menuBGM);
	al_destroy_bitmap(btn_backMenu.default_img);
	al_destroy_bitmap(btn_backMenu.hovered_img);
	al_destroy_bitmap(btn_yes.default_img);
	al_destroy_bitmap(btn_yes.hovered_img);
	al_destroy_bitmap(btn_no.default_img);
	al_destroy_bitmap(btn_no.hovered_img);
	al_destroy_bitmap(gameover);
}
// The only function that is shared across files.
Scene scene_gameover_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "gameover";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_move = &on_mouse_move;
	//scene.on_key_down = &on_key_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("gameover scene created");
	return scene;
}