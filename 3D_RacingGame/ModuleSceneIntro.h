#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2
//Walls
#define MAX_WALLS 30
#define WALL_DISTANCE 60

//Columns (first obstacle stage)
#define COLUMNS_PER_LINE 5
#define COLUMNS 8
#define COLUMS_DISTANCE 11

//

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

public:

	//Circuit walls
	PhysBody3D* left_walls_bodies[MAX_WALLS];
	Cube		left_walls_primitives[MAX_WALLS];

	PhysBody3D* right_walls_bodies[MAX_WALLS];
	Cube		right_walls_primitives[MAX_WALLS];
	
	//First obstacles stage
	PhysBody3D* columns_bodies[COLUMNS][COLUMNS_PER_LINE];
	Cylinder	columns_primitives[COLUMNS][COLUMNS_PER_LINE];

	//Car
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;
};
