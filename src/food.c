#include "food.h"
#include "consts.h"
#include <raylib.h>
#include <stdlib.h>

Food *create_food(int x, int y) {
	Food *food = malloc(sizeof(Food));
	food->x = x;
	food->y = y;
	return food;
}

void free_food(Food *food) {
	free(food);
}

void draw_food(Food *food) {
	DrawRectangle(food->x, food->y, FOOD_SIZE, FOOD_SIZE, RED);
}

void move_food(Food *food) {
	food->x = GetRandomValue(10, MAX_MAP_WIDTH);
	food->y = GetRandomValue(10, MAX_MAP_HEIGHT);

	food->x = food->x - (food->x % SNAKE_SIZE);
	food->y = food->y - (food->y % SNAKE_SIZE);
}