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

	//Build walls
	for (int i = 0; i < MAX_WALLS; ++i)
	{
		//Left walls
		left_walls_primitives[i].size = {50,3,3};
		left_walls_primitives[i].SetPos(50*i,0, 0);

		if (i % 2 == 0)
			left_walls_primitives[i].color = Color(1,0,0);
		else 
			left_walls_primitives[i].color = Color(1, 1, 1);

		left_walls_bodies[i] = App->physics->AddBody(left_walls_primitives[i],1000000);

		//Right walls
		right_walls_primitives[i].size = { 50,3,3 };
		right_walls_primitives[i].SetPos(50 * i, 00, WALL_DISTANCE);

		if (i % 2 == 0)
			right_walls_primitives[i].color = Color(1, 0, 0);
		else
			right_walls_primitives[i].color = Color(1, 1, 1);

		right_walls_bodies[i] = App->physics->AddBody(right_walls_primitives[i], 1000000);
	}

	//Build columns
	for (int i = 0; i <  COLUMNS; ++i)
	{
		for (int j = 0; j < COLUMNS_PER_LINE; ++j)
		{
			columns_primitives[i][j].radius = 3;				
			columns_primitives[i][j].height = 5;

			//Position of the columns
			if (i%2==0)
				columns_primitives[i][j].SetPos(COLUMS_DISTANCE*i+10 ,5, COLUMS_DISTANCE*j+ COLUMS_DISTANCE);
			else 
				columns_primitives[i][j].SetPos(COLUMS_DISTANCE * i +10, 5, COLUMS_DISTANCE * j + COLUMS_DISTANCE/2);

			//Color
				columns_primitives[i][j].color = Color(0.85, 0.85, 0.85);

			columns_primitives[i][j].SetRotation(90, {0,0,1});	

			columns_bodies[i][j] = App->physics->AddBody(columns_primitives[i][j],10000);
		}
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
	p.Render();

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

	for (int i = 0; i < COLUMNS; ++i)
	{
		for (int j = 0; j < COLUMNS_PER_LINE; ++j)
		{
			columns_bodies[i][j]->GetTransform(&columns_primitives[i][j].transform);
			columns_primitives[i][j].Render();
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}