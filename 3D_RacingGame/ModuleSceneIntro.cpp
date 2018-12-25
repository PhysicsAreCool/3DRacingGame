#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Build road
	float road_lenght = 1000;
	road.size = {road_lenght,0.1,WALL_DISTANCE };
	road.SetPos(road_lenght/2,-1, WALL_DISTANCE / 2);
	road.color = Color(0.50, 0.50, 0.50);

	//Build walls
	for (int i = 0; i < MAX_WALLS; ++i)
	{
		//Left walls
		left_walls_primitives[i].size = WALL_SIZE;
		left_walls_primitives[i].SetPos(left_walls_primitives[i].size.x*i,0, 0);

		if (i % 2 == 0)
			left_walls_primitives[i].color = Color(1,0,0);
		else 
			left_walls_primitives[i].color = Color(1, 1, 1);

		left_walls_bodies[i] = App->physics->AddBody(left_walls_primitives[i],1000000);

		//Right walls
		right_walls_primitives[i].size = WALL_SIZE;
		right_walls_primitives[i].SetPos(left_walls_primitives[i].size.x*i, 00, WALL_DISTANCE);

		if (i % 2 == 0)
			right_walls_primitives[i].color = Color(1, 0, 0);
		else
			right_walls_primitives[i].color = Color(1, 1, 1);

		right_walls_bodies[i] = App->physics->AddBody(right_walls_primitives[i], 1000000);
	}

	//STAGE 1 - Build columns 
	for (int i = 0; i <  COLUMNS_LINES; ++i)
	{
		for (int j = 0; j < COLUMNS_PER_LINE; ++j)
		{
			columns_primitives[i][j].radius = 3;				
			columns_primitives[i][j].height = 5;

			//Position of the columns
			if (i%2==0)
				columns_primitives[i][j].SetPos(STAGE1_POSITION + COLUMS_DISTANCE*i+10 ,5, COLUMS_DISTANCE*j+ COLUMS_DISTANCE);
			else 
				columns_primitives[i][j].SetPos(STAGE1_POSITION + COLUMS_DISTANCE * i +10, 5, COLUMS_DISTANCE * j + COLUMS_DISTANCE/2);

			//Color
			if (i%2==0)
				columns_primitives[i][j].color = Color(1, 0, 0);
			else 
				columns_primitives[i][j].color = Color(1, 1, 1);

			columns_primitives[i][j].SetRotation(90, {0,0,1});	

			columns_bodies[i][j] = App->physics->AddBody(columns_primitives[i][j],0);
		}
	}
	
	//STAGE 2 - First pendulum

	pendulum1_primitive.color = Color(1, 1, 1);
	pendulum1_primitive.radius = 5;
	pendulum1_primitive.height = 180;
	pendulum1_primitive.SetPos(PENDULUM1_POSITION, 30, 0);
	pendulum1_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum1_body = App->physics->AddBody(pendulum1_primitive, 0);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum1_balls_primitives[i].radius = 3;
		pendulum1_balls_primitives[i].color = Color(1,1,0);
		pendulum1_balls_primitives[i].SetPos(PENDULUM1_POSITION + 200,5,6*i + 6);
		pendulum1_balls_bodies[i] = App->physics->AddBody(pendulum1_balls_primitives[i],1000);

		App->physics->AddConstraintP2P(*pendulum1_body, *pendulum1_balls_bodies[i], vec3(-i*6 -6, 0, 0), vec3(0, 26, 0));
	}

	//STAGE 2 - Second Pendulum

	pendulum2_primitive.color = Color(1,0, 0);
	pendulum2_primitive.radius = 5;
	pendulum2_primitive.height = 180;
	pendulum2_primitive.SetPos(PENDULUM2_POSITION, 30, 0);
	pendulum2_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum2_body = App->physics->AddBody(pendulum2_primitive, 0);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum2_balls_primitives[i].radius = 3;
		pendulum2_balls_primitives[i].color = Color(1, 1, 0);
		pendulum2_balls_primitives[i].SetPos(PENDULUM2_POSITION + 200, 100, 6 * i + 6);
		pendulum2_balls_bodies[i] = App->physics->AddBody(pendulum2_balls_primitives[i], 1000);

		App->physics->AddConstraintP2P(*pendulum2_body, *pendulum2_balls_bodies[i], vec3(-i * 6 - 6, 0, 0), vec3(0, 26, 0));
	}

	//STAGE 3 - Third pendulum
	pendulum3_primitive.color = Color(1,1,1);
	pendulum3_primitive.radius = 5;
	pendulum3_primitive.height = 180;
	pendulum3_primitive.SetPos(PENDULUM3_POSITION, 30, 0);
	pendulum3_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum3_body = App->physics->AddBody(pendulum3_primitive, 0);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum3_balls_primitives[i].radius = 3;
		pendulum3_balls_primitives[i].color = Color(1, 1, 0);
		pendulum3_balls_primitives[i].SetPos(PENDULUM3_POSITION + 600, 100, 6 * i + 6);
		pendulum3_balls_bodies[i] = App->physics->AddBody(pendulum3_balls_primitives[i], 1000);

		App->physics->AddConstraintP2P(*pendulum3_body, *pendulum3_balls_bodies[i], vec3(-i * 6 - 6, 0, 0), vec3(0, 26, 0));
	}

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.color = Color(1,1,1);
	p.Render();

	//Draw road
	road.Render();

	//Draw and transfrom walls
	for (int i = 0; i < MAX_WALLS; ++i)
	{
		//Left walls
		left_walls_bodies[i]->GetTransform(&left_walls_primitives[i].transform);
		left_walls_primitives[i].Render();

		//Right walls
		right_walls_bodies[i]->GetTransform(&right_walls_primitives[i].transform);
		right_walls_primitives[i].Render();
	}

	//STAGE 1 - Draw and transform columns
	for (int i = 0; i < COLUMNS_LINES; ++i)
	{
		for (int j = 0; j < COLUMNS_PER_LINE; ++j)
		{
			columns_bodies[i][j]->GetTransform(&columns_primitives[i][j].transform);
			columns_primitives[i][j].Render();
		}
	}

	//STAGE 2 - Draw and transform balls & pendulum
	pendulum1_primitive.Render();
	pendulum2_primitive.Render();
	pendulum3_primitive.Render();

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum1_balls_bodies[i]->GetTransform(&pendulum1_balls_primitives[i].transform);
		pendulum1_balls_primitives[i].Render();
	}

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum2_balls_bodies[i]->GetTransform(&pendulum2_balls_primitives[i].transform);
		pendulum2_balls_primitives[i].Render();
	}

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum3_balls_bodies[i]->GetTransform(&pendulum3_balls_primitives[i].transform);
		pendulum3_balls_primitives[i].Render();
	}

	//STAGE 2 - Spawn balls
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		RestartPendulum();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::RestartPendulum()
{
	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum1_balls_bodies[i]->SetPos(PENDULUM1_POSITION + 500, 10, 6 * i + 6);
		pendulum2_balls_bodies[i]->SetPos(PENDULUM2_POSITION + 600, 30, 6 * i + 6);
		pendulum3_balls_bodies[i]->SetPos(PENDULUM3_POSITION + 70, 80, 6 * i + 6);
	}
}