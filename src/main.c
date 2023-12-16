#include <raylib.h>
#include <stdlib.h>
#include "snake.h"
#include "food.h"
#include "consts.h"
#include "particles.h"

int main(int argc, char **argv) {
	InitWindow(450, 450, "snake");
	SetTargetFPS(60);
	InitAudioDevice();
	Snake *snake = create_snake(10, 10);
	Food *food = create_food(200, 200);
	double game_tick_time = 0.1;
	double time_since_last_tick = 0.0;
	double max_tick_time = 0.05;
	int score = 0;
	int high_score = 0;
	Wave eat_sound_wave = LoadWave("assets/sfx_twoTone.ogg");
	Wave die_sound_wave = LoadWave("assets/sfx_zap.ogg");
	Sound eat_sound = LoadSoundFromWave(eat_sound_wave);
	Sound die_sound = LoadSoundFromWave(die_sound_wave);

	ParticleSystem* apple_particles = NULL;
	ParticleSystem* death_particles = NULL;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		if (IsKeyPressed(KEY_UP)) {
			snake->direction = UP;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			snake->direction = DOWN;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			snake->direction = LEFT;
		}
		if (IsKeyPressed(KEY_RIGHT)) {
			snake->direction = RIGHT;
		}

		if (game_tick_time < max_tick_time) {
			game_tick_time = max_tick_time;
		}

		if (time_since_last_tick > game_tick_time) {
			if (check_snake_food_collision(snake, food)) {
				game_tick_time -= 0.005;
				score++;
				if (score > high_score) {
					high_score = score;
				}
				apple_particles = create_apple_particles(food->x, food->y);
				move_food(food);
				grow_snake(snake);
				PlaySound(eat_sound);
			}

			if (check_snake_collision(snake)) {
				death_particles = create_snake_particles(snake->head->x, snake->head->y);
				free_snake(snake);
				free_food(food);
				snake = create_snake(10, 10);
				food = create_food(20, 20);
				score = 0;
				game_tick_time = 0.1;
				PlaySound(die_sound);
			}

			if (check_out_of_bounds(snake)) {
				death_particles = create_snake_particles(snake->head->x, snake->head->y);
				free_snake(snake);
				free_food(food);
				snake = create_snake(10, 10);
				food = create_food(20, 20);
				score = 0;
				game_tick_time = 0.1;
				PlaySound(die_sound);
			}

			move_snake(snake, snake->direction);
			time_since_last_tick = 0.0;
		} else {
			time_since_last_tick += GetFrameTime();
		}

		if (apple_particles != NULL) {
			update_particle_system(apple_particles);
			draw_particle_system(apple_particles);
		}

		if (death_particles != NULL) {
			update_particle_system(death_particles);
			draw_particle_system(death_particles);
		}

		// draw grid
		for (int i = 0; i < GetScreenWidth(); i += SNAKE_SIZE) {
			DrawLine(i, 0, i, GetScreenHeight(), LIGHTGRAY);
			for (int j = 0; j < GetScreenHeight(); j += SNAKE_SIZE) {
				DrawLine(0, j, GetScreenWidth(), j, LIGHTGRAY);
			}
		}
		
		DrawText(TextFormat("%02i", score), (GetScreenWidth() / 2) - 10, 10, 20, GRAY);
		DrawText(TextFormat("%02i", high_score), (GetScreenWidth() / 2) - 10, 30, 20, GRAY);
		draw_snake(snake);
		draw_food(food);
		EndDrawing();
	}
	UnloadSound(eat_sound);
	UnloadSound(die_sound);
	UnloadWave(eat_sound_wave);
	UnloadWave(die_sound_wave);
	free_snake(snake);
	free_food(food);
	free_particle_system(apple_particles);
	free_particle_system(death_particles);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}