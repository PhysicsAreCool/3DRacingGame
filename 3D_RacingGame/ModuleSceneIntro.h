#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "Timer.h"


//Walls
#define MAX_WALLS 23
#define WALL_DISTANCE 60
#define WALL_SIZE {30,5,3}

//Columns - first obstacle stage
#define COLUMNS_PER_LINE 5
#define COLUMNS_LINES 10
#define COLUMS_DISTANCE 11

//RAMP - second obstacle
#define	ACCELERATOR_SIZE {1,5,100}
#define BALLS_NUMBER 9
#define PENDULUM1_POSITION STAGE2_POSITION + 30
#define PENDULUM2_POSITION PENDULUM1_POSITION + 50
#define PENDULUM3_POSITION PENDULUM2_POSITION + 50
#define PENDULUM4_POSITION PENDULUM3_POSITION + 50
#define PENDULUM5_POSITION PENDULUM4_POSITION + 50

//SNAKES - Third obstacle
#define SNAKE_SIZE 4
#define SNAKE_RADIUS 6 

//Stages positions
#define STAGE1_POSITION 20
#define STAGE2_POSITION COLUMNS_LINES*COLUMS_DISTANCE+50 + STAGE1_POSITION
#define STAGE3_POSITION PENDULUM5_POSITION + 50

struct PhysBody3D;
struct PhysMotor3D;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void Player_Timer(int milisec); 

public:
	//Cube to simulate a road
	Cube road;

	//Cubes to limitate beggning and end

	Cube front_wall_primitive;
	PhysBody3D* front_wall_body;

	Cube back_wall_primitive;
	PhysBody3D* back_wall_body;

	//Circuit walls
	PhysBody3D* left_walls_bodies[MAX_WALLS];
	Cube		left_walls_primitives[MAX_WALLS];

	PhysBody3D* right_walls_bodies[MAX_WALLS];
	Cube		right_walls_primitives[MAX_WALLS];
	
	//COLUMNS - first obstacle
	PhysBody3D* columns_bodies[COLUMNS_LINES][COLUMNS_PER_LINE];
	Cylinder	columns_primitives[COLUMNS_LINES][COLUMNS_PER_LINE];

	//PENDULUM - second obstacle
	//PENDULUM 1
	PhysBody3D* pendulum1_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum1_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum1_body;
	Cylinder	pendulum1_primitive;

	Cube	pendulum1_accelerator_primitive;
	PhysBody3D* pendulum1_accelerator_body;

	//PENDULUM 2
	PhysBody3D* pendulum2_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum2_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum2_body;
	Cylinder	pendulum2_primitive;

	Cube		pendulum2_accelerator_primitive;
	PhysBody3D* pendulum2_accelerator_body;

	//PENDULUM 3
	PhysBody3D* pendulum3_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum3_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum3_body;
	Cylinder	pendulum3_primitive;

	Cube		pendulum3_accelerator_primitive;
	PhysBody3D* pendulum3_accelerator_body;

	//PENDULUM 4
	PhysBody3D* pendulum4_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum4_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum4_body;
	Cylinder	pendulum4_primitive;

	Cube		pendulum4_accelerator_primitive;
	PhysBody3D* pendulum4_accelerator_body;

	//PENDULUM 5
	PhysBody3D* pendulum5_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum5_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum5_body;
	Cylinder	pendulum5_primitive;
	
	Cube		pendulum5_accelerator_primitive;
	PhysBody3D* pendulum5_accelerator_body;

	//SNAKES - Third obstacle
	Sphere		snake1_primitives[SNAKE_SIZE];
	PhysBody3D* snake1_bodies[SNAKE_SIZE];

	Sphere		snake2_primitives[SNAKE_SIZE];
	PhysBody3D* snake2_bodies[SNAKE_SIZE];

	Sphere		snake3_primitives[SNAKE_SIZE];
	PhysBody3D* snake3_bodies[SNAKE_SIZE];

	Sphere		snake4_primitives[SNAKE_SIZE];
	PhysBody3D* snake4_bodies[SNAKE_SIZE];

	Sphere		snake5_primitives[SNAKE_SIZE];
	PhysBody3D* snake5_bodies[SNAKE_SIZE];

	Timer timer; 

	//Car
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

private:

	//Adding Fx sounds
	uint motor_fx; 

	//Adding sensors
	PhysBody3D* sens_1; 
	Cube* cube_1; 
};
