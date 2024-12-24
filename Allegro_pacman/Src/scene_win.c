#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_win.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

static ALLEGRO_BITMAP* win = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
static int winW;
static int winH;
static Button btn_backMenu;
static Button btn_yes;
static Button btn_no;
char score[15];
char topscore[15];
FILE* highscore;
static void init() {
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic4, music_volume);
	win = load_bitmap("Assets/win.png");
	winW = al_get_bitmap_width(win);
	winH = al_get_bitmap_height(win);
	btn_backMenu = button_create(20, 20, 50, 50, "Assets/back.png", "Assets/back2.png");
	btn_yes = button_create(SCREEN_W / 2 - 300, SCREEN_H / 2 + 120, 300, 100, "Assets/yes.png", "Assets/yes2.png");
	btn_no = button_create(SCREEN_W / 2 + 20, SCREEN_H / 2 +120, 300, 100, "Assets/no.png", "Assets/no2.png");
}
static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	const float scale = 1;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * winW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * winH;

	//draw title image
	al_draw_scaled_bitmap(
		win,
		0, 0,
		winW, winH,
		offset_w, offset_h,
		winW * scale, winH * scale,
		0
	);
	al_draw_textf(menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		SCREEN_H /2- 100,
		ALLEGRO_ALIGN_CENTER,
		"HIGH SCORE : %s", topscore);
	al_draw_textf(menuFont,
		al_map_rgb(0, 0, 0),
		SCREEN_W / 2+3,
		SCREEN_H / 2 - 97,
		ALLEGRO_ALIGN_CENTER,
		"HIGH SCORE : %s", topscore);

	al_draw_text(
		menuFont,
		al_map_rgb(0, 0, 0),
		SCREEN_W / 2,
		SCREEN_H - 290,
		ALLEGRO_ALIGN_CENTER,
		"PLAY AGAIN ?"
	);

	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2+3,
		SCREEN_H - 287,
		ALLEGRO_ALIGN_CENTER,
		"PLAY AGAIN ?"
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
	if (btn_backMenu.hovered && ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
		game_change_scene(scene_menu_create(btn_backMenu));
	if (btn_no.hovered && ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{			
		game_change_scene(scene_menu_create(btn_no));

	}
	if (btn_yes.hovered && ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		game_change_scene(scene_main_create(btn_yes));
	}
}

static void destroy() {
	al_destroy_bitmap(win);
	al_destroy_bitmap(btn_backMenu.default_img);
	al_destroy_bitmap(btn_backMenu.hovered_img);
	al_destroy_bitmap(btn_yes.default_img);
	al_destroy_bitmap(btn_yes.hovered_img);
	al_destroy_bitmap(btn_no.default_img);
	al_destroy_bitmap(btn_no.hovered_img);
	stop_bgm(menuBGM);
}
// The only function that is shared across files.
Scene scene_win_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "win";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_move = &on_mouse_move;
	//scene.on_key_down = &on_key_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("win scene created");
	return scene;
}