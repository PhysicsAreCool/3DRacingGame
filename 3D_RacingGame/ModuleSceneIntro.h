#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "Timer.h"

//Walls
#define MAX_WALLS 30
#define WALL_DISTANCE 60
#define WALL_SIZE {30,5,3}

//Columns - first obstacle stage
#define COLUMNS_PER_LINE 5
#define COLUMNS_LINES 10
#define COLUMS_DISTANCE 11

//RAMP - second obstacle
#define RAMP_SIZE {10,1,20} 
#define BALLS_NUMBER 9
#define PENDULUM1_POSITION STAGE2_POSITION + 30
#define PENDULUM2_POSITION PENDULUM1_POSITION + 60
#define PENDULUM3_POSITION PENDULUM2_POSITION + 60

//Stages positions
#define STAGE1_POSITION 20
#define STAGE2_POSITION COLUMNS_LINES*COLUMS_DISTANCE+50 + STAGE1_POSITION

struct PhysBody3D;
struct PhysMotor3D;

enum class Stage
{
	first_stage, 
	second_stage
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	//Stage 2 - Pendulum
	void RestartPendulum();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void Player_Timer(int milisec); 

public:
	//Cube to simulate a road
	Cube road;

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

	//PENDULUM 2
	PhysBody3D* pendulum2_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum2_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum2_body;
	Cylinder	pendulum2_primitive;

	//PENDULUM 3
	PhysBody3D* pendulum3_balls_bodies[BALLS_NUMBER];
	Sphere		pendulum3_balls_primitives[BALLS_NUMBER];

	PhysBody3D* pendulum3_body;
	Cylinder	pendulum3_primitive;
	

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

	PhysBody3D* sens_2; 
	Cube* cube_2; 
};
