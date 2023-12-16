#pragma once
#include <stdbool.h>
#include "food.h"

typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

typedef struct SnakeSegment {
	int x;
	int y;
	struct SnakeSegment *next;
	struct SnakeSegment *prev;
} SnakeSegment;

typedef struct Snake {
	SnakeSegment *head;
	SnakeSegment *tail;
	int length;
	Direction direction;
} Snake;

Snake *create_snake(int x, int y);
Snake* add_snake_segment(Snake *snake, Direction direction);
void free_snake(Snake *snake);
void move_snake(Snake *snake, Direction direction);
void draw_snake(Snake *snake);
bool check_snake_collision(Snake *snake);
bool check_snake_food_collision(Snake *snake, Food* food);
bool check_out_of_bounds(Snake *snake);
void grow_snake(Snake *snake);
