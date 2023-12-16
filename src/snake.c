#include "snake.h"
#include "consts.h"
#include <stdlib.h>
#include <math.h>
#include <raylib.h>

int min(int a, int b) {
	return a < b ? a : b;
}

Snake *create_snake(int x, int y) {
	Snake *snake = malloc(sizeof(Snake));
	snake->head = malloc(sizeof(SnakeSegment));
	snake->head->x = x;
	snake->head->y = y;
	snake->head->next = NULL;
	snake->tail = snake->head;
	snake->length = 1;
	snake->direction = RIGHT;
	return snake;
}


void free_snake(Snake *snake) {
	SnakeSegment *current = snake->head;
	while (current != NULL) {
		SnakeSegment *next = current->next;
		free(current);
		current = next;
	}
}

Snake *add_snake_segment(Snake* snake, Direction direction) {
	SnakeSegment *new_segment = malloc(sizeof(SnakeSegment));
	new_segment->next = NULL;
	new_segment->prev = snake->tail;
	snake->tail->next = new_segment;
	snake->tail = new_segment;
	snake->length++;

	switch (direction) {
		case UP:
			new_segment->x = snake->tail->x;
			new_segment->y = snake->tail->y + SNAKE_SIZE;
			break;
		case DOWN:
			new_segment->x = snake->tail->x;
			new_segment->y = snake->tail->y - SNAKE_SIZE;
			break;
		case LEFT:
			new_segment->x = snake->tail->x + SNAKE_SIZE;
			new_segment->y = snake->tail->y;
			break;
		case RIGHT:
			new_segment->x = snake->tail->x - SNAKE_SIZE;
			new_segment->y = snake->tail->y;
			break;
	}
	return snake;
}

void move_snake(Snake *snake, Direction direction) {
    snake->direction = direction;
	int new_x = snake->head->x;
	int new_y = snake->head->y;
	switch (direction) {
		case UP:
			new_y -= SNAKE_SIZE;
			break;
		case DOWN:
			new_y += SNAKE_SIZE;
			break;
		case LEFT:
			new_x -= SNAKE_SIZE;
			break;
		case RIGHT:
			new_x += SNAKE_SIZE;
			break;
	}
    SnakeSegment *current_segment = snake->tail;
    while (current_segment != snake->head) {
        current_segment->x = current_segment->prev->x;
        current_segment->y = current_segment->prev->y;
        current_segment = current_segment->prev;
    }
    snake->head->x = new_x;
    snake->head->y = new_y;
}

void draw_snake(Snake *snake) {
	SnakeSegment *current = snake->head;
	int i = 0;
	while (current != NULL) {
		if (i % 2 == 0) {
			DrawRectangle(current->x, current->y, SNAKE_SIZE, SNAKE_SIZE, GREEN);
		} else {
			DrawRectangle(current->x, current->y, SNAKE_SIZE, SNAKE_SIZE, DARKGREEN);
		}
		current = current->next;
		i++;
	}
}

bool check_snake_collision(Snake *snake) {
	SnakeSegment *current = snake->head->next;
	while (current != NULL) {
		if (snake->head->x < current->x + SNAKE_SIZE &&
			snake->head->x + SNAKE_SIZE > current->x &&
			snake->head->y < current->y + SNAKE_SIZE &&
			snake->head->y + SNAKE_SIZE > current->y) {
			return true;
		}
		current = current->next;
	}

	return false;
}

bool check_snake_food_collision(Snake *snake, Food* food) {
	if (snake->head->x < food->x + FOOD_SIZE &&
		snake->head->x + SNAKE_SIZE > food->x &&
		snake->head->y < food->y + FOOD_SIZE &&
		snake->head->y + SNAKE_SIZE > food->y) {
		return true;
	}

	return false;
}

bool check_out_of_bounds(Snake *snake) {
	if (snake->head->x < 0 || snake->head->x > GetScreenWidth() ||
		snake->head->y < 0 || snake->head->y > GetScreenHeight()) {
		return true;
	}

	return false;
}

void grow_snake(Snake *snake) {
	snake = add_snake_segment(snake, snake->direction);
}