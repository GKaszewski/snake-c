#include "particles.h"
#include <stdlib.h>

Particle *create_particle(int x, int y, int dx, int dy, float life, int size, Color color) {
	Particle *particle = malloc(sizeof(Particle));
	particle->x = x;
	particle->y = y;
	particle->size = size;
	particle->color = color;
	particle->dx = dx;
	particle->dy = dy;
	particle->life = life;
	return particle;
}

void free_particle(Particle *particle) {
	if (particle == NULL) return;
	free(particle);
	particle = NULL;
}

void draw_particle(Particle *particle) {
	DrawRectangle(particle->x, particle->y, particle->size, particle->size, particle->color);
}

void update_particle(Particle *particle) {
	if (particle == NULL) return;
	particle->x += particle->dx;
	particle->y += particle->dy;
	particle->life -= 0.01f;

	if (particle->life <= 0) {
		particle = NULL;
		return;
	}

	if (particle->x < 0) {
		particle = NULL;
		return;
	}
	if (particle->x > GetScreenWidth()) {
		particle = NULL;
		return;
	}
	if (particle->y < 0) {
		particle = NULL;
		return;
	}
	if (particle->y > GetScreenHeight()) {
		particle = NULL;
		return;
	}
}


ParticleSystem *init_particle_system(int max_particles) {
	ParticleSystem *particle_system = malloc(sizeof(ParticleSystem));
	particle_system->max_particles = max_particles;
	particle_system->particles = malloc(sizeof(Particle*) * max_particles);
	particle_system->num_particles = 0;
	return particle_system;
}

void free_particle_system(ParticleSystem *particle_system) {
	for (int i = 0; i < particle_system->num_particles; i++) {
		if (particle_system->particles[i] != NULL) {
			free_particle(particle_system->particles[i]);
		}
	}
	particle_system->particles = NULL;
	free(particle_system);
}

void add_particle(ParticleSystem *particle_system, Particle *particle) {
	if (particle_system->num_particles < particle_system->max_particles) {
		particle_system->particles[particle_system->num_particles] = particle;
		particle_system->num_particles++;
	}
}

void remove_particle(ParticleSystem *particle_system, int index) {
	if (particle_system->particles[index] != NULL) {
		free_particle(particle_system->particles[index]);
		particle_system->particles[index] = NULL;
		particle_system->num_particles--;
	}
}

void remove_particle_by_pointer(ParticleSystem *particle_system, Particle *particle) {
	for (int i = 0; i < particle_system->num_particles; i++) {
		if (particle_system->particles[i] == particle) {
			remove_particle(particle_system, i);
			break;
		}
	}
}

void update_particle_system(ParticleSystem *particle_system) {
	for (int i = 0; i < particle_system->num_particles; i++) {
		if (particle_system->particles[i] != NULL) {
			if (particle_system->particles[i]->life <= 0) {
				remove_particle(particle_system, i);
				continue;
			}
			else {
				update_particle(particle_system->particles[i]);
			}
		}
	}
}

void draw_particle_system(ParticleSystem *particle_system) {
	for (int i = 0; i < particle_system->num_particles; i++) {
		if (particle_system->particles[i] != NULL) {
			draw_particle(particle_system->particles[i]);
		}
	}
}

ParticleSystem* create_apple_particles(int x, int y) {
	ParticleSystem *particle_system = init_particle_system(10);
	for (int i = 0; i < 10; i++) {
		int dx = GetRandomValue(-5, 5);
		int dy = GetRandomValue(-5, 5);
		int size = GetRandomValue(1, 5);
		Color color = RED;
		float life = GetRandomValue(10, 100) / 100.0f;
		Particle *particle = create_particle(x, y, dx, dy, life, size, color);
		add_particle(particle_system, particle);
	}
	return particle_system;
}


ParticleSystem* create_snake_particles(int x, int y) {
	ParticleSystem *particle_system = init_particle_system(10);
	for (int i = 0; i < 10; i++) {
		int dx = GetRandomValue(-5, 5);
		int dy = GetRandomValue(-5, 5);
		int size = GetRandomValue(1, 5);
		Color color = GREEN;
		float life = GetRandomValue(10, 100) / 100.0f;
		Particle *particle = create_particle(x, y, dx, dy, life, size, color);
		add_particle(particle_system, particle);
	}
	return particle_system;
}
