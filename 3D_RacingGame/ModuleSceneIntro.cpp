#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	//First sensor as a check point
	Cube* Sensor1 = new Cube(10, 5, 1); 
	Sensor1->SetPos(0, 1, 20);
	Sensor1->color = White; 
	cube_1 = Sensor1; 
	

	sens_1 = App->physics->AddBody(*cube_1, 0.0f);
	sens_1->BodyToSensor(true); 
	sens_1->collision_listeners.add(this); 

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
	Player_Timer(timer.Read()); 

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//Render sensors 
	if (App->physics->debug)
	{
		cube_1->Render(); 
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sens_1)
	{
		if (App->player->change)
		{
			App->player->CleanUp();
			App->player->enabled = false;

			App->player2->enabled = true;
			App->player2->Start();

			App->player->change = false; 
		}
	}

}

void ModuleSceneIntro::Player_Timer(int milisec)
{

	char title[100]; 

	int sec = milisec / 1000.0f; //from milisecond to sec
	int min = sec / 60.0f; //from seconds to minutes 
	int hour = min / 60.0f; //from minutes to hours

	int sec_print = sec;

	if (min > 0)
		sec_print -= min * 60;

	if (hour >= 10 && min >= 10 && sec_print >= 10) {
		sprintf_s(title, " Time: %i : %i : %i", hour, min, sec_print);
	}
	else if (hour < 10 && min >= 10 && sec_print >= 10) {
		sprintf_s(title, " Time: 0%i : %i : %i", hour, min, sec_print);
	}
	else if (hour >= 10 && min < 10 && sec_print >= 10) {
		sprintf_s(title, " Time: %i : 0%i : %i", hour, min, sec_print);
	}
	else if (hour >= 10 && min >= 10 && sec_print < 10) {
		sprintf_s(title, " Time: %i : %i : 0%i", hour, min, sec_print);
	}
	else if (hour >= 10 && min < 10 && sec_print < 10) {
		sprintf_s(title, " Time: %i : 0%i : 0%i", hour, min, sec_print);
	}
	else if (hour < 10 && min >= 10 && sec_print < 10) {
		sprintf_s(title, " Time: 0%i : %i : 0%i", hour, min, sec_print);
	}
	else if (hour < 10 && min < 10 && sec_print >= 10) {
		sprintf_s(title, " Time: 0%i : 0%i : %i", hour, min, sec_print);
	}
	else {
		sprintf_s(title, " Time: 0%i : 0%i : 0%i", hour, min, sec_print);
	}

	App->window->SetTitle(title);
}

