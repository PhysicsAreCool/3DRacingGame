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

	//Build road
	float road_lenght = 680;
	road.size = {road_lenght,0.1,WALL_DISTANCE };
	road.SetPos(road_lenght/2 - 10,-0.15, WALL_DISTANCE / 2);
	road.color = Color(0.4, 0.4, 0.4);

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

	back_wall_primitive.size = {58,6,6};
	back_wall_primitive.color = Color(1,0,0);
	back_wall_primitive.SetRotation(90,vec3(0,1,0));
	
	back_wall_body = App->physics->AddBody(back_wall_primitive,10000);
	back_wall_body->SetPos(673, 3, 30);

	front_wall_primitive.size = { 58,6,6 };
	front_wall_primitive.color = Color(1, 0, 0);
	front_wall_primitive.SetRotation(90, vec3(0, 1, 0));

	front_wall_body = App->physics->AddBody(back_wall_primitive, 10000);
	front_wall_body->SetPos(-10, 3, 30);

	
	//STAGE 1 - Build columns 
	for (int i = 0; i <  COLUMNS_LINES; ++i)
	{
		for (int j = 0; j < COLUMNS_PER_LINE; ++j)
		{
			columns_primitives[i][j].radius = 3;				
			columns_primitives[i][j].height = 10;

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

			columns_bodies[i][j] = App->physics->AddBody(columns_primitives[i][j],100000);
		}
	}
	
	//STAGE 2 - First pendulum

	//Pendulum
	pendulum1_primitive.color = Color(1, 1, 1);
	pendulum1_primitive.radius = 5;
	pendulum1_primitive.height = 180;
	pendulum1_primitive.SetPos(PENDULUM1_POSITION, 20, 0);
	pendulum1_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum1_body = App->physics->AddBody(pendulum1_primitive, 0.0f); 

	//Accelerator
	pendulum1_accelerator_primitive.size = ACCELERATOR_SIZE;
	pendulum1_accelerator_primitive.SetPos(PENDULUM1_POSITION,35,+50);
	pendulum1_accelerator_body = App->physics->AddBody(pendulum1_accelerator_primitive,0);
	pendulum1_accelerator_body->BodyToSensor(true);
	pendulum1_accelerator_body->collision_listeners.add(App->scene_intro);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum1_balls_primitives[i].radius = 3;
		pendulum1_balls_primitives[i].color = Color(1,1,0);
		pendulum1_balls_primitives[i].SetPos(PENDULUM1_POSITION+10, 30, 6 * i + 6);
		pendulum1_balls_bodies[i] = App->physics->AddBody(pendulum1_balls_primitives[i],10000);
		pendulum1_balls_bodies[i]->collision_listeners.add(App->scene_intro);

		App->physics->AddConstraintP2P(*pendulum1_body, *pendulum1_balls_bodies[i], vec3(-i*6 -6, 0, 0), vec3(0, 16, 0));
	}

	//STAGE 2 - Second Pendulum
	
		pendulum2_primitive.color = Color(1, 0, 0);
		pendulum2_primitive.radius = 5;
		pendulum2_primitive.height = 180;
		pendulum2_primitive.SetPos(PENDULUM2_POSITION, 20, 0);
		pendulum2_primitive.SetRotation(90, vec3(0, 1, 0));
		pendulum2_body = App->physics->AddBody(pendulum2_primitive, 0);

		//Accelerator
		pendulum2_accelerator_primitive.size = ACCELERATOR_SIZE;
		pendulum2_accelerator_primitive.SetPos(PENDULUM2_POSITION, 35, +50);
		pendulum2_accelerator_body = App->physics->AddBody(pendulum2_accelerator_primitive, 0);
		pendulum2_accelerator_body->BodyToSensor(true);
		pendulum2_accelerator_body->collision_listeners.add(App->scene_intro);

		for (int i = 0; i < BALLS_NUMBER; ++i)
		{
			pendulum2_balls_primitives[i].radius = 3;
			pendulum2_balls_primitives[i].color = Color(1, 1, 0);
			pendulum2_balls_primitives[i].SetPos(PENDULUM2_POSITION - 10, 30, 6 * i + 6);
			pendulum2_balls_bodies[i] = App->physics->AddBody(pendulum2_balls_primitives[i], 10000);
			pendulum2_balls_bodies[i]->collision_listeners.add(App->scene_intro);

			App->physics->AddConstraintP2P(*pendulum2_body, *pendulum2_balls_bodies[i], vec3(-i * 6 - 6, 0, 0), vec3(0, 16, 0));
		}
	
	//STAGE 2 - Third pendulum
	pendulum3_primitive.color = Color(1,1,1);
	pendulum3_primitive.radius = 5;
	pendulum3_primitive.height = 180;
	pendulum3_primitive.SetPos(PENDULUM3_POSITION, 20, 0);
	pendulum3_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum3_body = App->physics->AddBody(pendulum3_primitive, 0);

	//Accelerator
	pendulum3_accelerator_primitive.size = ACCELERATOR_SIZE;
	pendulum3_accelerator_primitive.SetPos(PENDULUM3_POSITION, 35, +50);
	pendulum3_accelerator_body = App->physics->AddBody(pendulum3_accelerator_primitive, 0);
	pendulum3_accelerator_body->BodyToSensor(true);
	pendulum3_accelerator_body->collision_listeners.add(App->scene_intro);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum3_balls_primitives[i].radius = 3;
		pendulum3_balls_primitives[i].color = Color(1, 1, 0);
		pendulum3_balls_primitives[i].SetPos(PENDULUM3_POSITION + 10, 30, 6 * i + 6);
		pendulum3_balls_bodies[i] = App->physics->AddBody(pendulum3_balls_primitives[i], 10000);
		pendulum3_balls_bodies[i]->collision_listeners.add(App->scene_intro);

		App->physics->AddConstraintP2P(*pendulum3_body, *pendulum3_balls_bodies[i], vec3(-i * 6 - 6, 0, 0), vec3(0, 16, 0));
	}

	//STAGE 2 - Fourth pendulum
	pendulum4_primitive.color = Color(1, 0, 0);
	pendulum4_primitive.radius = 5;
	pendulum4_primitive.height = 180;
	pendulum4_primitive.SetPos(PENDULUM4_POSITION, 20, 0);
	pendulum4_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum4_body = App->physics->AddBody(pendulum4_primitive, 0);

	//Accelerator
	pendulum4_accelerator_primitive.size = ACCELERATOR_SIZE;
	pendulum4_accelerator_primitive.SetPos(PENDULUM4_POSITION, 35, +50);
	pendulum4_accelerator_body = App->physics->AddBody(pendulum4_accelerator_primitive, 0);
	pendulum4_accelerator_body->BodyToSensor(true);
	pendulum4_accelerator_body->collision_listeners.add(App->scene_intro);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum4_balls_primitives[i].radius = 3;
		pendulum4_balls_primitives[i].color = Color(1, 1, 0);
		pendulum4_balls_primitives[i].SetPos(PENDULUM4_POSITION - 10, 30, 6 * i + 6);
		pendulum4_balls_bodies[i] = App->physics->AddBody(pendulum4_balls_primitives[i], 10000);
		pendulum4_balls_bodies[i]->collision_listeners.add(App->scene_intro);

		App->physics->AddConstraintP2P(*pendulum4_body, *pendulum4_balls_bodies[i], vec3(-i * 6 - 6, 0, 0), vec3(0, 16, 0));
	}

	//STAGE 2 - Fifth pendulum
	pendulum5_primitive.color = Color(1, 1, 1);
	pendulum5_primitive.radius = 5;
	pendulum5_primitive.height = 180;
	pendulum5_primitive.SetPos(PENDULUM5_POSITION, 20, 0);
	pendulum5_primitive.SetRotation(90, vec3(0, 1, 0));
	pendulum5_body = App->physics->AddBody(pendulum5_primitive, 0);

	//Accelerator
	pendulum5_accelerator_primitive.size = ACCELERATOR_SIZE;
	pendulum5_accelerator_primitive.SetPos(PENDULUM5_POSITION, 35, +50);
	pendulum5_accelerator_body = App->physics->AddBody(pendulum5_accelerator_primitive, 0);
	pendulum5_accelerator_body->BodyToSensor(true);
	pendulum5_accelerator_body->collision_listeners.add(App->scene_intro);

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		pendulum5_balls_primitives[i].radius = 3;
		pendulum5_balls_primitives[i].color = Color(1, 1, 0);
		pendulum5_balls_primitives[i].SetPos(PENDULUM5_POSITION + 10, 30, 6 * i + 6);
		pendulum5_balls_bodies[i] = App->physics->AddBody(pendulum5_balls_primitives[i], 10000);
		pendulum5_balls_bodies[i]->collision_listeners.add(App->scene_intro);

		App->physics->AddConstraintP2P(*pendulum5_body, *pendulum5_balls_bodies[i], vec3(-i * 6 - 6, 0, 0), vec3(0, 16, 0));
	}

	//STAGE 3 - Add Snakes

	for (int i = 0; i < SNAKE_SIZE; i++)
	{
		//snake 1
		snake1_primitives[i].radius = SNAKE_RADIUS;
		snake1_primitives[i].color = Color(1,0,0);
		snake1_bodies[i] = App->physics->AddBody(snake1_primitives[i],500);
		if (i > 0)
			App->physics->AddConstraintP2P(*snake1_bodies[i], *snake1_bodies[i-1], vec3(0,0,-SNAKE_RADIUS), vec3(0, 0, SNAKE_RADIUS));
		
		snake1_bodies[i]->SetPos(STAGE3_POSITION + 30, SNAKE_RADIUS + 10, i*SNAKE_RADIUS +15);

		//snake 2
		snake2_primitives[i].radius = SNAKE_RADIUS;
		snake2_primitives[i].color = Color(1, 0, 0);
		snake2_bodies[i] = App->physics->AddBody(snake2_primitives[i], 500);

		if (i > 0)
			App->physics->AddConstraintP2P(*snake2_bodies[i], *snake2_bodies[i - 1], vec3(0, 0, -SNAKE_RADIUS), vec3(0, 0, SNAKE_RADIUS));

		snake2_bodies[i]->SetPos(STAGE3_POSITION + 50, SNAKE_RADIUS + 10, i*SNAKE_RADIUS + 25);

		//snake 3
		snake3_primitives[i].radius = SNAKE_RADIUS;
		snake3_primitives[i].radius = SNAKE_RADIUS;
		snake3_primitives[i].color = Color(1, 0, 0);
		snake3_bodies[i] = App->physics->AddBody(snake3_primitives[i], 500);

		if (i > 0)
			App->physics->AddConstraintP2P(*snake3_bodies[i], *snake3_bodies[i - 1], vec3(0, 0, -SNAKE_RADIUS), vec3(0, 0, SNAKE_RADIUS));

		snake3_bodies[i]->SetPos(STAGE3_POSITION + 70, SNAKE_RADIUS + 10, i*SNAKE_RADIUS + 15);

		//snake 4
		snake4_primitives[i].radius = SNAKE_RADIUS;
		snake4_primitives[i].radius = SNAKE_RADIUS;
		snake4_primitives[i].color = Color(1, 0, 0);
		snake4_bodies[i] = App->physics->AddBody(snake4_primitives[i], 500);

		if (i > 0)
			App->physics->AddConstraintP2P(*snake4_bodies[i], *snake4_bodies[i - 1], vec3(0, 0, -SNAKE_RADIUS), vec3(0, 0, SNAKE_RADIUS));

		snake4_bodies[i]->SetPos(STAGE3_POSITION + 90, SNAKE_RADIUS + 10, i*SNAKE_RADIUS + 25);

		//snake 5
		snake5_primitives[i].radius = SNAKE_RADIUS;
		snake5_primitives[i].radius = SNAKE_RADIUS;
		snake5_primitives[i].color = Color(1, 0, 0);
		snake5_bodies[i] = App->physics->AddBody(snake5_primitives[i], 500);

		if (i > 0)
			App->physics->AddConstraintP2P(*snake5_bodies[i], *snake5_bodies[i - 1], vec3(0, 0, -SNAKE_RADIUS), vec3(0, 0, SNAKE_RADIUS));

		snake5_bodies[i]->SetPos(STAGE3_POSITION +110, SNAKE_RADIUS + 10, i*SNAKE_RADIUS + 15);

	}

	//Audio
	App->audio->SetMusicVolume(); 
	App->audio->SetFxVolume(); 

	motor_fx = App->audio->LoadFx("audio/new_motor.wav");
	engine_acc_fx = App->audio->LoadFx("audio/engine_acceleration.wav"); 
	App->audio->PlayMusic("audio/music.ogg"); 

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//First sensor as a check point after cilinders (stage 1) 
	Cube* Sensor1 = new Cube(1.0f, 5.0f, 50.0f);
	Sensor1->SetPos(150.0f, 2.0f, 30.0f);
	Sensor1->color = White; 
	cube_1 = Sensor1; 
	
	sens_1 = App->physics->AddBody(*cube_1, 0.0f);
	sens_1->BodyToSensor(true); 
	sens_1->collision_listeners.add(this); 

	//Second sensor after ball pendulums 
	Cube* Sensor2 = new Cube(1.0f, 5.0f, 50.0f);
	Sensor2->SetPos(430.0f, 2.0f, 30.0f);
	Sensor2->color = White;
	cube_2 = Sensor2;

	sens_2 = App->physics->AddBody(*cube_2, 0.0f);
	sens_2->BodyToSensor(true);
	sens_2->collision_listeners.add(this);

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

	back_wall_body->GetTransform(&back_wall_primitive.transform);
	back_wall_primitive.Render();

	front_wall_body->GetTransform(&front_wall_primitive.transform);
	front_wall_primitive.Render();
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
	pendulum4_primitive.Render();
	pendulum5_primitive.Render();

	for (int i = 0; i < BALLS_NUMBER; ++i)
	{
		//pendulum 1
		pendulum1_balls_bodies[i]->GetTransform(&pendulum1_balls_primitives[i].transform);
		pendulum1_balls_primitives[i].Render();

		//pendulum 2
		pendulum2_balls_bodies[i]->GetTransform(&pendulum2_balls_primitives[i].transform);
		pendulum2_balls_primitives[i].Render();

		//pendulum 3
		pendulum3_balls_bodies[i]->GetTransform(&pendulum3_balls_primitives[i].transform);
		pendulum3_balls_primitives[i].Render();

		//pendulum 4
		pendulum4_balls_bodies[i]->GetTransform(&pendulum4_balls_primitives[i].transform);
		pendulum4_balls_primitives[i].Render();

		//pendulum 5
		pendulum5_balls_bodies[i]->GetTransform(&pendulum5_balls_primitives[i].transform);
		pendulum5_balls_primitives[i].Render();
	}
  
	for (int i = 0; i < SNAKE_SIZE; i++)
	{
		snake1_bodies[i]->GetTransform(&snake1_primitives[i].transform);
		snake2_bodies[i]->GetTransform(&snake2_primitives[i].transform);
		snake3_bodies[i]->GetTransform(&snake3_primitives[i].transform);
		snake4_bodies[i]->GetTransform(&snake4_primitives[i].transform);
		snake5_bodies[i]->GetTransform(&snake5_primitives[i].transform);

		snake1_primitives[i].Render();
		snake2_primitives[i].Render();
		snake3_primitives[i].Render();
		snake4_primitives[i].Render();
		snake5_primitives[i].Render();
	}

	//Render sensors 
	if (App->physics->debug)
	{
		cube_1->Render(); 
		cube_2->Render(); 
	}

	//Which player wins
	if (TotalTime_p1 < TotalTime_p2)
		wins_p1 = true;
	else
		wins_p1 = false; 

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sens_1)
	{
		if (App->player->player1)
		{
			App->player->actual_stage = Stage::second_stage;
		}
		else
		{
			App->player2->actual_stage = Stage::second_stage; 
		}
	}
	else if (body1 == sens_2 && App->player->player1 == true)
	{
		TotalTime_p1 = timer.Read();
		App->player->CleanUp();
		App->player->enabled = false;

		App->player2->enabled = true;
		App->player2->Start();
		App->player->TimeStarts = false; 
		App->player->player1 = false;
	}
	else if(body1 == sens_2 && App->player->player1 == false)
	{
		TotalTime_p2 = timer.Read(); 
		timer.Stop(); 
		game_ends = true; 
	}

	if (body1 == pendulum1_accelerator_body ||
		body1 == pendulum3_accelerator_body ||
		body1 == pendulum5_accelerator_body)
		body2->Push(60000, 60000, 0);
	else if (body1 == pendulum2_accelerator_body || 
		body1 == pendulum4_accelerator_body )
		body2->Push(-60000, 60000, 0);
}

void ModuleSceneIntro::Player_Timer(int milisec)
{

	if (App->player->TimeStarts == false)
		timer.Start(); 

	char title[150]; 

	int sec = milisec / 1000.0f; //from milisecond to sec
	int min = sec / 60.0f; //from seconds to minutes 
	int hour = min / 60.0f; //from minutes to hours

	int sec_print = sec;

	if (min > 0)
		sec_print -= min * 60;
	if (!game_ends)
	{
		if (hour >= 10 && min >= 10 && sec_print >= 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: %i : %i : %i", hour, min, sec_print);
		}
		else if (hour < 10 && min >= 10 && sec_print >= 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: 0%i : %i : %i", hour, min, sec_print);
		}
		else if (hour >= 10 && min < 10 && sec_print >= 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: %i : 0%i : %i", hour, min, sec_print);
		}
		else if (hour >= 10 && min >= 10 && sec_print < 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: %i : %i : 0%i", hour, min, sec_print);
		}
		else if (hour >= 10 && min < 10 && sec_print < 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: %i : 0%i : 0%i", hour, min, sec_print);
		}
		else if (hour < 10 && min >= 10 && sec_print < 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: 0%i : %i : 0%i", hour, min, sec_print);
		}
		else if (hour < 10 && min < 10 && sec_print >= 10) {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: 0%i : 0%i : %i", hour, min, sec_print);
		}
		else {
			sprintf_s(title, " Monster Truck Obstacle Race | TIME: 0%i : 0%i : 0%i", hour, min, sec_print);
		}

		App->window->SetTitle(title);
	}
	else
	{
		if (wins_p1)
		{
			if (hour >= 10 && min >= 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: %i : %i : %i", hour, min, sec_print);
			}
			else if (hour < 10 && min >= 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: 0%i : %i : %i", hour, min, sec_print);
			}
			else if (hour >= 10 && min < 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: %i : 0%i : %i", hour, min, sec_print);
			}
			else if (hour >= 10 && min >= 10 && sec_print < 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: %i : %i : 0%i", hour, min, sec_print);
			}
			else if (hour >= 10 && min < 10 && sec_print < 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: %i : 0%i : 0%i", hour, min, sec_print);
			}
			else if (hour < 10 && min >= 10 && sec_print < 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: 0%i : %i : 0%i", hour, min, sec_print);
			}
			else if (hour < 10 && min < 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: 0%i : 0%i : %i", hour, min, sec_print);
			}
			else {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 1 WINS!!! TIME: 0%i : 0%i : 0%i", hour, min, sec_print);
			}

			App->window->SetTitle(title);
		}
		else
		{
			if (hour >= 10 && min >= 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: %i : %i : %i", hour, min, sec_print);
			}
			else if (hour < 10 && min >= 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: 0%i : %i : %i", hour, min, sec_print);
			}
			else if (hour >= 10 && min < 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: %i : 0%i : %i", hour, min, sec_print);
			}
			else if (hour >= 10 && min >= 10 && sec_print < 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: %i : %i : 0%i", hour, min, sec_print);
			}
			else if (hour >= 10 && min < 10 && sec_print < 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: %i : 0%i : 0%i", hour, min, sec_print);
			}
			else if (hour < 10 && min >= 10 && sec_print < 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: 0%i : %i : 0%i", hour, min, sec_print);
			}
			else if (hour < 10 && min < 10 && sec_print >= 10) {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: 0%i : 0%i : %i", hour, min, sec_print);
			}
			else {
				sprintf_s(title, " Monster Truck Obstacle Race | PLAYER 2 WINS!!! TIME: 0%i : 0%i : 0%i", hour, min, sec_print);
			}

			App->window->SetTitle(title);
		}
	}
}
