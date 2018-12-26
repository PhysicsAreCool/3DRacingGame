#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 2000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 2000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	bool player1 = true;
	bool TimeStarts = false;

	Stage actual_stage = Stage::first_stage;

	mat4x4 Stage1_mat = mat4x4(
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.5f, 30.0f, 0.0f);

	mat4x4 Stage2_mat = mat4x4(
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		150.0f, 1.5f, 30.0f, 0.0f);

	mat4x4 Stage3_mat = mat4x4(
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		440.0f, 1.5f, 30.0f, 0.0f);

};