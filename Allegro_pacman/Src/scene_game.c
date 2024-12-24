#define _CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include "game.h"
#include "shared.h"
#include "utility.h"
#include "scene_game.h"
#include "scene_gameover.h"
#include "scene_menu_object.h"
#include "scene_win.h"
#include "scene_settings.h"
#include "scene_menu.h"
#include "pacman_obj.h"
#include "ghost.h"
#include "map.h"
#include <stdio.h>

// [HACKATHON 2-0]
// Just modify the GHOST_NUM to 1
#define GHOST_NUM 4 
/* global variables*/
extern const uint32_t GAME_TICK_CD;
extern uint32_t GAME_TICK;
extern ALLEGRO_TIMER* game_tick_timer;
static ALLEGRO_SAMPLE_ID menuBGM;
int game_main_Score = 0;
int game_high_Score = 0;
int timerGhost = 0;
int pause = 0;
int text_timer = 0;
extern int beans_num;
bool game_over = false;
bool win = false;
extern FILE* highscore = NULL;
extern char score[8];
extern char topscore[8];

/* Internal variables*/
static ALLEGRO_TIMER* power_up_timer;
static ALLEGRO_TIMER* bean_K_timer;
static ALLEGRO_TIMER* bean_S_timer;
static ALLEGRO_TIMER* bean_L_timer;
static ALLEGRO_SAMPLE_ID menuBGM;
static ALLEGRO_SAMPLE_ID slowBean;
static ALLEGRO_SAMPLE_ID speedBean;
static ALLEGRO_SAMPLE_ID frozenBean;
static ALLEGRO_SAMPLE_ID powerBean;
static const int text_duration = 3;
static Pacman* pman;
static Map* basic_map;
static Ghost** ghosts;
int bomb = 0; 
extern int map;
bool debug_mode = false;
bool cheat_mode = false;

/* Declare static function prototypes */
static void init(void);
static void step(void);
static void checkItem(void);
static void status_update(void);
static void update(void);
static void draw(void);
static void printinfo(void);
static void destroy(void);
static void on_key_down(int key_code);
static void render_init_screen(void);
static void draw_hitboxes(void);


static void init(void) {
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic3, 0.5);
	highscore = fopen("Assets/highscore.txt", "r");
	fgets(topscore, 8, highscore);
	game_over = false;
	game_main_Score = 0;
	// create map
	//basic_map = create_map(NULL);
	// [TODO]
	// Create map from .txt file and design your own map !!
	if (map == 1)
	{
		basic_map = create_map("Assets/map_custom.txt");
	}
	else if (map == 2)
	{
		basic_map = create_map("Assets/map_nthu.txt");
	}
	//basic_map = create_map("Assets/map_nthu.txt");
	if (!basic_map) {
		game_abort("error on creating map");
	}
	// create pacman
	pman = pacman_create();
	if (!pman) {
		game_abort("error on creating pacamn\n");
	}

	// allocate ghost memory
	// [HACKATHON 2-1]
	// TODO: Allocate dynamic memory for ghosts array.

	ghosts = (Ghost*)malloc(sizeof(Ghost) * GHOST_NUM);

	if (!ghosts) {
		game_log("We haven't create any ghosts!\n");
	}
	else {
		// [HACKATHON 2-2]
		// TODO: create a ghost.
		// Try to look the definition of ghost_create and figure out what should be placed here.
		for (int i = 0; i < GHOST_NUM; i++) {
			if (i % 4 == 0)
			{
				ghosts[i] = ghost_create(0);
			}
			else if (i % 4 == 1)
			{
				ghosts[i] = ghost_create(1);
			}
			else if (i % 4 == 2)
			{
				ghosts[i] = ghost_create(2);
			}
			else if (i % 4 == 3)
			{
				ghosts[i] = ghost_create(3);
			}
			/*
			game_log("creating ghost %d\n", i);
			ghosts[i] = ghost_create(i);
			if (!ghosts[i])
				game_abort("error creating ghost\n");
			*/
		}
	}
	GAME_TICK = 0;

	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick / sec
	bean_K_timer = al_create_timer(1.0f);
	bean_S_timer = al_create_timer(1.0f);
	bean_L_timer = al_create_timer(1.0f);
	
	if (!power_up_timer)
		game_abort("Error on create timer\n");
	return;
}

static void step(void) {
	if (pman->objData.moveCD > 0)
		pman->objData.moveCD -= pman->speed;
	for (int i = 0; i < GHOST_NUM; i++) {
		// important for movement
		if (ghosts[i]->objData.moveCD > 0)
			ghosts[i]->objData.moveCD -= ghosts[i]->speed;
	}
}
static void checkItem(void) {
	int Grid_x = pman->objData.Coord.x, Grid_y = pman->objData.Coord.y;
	if (Grid_y >= basic_map->row_num - 1 || Grid_y <= 0 || Grid_x >= basic_map->col_num - 1 || Grid_x <= 0)
		return;
	// [HACKATHON 1-3]
	// TODO: check which item you are going to eat and use `pacman_eatItem` to deal with it.

	switch (basic_map->map[Grid_y][Grid_x])
	{
	case '.':
		pacman_eatItem(pman, basic_map->map[Grid_y][Grid_x]);
		basic_map->map[Grid_y][Grid_x] = ' ';
		basic_map->beansCount--;
		beans_num--;
		if (beans_num <= 0)
		{
			win = true;
		}
		game_main_Score += 5;
		break;
	case 'P':
		pacman_eatItem(pman, basic_map->map[Grid_y][Grid_x]);
		basic_map->map[Grid_y][Grid_x] = ' ';
		game_main_Score += 50;
		//buat timer pas power bean dimakan pacman
		if (al_get_timer_started(power_up_timer))
		{
			al_set_timer_count(power_up_timer, 0);
			powerBean = play_audio(powerbean, effect_volume);
		}
		else
		{
			al_start_timer(power_up_timer);
			powerBean = play_audio(powerbean, effect_volume);
		}
		timerGhost = 0;
		//buat balikin ghost
		for (int i = 0; i < GHOST_NUM; i++)
		{
			ghost_toggle_FLEE(ghosts[i], true);
		}
		break;
	case 'K':
		pacman_eatItem(pman, basic_map->map[Grid_y][Grid_x]);
		basic_map->map[Grid_y][Grid_x] = ' ';
		game_main_Score += 50;
		//buat timer pas power bean dimakan pacman
		if (al_get_timer_started(bean_K_timer))
		{
			al_set_timer_count(bean_K_timer, 0);
			speedBean = play_audio(speedbean, effect_volume);
		}
		else
		{
			al_start_timer(bean_K_timer);
			speedBean = play_audio(speedbean, effect_volume);
		}
		pman->speed = 4.8;
		break;
	case 'S':
		pacman_eatItem(pman, basic_map->map[Grid_y][Grid_x]);
		basic_map->map[Grid_y][Grid_x] = ' ';
		game_main_Score += 50;
		//buat timer pas power bean dimakan pacman
		if (al_get_timer_started(bean_S_timer))
		{
			al_set_timer_count(bean_S_timer, 0);
			slowBean = play_audio(slowbean, effect_volume);
		}
		else
		{
			al_start_timer(bean_S_timer);
			slowBean = play_audio(slowbean, effect_volume);
		}
		pman->speed = 1;
		break;
	case 'L':
		pacman_eatItem(pman, basic_map->map[Grid_y][Grid_x]);
		basic_map->map[Grid_y][Grid_x] = ' ';
		bomb = 1;
		text_timer = 1;
		game_main_Score -= 10;
		
		//buat timer pas power bean dimakan pacman
		if (al_get_timer_started(bean_L_timer))
		{
			al_set_timer_count(bean_L_timer, 0);
			frozenBean = play_audio(blackbean, effect_volume);
		}
		else
		{
			al_start_timer(bean_L_timer);
			frozenBean = play_audio(blackbean, effect_volume);
		}
		
		break;
	default:
		break;
	}

	// [HACKATHON 1-4]
	// erase the item you eat from map
	// be careful no erasing the wall block.
	/*
		basic_map->map...;
	*/
}
static void status_update(void) {
	RecArea drawpacman = getDrawArea(pman->objData, GAME_TICK_CD);
	for (int i = 0; i < GHOST_NUM; i++) {
		RecArea drawpacman = getDrawArea(pman->objData, GAME_TICK_CD);
		if (ghosts[i]->status == GO_IN)
			continue;
		// [TODO]
		// use `getDrawArea(..., GAME_TICK_CD)` and `RecAreaOverlap(..., GAME_TICK_CD)` functions to detect
		// if pacman and ghosts collide with each other.
		// And perform corresponding operations.
		// [NOTE]
		// You should have some branch here if you want to implement power bean mode. 
		// Uncomment Following Code

		if (!cheat_mode && RecAreaOverlap(getDrawArea(pman->objData, GAME_TICK_CD), getDrawArea(ghosts[i]->objData, GAME_TICK_CD)))
		{
			if (ghosts[i]->status != FLEE) {
			game_log("collide with ghost\n");
			al_rest(1.0);
			pacman_die();
			game_over = true;
			al_start_timer(pman->death_anim_counter);
			break;
			}

			else
			{
				ghost_collided(ghosts[i]);
				game_main_Score += 100;
			}
		}
		
	}
}

static void update(void) {
	
	if (game_over) {
		bomb = 0;
		text_timer = 0;
		stop_bgm(menuBGM);
		if (atoi(topscore) <= atoi(score))
		{
			highscore = fopen("Assets/highscore.txt", " w");
			fputs(score, highscore);
			fclose(highscore);
		}
		al_start_timer(pman->death_anim_counter);
		if (al_get_timer_count(pman->death_anim_counter) > 65)
		{
			al_rest(1);
			game_over = false;
			beans_num = 0;
			win = false;
			game_change_scene(scene_gameover_create());
		}
		
		/*
			[TODO]
			start pman->death_anim_counter and schedule a game-over event (e.g change scene to menu) after Pacman's death animation finished
			game_change_scene(...);
		*/
		return;
	}
	if (win)
	{
		stop_bgm(menuBGM);
		menuBGM = play_audio(WINSOUND, music_volume);
		game_log("tes\n");
		if (atoi(topscore) <= atoi(score))
		{
			highscore = fopen("Assets/highscore.txt", " w");
			fputs(score, highscore);
			fclose(highscore);
		}
		al_rest(2);
		game_over = false;
		win = false;
		game_change_scene(scene_win_create());
	}

	//balik blinking lagi
	if (al_get_timer_count(power_up_timer) > 8)
	{
		timerGhost = 1;
	}

	//stop blinking 
	if (al_get_timer_count(power_up_timer) > 10)
	{
		al_stop_timer(power_up_timer);
		al_set_timer_count(power_up_timer, 0);
		timerGhost = 0;
		for (int i = 0; i < GHOST_NUM; i++)
		{
			ghost_toggle_FLEE(ghosts[i], false);
		}
	}
	//power bean K speed up
	if (al_get_timer_count(bean_K_timer) > 7)
	{
		al_stop_timer(bean_K_timer);
		al_set_timer_count(bean_K_timer, 0);
		pman->speed = 2;
	}
	//power bean S slow down
	if (al_get_timer_count(bean_S_timer) > 7)
	{
		al_stop_timer(bean_K_timer);
		al_set_timer_count(bean_K_timer, 0);
		pman->speed = 2;
	}
	//power bean L stop pacman
	if (al_get_timer_count(bean_L_timer) > 2)
	{
		al_stop_timer(bean_L_timer);
		al_set_timer_count(bean_L_timer, 0);
		bomb = 0;
		text_timer = 0;
		pman->speed = 2;
	}
	
	step();
	checkItem();
	status_update();
	if (pause == 0)
	{
		pacman_move(pman, basic_map);
		for (int i = 0; i < GHOST_NUM; i++)
			ghosts[i]->move_script(ghosts[i], basic_map, pman);
	}
	
}

static void draw(void) {

	al_clear_to_color(al_map_rgb(255, 255, 255));
	sprintf_s(score, 8, "%d", game_main_Score);
	//	[TODO]
	//	Draw scoreboard, something your may need is sprinf();
	
		al_draw_textf(menuFont,
			al_map_rgb(86, 70, 86),
			SCREEN_W / 2,
			SCREEN_H - 100,
			ALLEGRO_ALIGN_CENTER,
			"SCORE : %d", game_main_Score);

		al_draw_textf(menuFont,
			al_map_rgb(86, 70, 86),
			SCREEN_W /2,
			SCREEN_H - 50,
			ALLEGRO_ALIGN_CENTER,
			"HIGH SCORE : %s", topscore);

	draw_map(basic_map);
	
	pacman_draw(pman);
	if (game_over)
		return;
	// no drawing below when game over
	for (int i = 0; i < GHOST_NUM; i++)
		ghost_draw(ghosts[i]);

	//debugging mode
	if (debug_mode) {
		draw_hitboxes();
	}

	if (pause == 1)
	{
		al_draw_filled_circle(400, 400, 200, al_map_rgba(230, 100, 137, 175));
		al_draw_text(menuFont,
			al_map_rgb(255, 255, 255),
			SCREEN_W / 2,
			SCREEN_H /2-25,
			ALLEGRO_ALIGN_CENTER,
			"PRESS \" SPACEBAR \"");
		al_draw_text(menuFont,
			al_map_rgb(255, 255, 255),
			SCREEN_W / 2,
			SCREEN_H / 2 + 25,
			ALLEGRO_ALIGN_CENTER,
			"TO CONTINUE");
		al_draw_text(menuFont,
			al_map_rgb(0, 0, 0),
			SCREEN_W / 2,
			SCREEN_H / 2 - 22,
			ALLEGRO_ALIGN_CENTER,
			"PRESS \" SPACEBAR \"");
		al_draw_text(menuFont,
			al_map_rgb(0, 0, 0),
			SCREEN_W / 2,
			SCREEN_H / 2 + 22,
			ALLEGRO_ALIGN_CENTER,
			"TO CONTINUE");
	}

	if (text_timer == 1)
	{
		al_draw_text(menuFont,
			al_map_rgb(178, 28, 13),
			SCREEN_W / 2,
			SCREEN_H / 2,
			ALLEGRO_ALIGN_CENTER,
			"YOU CAN'T MOVE NOW!");
		al_draw_text(menuFont,
			al_map_rgb(0, 0, 0),
			SCREEN_W / 2,
			SCREEN_H / 2 + 5,
			ALLEGRO_ALIGN_CENTER,
			"YOU CAN'T MOVE NOW!");
	}
	
}


static void draw_hitboxes(void) {
	RecArea pmanHB = getDrawArea(pman->objData, GAME_TICK_CD);
	al_draw_rectangle(
		pmanHB.x, pmanHB.y,
		pmanHB.x + pmanHB.w, pmanHB.y + pmanHB.h,
		al_map_rgb_f(1.0, 0.0, 0.0), 2
	);

	for (int i = 0; i < GHOST_NUM; i++) {
		RecArea ghostHB = getDrawArea(ghosts[i]->objData, GAME_TICK_CD);
		al_draw_rectangle(
			ghostHB.x, ghostHB.y,
			ghostHB.x + ghostHB.w, ghostHB.y + ghostHB.h,
			al_map_rgb_f(1.0, 0.0, 0.0), 2
		);
	}

}

static void printinfo(void) {
	game_log("pacman:\n");
	game_log("coord: %d, %d\n", pman->objData.Coord.x, pman->objData.Coord.y);
	game_log("PreMove: %d\n", pman->objData.preMove);
	game_log("NextTryMove: %d\n", pman->objData.nextTryMove);
	game_log("Speed: %f\n", pman->speed);
}


static void destroy(void) {
	/*
		[TODO]
		free map array, Pacman and ghosts
	
	delete_map(basic_map);
	for (int i = 0; i < GHOST_NUM; i++)
	{
		ghost_destroy(ghosts[i]);
	}
	//free(ghosts);
	//pacman_destroy(pman);
	*/
	al_destroy_timer(power_up_timer);
	al_destroy_timer(bean_K_timer);
	al_destroy_timer(bean_L_timer);
	al_destroy_timer(bean_S_timer);
	stop_bgm(menuBGM);
	
}

static void on_key_down(int key_code) {
	switch (key_code)
	{
		// [HACKATHON 1-1]	
		// TODO: Use allegro pre-defined enum ALLEGRO_KEY_<KEYNAME> to controll pacman movement
		// we provided you a function `pacman_NextMove` to set the pacman's next move direction.
	case ALLEGRO_KEY_UP:
		pacman_NextMove(pman, UP);
		break;
	case ALLEGRO_KEY_LEFT:
		pacman_NextMove(pman, LEFT);
		break;
	case ALLEGRO_KEY_DOWN:
		pacman_NextMove(pman, DOWN);
		break;
	case ALLEGRO_KEY_RIGHT:
		pacman_NextMove(pman, RIGHT);
		break;
	case ALLEGRO_KEY_Q:
		win = true;
		break;
	case ALLEGRO_KEY_ESCAPE:
		game_change_scene(scene_menu_create(ALLEGRO_KEY_ESCAPE));
		break;
	case ALLEGRO_KEY_SPACE:
		if (pause == 0)
		{
			pause = 1;
		}
		else if (pause == 1)
		{
			pause = 0;
		}

		break;
	case ALLEGRO_KEY_C:
		cheat_mode = !cheat_mode;
		if (cheat_mode)
			printf("cheat mode on\n");
		else
			printf("cheat mode off\n");
		break;
	case ALLEGRO_KEY_G:
		debug_mode = !debug_mode;
		break;

	default:
		break;
	}

}


static void render_init_screen(void) {
	al_clear_to_color(al_map_rgb(255, 255, 255));

	draw_map(basic_map);
	pacman_draw(pman);
	for (int i = 0; i < GHOST_NUM; i++) {
		ghost_draw(ghosts[i]);
	}
	al_draw_text(
		menuFont,
		al_map_rgb(0, 0, 0),
		402, 22,
		ALLEGRO_ALIGN_CENTER,
		"DON'T LET BLACK BEANS STOP YOU!"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(242, 158, 85),
		400, 20,
		ALLEGRO_ALIGN_CENTER,
		"DON'T LET BLACK BEANS STOP YOU!"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(0, 0 , 0),
		400, 403,
		ALLEGRO_ALIGN_CENTER,
		"READY!"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 0),
		400, 400,
		ALLEGRO_ALIGN_CENTER,
		"READY!"
	);
	al_draw_text(menuFont,
		al_map_rgb(86, 70, 86),
		SCREEN_W/2,
		SCREEN_H - 50,
		ALLEGRO_ALIGN_CENTER,
		"\" ESC \" TO BACK");
	al_flip_display();
	al_rest(3.0);

}
// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_main_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start";
	scene.initialize = &init;
	scene.update = &update;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Start scene created");
	return scene;
}
