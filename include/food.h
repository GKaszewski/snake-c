#pragma once

typedef struct Food {
	int x;
	int y;
} Food;

Food* create_food(int x, int y);
void free_food(Food* food);
void draw_food(Food* food);
void move_food(Food* food);