#pragma once
#include <raylib.h>

typedef struct Particle {
	int x;
	int y;
	int dx;
	int dy;
	float life;
	Color color;
	int size;
} Particle;

Particle* init_particle(int x, int y, int dx, int dy, float life, Color color, int size);
void update_particle(Particle* p);
void draw_particle(Particle* p);
void free_particle(Particle* p);

typedef struct ParticleSystem {
	Particle** particles;
	int num_particles;
	int max_particles;
} ParticleSystem;

ParticleSystem* init_particle_system(int max_particles);
void update_particle_system(ParticleSystem* ps);
void draw_particle_system(ParticleSystem* ps);
void free_particle_system(ParticleSystem* ps);
void add_particle(ParticleSystem* ps, Particle* p);
void remove_particle(ParticleSystem* ps, int index);
void remove_particle_by_pointer(ParticleSystem* ps, Particle* p);

ParticleSystem* create_apple_particles(int x, int y);
ParticleSystem* create_snake_particles(int x, int y);


