// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.


// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.

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
#include "scene_gameover.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
#include "scene_settings.h"

static int settingW;
static int settingH;
static ALLEGRO_BITMAP* setting = NULL;
static Button btn_backMenu;
static Button btn_music1;
static Button btn_music2;
static Button btn_nomusic;
static Button btn_plusMusic;
static Button btn_plusSFX;
static Button btn_minusMusic;
static Button btn_minusSFX;
static Button btn_map1;
static Button btn_map2;
static Button btn_volmusic0;
static Button btn_volmusic1;
static Button btn_volmusic2;
static Button btn_volmusic3;
static Button btn_volmusic4;
static Button btn_volmusic5;
static Button btn_volmusic6;
static Button btn_volmusic7;
static Button btn_volmusic8;
static Button btn_volmusic9;
static Button btn_volmusic10;
static Button btn_volSFX0;
static Button btn_volSFX1;
static Button btn_volSFX2;
static Button btn_volSFX3;
static Button btn_volSFX4;
static Button btn_volSFX5;
static Button btn_volSFX6;
static Button btn_volSFX7;
static Button btn_volSFX8;
static Button btn_volSFX9;
static Button btn_volSFX10;
static ALLEGRO_SAMPLE_ID menuBGM;
int music = 1;
int map = 1;
static void init() {
	if (music == 1)
	{
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic1, music_volume);
	}
	else if (music == 2)
	{
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic2, music_volume);
	}
	else if (music == 0)
	{
		stop_bgm(menuBGM);
	}
	setting = load_bitmap("Assets/setting.png");
	settingW = al_get_bitmap_width(setting);
	settingH = al_get_bitmap_height(setting);
	btn_backMenu= button_create(20, 730, 50, 50, "Assets/back.png", "Assets/back2.png");
	btn_music1 = button_create(SCREEN_W / 2 - 295, 360, 180, 70, "Assets/kpop.png", "Assets/kpop2.png");
	btn_music2 = button_create(SCREEN_W / 2 - 100, 360, 180, 70, "Assets/jpop.png", "Assets/jpop2.png");
	btn_nomusic = button_create(SCREEN_W / 2 + 95, 360, 180, 70, "Assets/none.png", "Assets/none2.png");
	btn_plusMusic = button_create(SCREEN_W - 185, 210, 50, 50, "Assets/plusMusic.png", "Assets/plusMusic2.png");
	btn_minusMusic = button_create(SCREEN_W / 2 - 95, 210, 50, 50, "Assets/minusMusic.png", "Assets/minusMusic2.png");
	btn_plusSFX = button_create(SCREEN_W - 185, 530, 50, 50, "Assets/plusSFX.png", "Assets/plusSFX2.png");
	btn_minusSFX = button_create(SCREEN_W / 2 - 95, 530, 50, 50, "Assets/minusSFX.png", "Assets/minusSFX2.png");
	btn_map1 = button_create(SCREEN_W / 2 - 100, 440, 180, 70, "Assets/one.png", "Assets/one2.png");
	btn_map2 = button_create(SCREEN_W / 2 + 95, 440, 180, 70, "Assets/two.png", "Assets/two2.png");
	btn_volmusic0 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol0.png", "Assets/vol0.png");
	btn_volmusic1 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol1.png", "Assets/vol1.png");
	btn_volmusic2 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol2.png", "Assets/vol2.png");
	btn_volmusic3 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol3.png", "Assets/vol3.png");
	btn_volmusic4 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol4.png", "Assets/vol4.png");
	btn_volmusic5 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol5.png", "Assets/vol5.png");
	btn_volmusic6 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol6.png", "Assets/vol6.png");
	btn_volmusic7 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol7.png", "Assets/vol7.png");
	btn_volmusic8 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol8.png", "Assets/vol8.png");
	btn_volmusic9 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol9.png", "Assets/vol9.png");
	btn_volmusic10 = button_create(SCREEN_W / 2 - 25, 218, 225, 33, "Assets/vol10.png", "Assets/vol10.png");
	btn_volSFX0 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol0SFX.png", "Assets/vol0SFX.png");
	btn_volSFX1 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol1SFX.png", "Assets/vol1SFX.png");
	btn_volSFX2 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol2SFX.png", "Assets/vol2SFX.png");
	btn_volSFX3 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol3SFX.png", "Assets/vol3SFX.png");
	btn_volSFX4 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol4SFX.png", "Assets/vol4SFX.png");
	btn_volSFX5 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol5SFX.png", "Assets/vol5SFX.png");
	btn_volSFX6 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol6SFX.png", "Assets/vol6SFX.png");
	btn_volSFX7 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol7SFX.png", "Assets/vol7SFX.png");
	btn_volSFX8 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol8SFX.png", "Assets/vol8SFX.png");
	btn_volSFX9 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol9SFX.png", "Assets/vol9SFX.png");
	btn_volSFX10 = button_create(SCREEN_W / 2 - 25, 538, 225, 33, "Assets/vol10SFX.png", "Assets/vol10SFX.png");
}
static void draw(void ){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	const float scale = 1;
	const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * settingW;
	const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * settingH;

	//draw title image
	al_draw_scaled_bitmap(
		setting,
		0, 0,
		settingW, settingH,
		offset_w, offset_h,
		settingW * scale, settingH * scale,
		0
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2, 150,
		ALLEGRO_ALIGN_CENTER,
		"MUSIC : ");
	
	drawButton(btn_backMenu);
	drawButton(btn_music1);
	drawButton(btn_music2);
	drawButton(btn_nomusic);
	drawButton(btn_plusMusic);
	drawButton(btn_minusMusic);
	drawButton(btn_plusSFX);
	drawButton(btn_minusSFX);
	drawButton(btn_map1);
	drawButton(btn_map2);
	if (music_volume == 0)
	{
		drawButton(btn_volmusic0);
	}
	else if (music_volume == 1)
	{
		drawButton(btn_volmusic1);
	}
	else if (music_volume == 2)
	{
		drawButton(btn_volmusic2);
	}
	else if (music_volume == 3)
	{
		drawButton(btn_volmusic3);
	}
	else if (music_volume == 4)
	{
		drawButton(btn_volmusic4);
	}
	else if (music_volume == 5)
	{
		drawButton(btn_volmusic5);
	}
	else if (music_volume == 6)
	{
		drawButton(btn_volmusic6);
	}
	else if (music_volume == 7)
	{
		drawButton(btn_volmusic7);
	}
	else if (music_volume == 8)
	{
		drawButton(btn_volmusic8);
	}
	else if (music_volume == 9)
	{
		drawButton(btn_volmusic9);
	}
	else if (music_volume == 10)
	{
		drawButton(btn_volmusic10);
	}

	if (effect_volume == 0)
	{
		drawButton(btn_volSFX0);
	}
	else if (effect_volume == 1)
	{
		drawButton(btn_volSFX1);
	}
	else if (effect_volume == 2)
	{
		drawButton(btn_volSFX2);
	}
	else if (effect_volume == 3)
	{
		drawButton(btn_volSFX3);
	}
	else if (effect_volume == 4)
	{
		drawButton(btn_volSFX4);
	}
	else if (effect_volume == 5)
	{
		drawButton(btn_volSFX5);
	}
	else if (effect_volume == 6)
	{
		drawButton(btn_volSFX6);
	}
	else if (effect_volume == 7)
	{
		drawButton(btn_volSFX7);
	}
	else if (effect_volume == 8)
	{
		drawButton(btn_volSFX8);
	}
	else if (effect_volume == 9)
	{
		drawButton(btn_volSFX9);
	}
	else if (effect_volume == 10)
	{
		drawButton(btn_volSFX10);
	}
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	[HACKATHON 3-7]
	//	TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btn_backMenu.hovered = buttonHover(btn_backMenu, mouse_x, mouse_y);
	btn_music1.hovered = buttonHover(btn_music1, mouse_x, mouse_y);
	btn_music2.hovered = buttonHover(btn_music2, mouse_x, mouse_y);
	btn_nomusic.hovered = buttonHover(btn_nomusic, mouse_x, mouse_y);
	btn_plusMusic.hovered = buttonHover(btn_plusMusic, mouse_x, mouse_y);
	btn_minusMusic.hovered = buttonHover(btn_minusMusic, mouse_x, mouse_y);
	btn_plusSFX.hovered = buttonHover(btn_plusSFX, mouse_x, mouse_y);
	btn_minusSFX.hovered = buttonHover(btn_minusSFX, mouse_x, mouse_y);
	btn_map1.hovered = buttonHover(btn_map1, mouse_x, mouse_y);
	btn_map2.hovered = buttonHover(btn_map2, mouse_x, mouse_y);

}

static void on_mouse_down() {
	if (btn_backMenu.hovered)
	{
		game_change_scene(scene_menu_create(btn_backMenu));
	}
	else if (btn_music1.hovered)
	{
		music = 1;
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic1, music_volume);
	}
	else if (btn_music2.hovered)
	{
		music = 2;
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic2, music_volume);
		
	}
	else if (btn_nomusic.hovered)
	{
		music = 0;
		stop_bgm(menuBGM);
	}

	if (btn_plusMusic.hovered)
	{
		if (music_volume >= 0 && music_volume <10)
		{
			music_volume += 1;
			if (music == 1)
			{
				stop_bgm(menuBGM);
				menuBGM = play_bgm(themeMusic1, music_volume);
			}
			else if (music == 2)
			{
				stop_bgm(menuBGM);
				menuBGM = play_bgm(themeMusic2, music_volume);
			}
			else if(music ==0)
			{
				stop_bgm(menuBGM);
			}
			
		}
	}
	else if (btn_minusMusic.hovered)
	{
		if (music_volume <= 10 && music_volume > 0)
		{
			music_volume -= 1;
			if (music == 1)
			{
				stop_bgm(menuBGM);
				menuBGM = play_bgm(themeMusic1, music_volume);
			}
			else if (music == 2)
			{
				stop_bgm(menuBGM);
				menuBGM = play_bgm(themeMusic2, music_volume);
			}
			else if (music == 0)
			{
				stop_bgm(menuBGM);
			}
		}
	}

	if (btn_plusSFX.hovered)
	{
		if (effect_volume >= 0 && effect_volume < 10)
		{
			effect_volume += 1;
		}
	}
	else if (btn_minusSFX.hovered)
	{
		if (effect_volume <= 10 && effect_volume > 0)
		{
			effect_volume -= 1; 
		}
	}

	if (btn_map1.hovered)
	{
		map = 1;
	}
	else if (btn_map2.hovered)
	{
		map = 2;
	}
}

static void destroy() {
	stop_bgm(menuBGM);
	al_destroy_bitmap(btn_backMenu.default_img);
	al_destroy_bitmap(btn_backMenu.hovered_img);
	al_destroy_bitmap(btn_map1.default_img);
	al_destroy_bitmap(btn_map1.hovered_img);
	al_destroy_bitmap(btn_map2.default_img);
	al_destroy_bitmap(btn_map2.hovered_img);
	al_destroy_bitmap(btn_minusMusic.default_img);
	al_destroy_bitmap(btn_minusMusic.hovered_img);
	al_destroy_bitmap(btn_minusSFX.default_img);
	al_destroy_bitmap(btn_minusSFX.hovered_img);
	al_destroy_bitmap(btn_music1.default_img);
	al_destroy_bitmap(btn_music1.hovered_img);
	al_destroy_bitmap(btn_music2.default_img);
	al_destroy_bitmap(btn_music2.hovered_img);
	al_destroy_bitmap(btn_nomusic.default_img);
	al_destroy_bitmap(btn_nomusic.hovered_img);
	al_destroy_bitmap(btn_plusMusic.default_img);
	al_destroy_bitmap(btn_plusMusic.hovered_img);
	al_destroy_bitmap(btn_plusSFX.default_img);
	al_destroy_bitmap(btn_plusSFX.hovered_img);
	al_destroy_bitmap(btn_volmusic0.default_img);
	al_destroy_bitmap(btn_volmusic0.hovered_img);
	al_destroy_bitmap(btn_volmusic1.default_img);
	al_destroy_bitmap(btn_volmusic1.hovered_img);
	al_destroy_bitmap(btn_volmusic2.default_img);
	al_destroy_bitmap(btn_volmusic2.hovered_img);
	al_destroy_bitmap(btn_volmusic3.default_img);
	al_destroy_bitmap(btn_volmusic3.hovered_img);
	al_destroy_bitmap(btn_volmusic4.default_img);
	al_destroy_bitmap(btn_volmusic4.hovered_img);
	al_destroy_bitmap(btn_volmusic5.default_img);
	al_destroy_bitmap(btn_volmusic5.hovered_img);
	al_destroy_bitmap(btn_volmusic6.default_img);
	al_destroy_bitmap(btn_volmusic6.hovered_img);
	al_destroy_bitmap(btn_volmusic7.default_img);
	al_destroy_bitmap(btn_volmusic7.hovered_img);
	al_destroy_bitmap(btn_volmusic8.default_img);
	al_destroy_bitmap(btn_volmusic8.hovered_img);
	al_destroy_bitmap(btn_volmusic9.default_img);
	al_destroy_bitmap(btn_volmusic9.hovered_img);
	al_destroy_bitmap(btn_volSFX0.default_img);
	al_destroy_bitmap(btn_volSFX0.hovered_img);
	al_destroy_bitmap(btn_volSFX1.default_img);
	al_destroy_bitmap(btn_volSFX1.hovered_img);
	al_destroy_bitmap(btn_volSFX10.default_img);
	al_destroy_bitmap(btn_volSFX10.hovered_img);
	al_destroy_bitmap(btn_volSFX2.default_img);
	al_destroy_bitmap(btn_volSFX2.hovered_img);
	al_destroy_bitmap(btn_volSFX3.default_img);
	al_destroy_bitmap(btn_volSFX3.hovered_img);
	al_destroy_bitmap(btn_volSFX4.default_img);
	al_destroy_bitmap(btn_volSFX4.hovered_img);
	al_destroy_bitmap(btn_volSFX5.default_img);
	al_destroy_bitmap(btn_volSFX5.hovered_img);
	al_destroy_bitmap(btn_volSFX6.default_img);
	al_destroy_bitmap(btn_volSFX6.hovered_img);
	al_destroy_bitmap(btn_volSFX7.default_img);
	al_destroy_bitmap(btn_volSFX7.hovered_img);
	al_destroy_bitmap(btn_volSFX8.default_img);
	al_destroy_bitmap(btn_volSFX8.hovered_img);
	al_destroy_bitmap(btn_volSFX9.default_img);
	al_destroy_bitmap(btn_volSFX9.hovered_img);
	al_destroy_bitmap(setting);

}
// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_move = &on_mouse_move;
	//scene.on_key_down = &on_key_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}