#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	car.base_color = Orange;
	car.car_color = Red; 

	// Car properties ----------------------------------------
	car.chassis_size.Set(3.0f, 0.2f, 5.0f);
	car.chassis_offset.Set(0, 1.3f, 0);

	car.front_chassis.Set(3.0f, 0.6f, 1.2f);
	car.front_chassis_offset.Set(0, 1.7f, 1.85f);

	car.driver_chassis.Set(3.0f, 1.5f, 1.5f); 
	car.driver_chassis_offset.Set(0, 2.15f, 0.5f);

	car.back_chassis.Set(3.0f, 0.6f, 0.2f);
	car.back_chassis_offset.Set(0, 1.7f, -2.4f); 

	car.back_chassis_left.Set(0.2f, 0.6f, 2.2f); 
	car.back_chassis_left_offset.Set(-1.4f, 1.7f, -1.2f);

	car.back_chassis_right.Set(0.2f, 0.6f, 2.2f); 
	car.back_chassis_right_offset.Set(1.4f, 1.7f, -1.2f);

	car.front_wheel_bar.Set(3.0f, 0.2f, 0.2f);
	car.front_wheel_bar_offset.Set(0, 0, 1.5f); 

	car.back_wheel_bar.Set(3, 0.2f, 0.2f); 
	car.back_wheel_bar_offset.Set(0, 0, -1.5f); 

	car.suspension_front_right.Set(0.2f, 1.25f, 0.2f);
	car.suspension_front_right_offset.Set(0.4f, 0.75f, 1.5f); 

	car.suspension_front_left.Set(0.2f, 1.25f, 0.2f); 
	car.suspension_front_left_offset.Set(-0.4f, 0.75f, 1.5f);

	car.suspension_back_right.Set(0.2f, 1.25f, 0.2f);
	car.suspension_back_right_offset.Set(0.4f, 0.75f, -1.5f);

	car.suspension_back_left.Set(0.2f, 1.25f, 0.2f);
	car.suspension_back_left_offset.Set(-0.4f, 0.75f, -1.5f);

	car.mass = 400.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5f;
	car.maxSuspensionForce = 8000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius = 1.0f;
	float wheel_width = 1.2f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	mat4x4 InitialPos_mat = mat4x4(
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 30.0f, 0.0f);

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetTransform(InitialPos_mat.M); 

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	vehicle->SetPos(10000, 0, 10000);
	App->physics->vehicles.clear();

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER; 
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vehicle->vehicle->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
		vehicle->vehicle->getRigidBody()->setAngularVelocity(btVector3(0, 0, 0));

		if (actual_stage == Stage::first_stage)
		{
			vehicle->SetTransform(Stage1_mat.M);
		}
		else if (actual_stage == Stage::second_stage)
		{
			vehicle->SetTransform(Stage2_mat.M); 
		}
		
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	return UPDATE_CONTINUE;
}



