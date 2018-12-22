#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	//PRINCIPAL CHASSIS
	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	//FRONT CHASSIS 
	Cube front_chassis(info.front_chassis.x, info.front_chassis.y, info.front_chassis.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front_chassis.transform);
	btVector3 front_chassis_offset(info.front_chassis_offset.x, info.front_chassis_offset.y, info.front_chassis_offset.z);
	front_chassis_offset = front_chassis_offset.rotate(q.getAxis(), q.getAngle());

	front_chassis.transform.M[12] += front_chassis_offset.getX();
	front_chassis.transform.M[13] += front_chassis_offset.getY();
	front_chassis.transform.M[14] += front_chassis_offset.getZ();

	//DRIVER CHASSIS 
	Cube driver_chassis(info.driver_chassis.x, info.driver_chassis.y, info.driver_chassis.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&driver_chassis.transform);
	btVector3 driver_chassis_offset(info.driver_chassis_offset.x, info.driver_chassis_offset.y, info.driver_chassis_offset.z);
	driver_chassis_offset = driver_chassis_offset.rotate(q.getAxis(), q.getAngle());

	driver_chassis.transform.M[12] += driver_chassis_offset.getX();
	driver_chassis.transform.M[13] += driver_chassis_offset.getY();
	driver_chassis.transform.M[14] += driver_chassis_offset.getZ();

	//BACK CHASSIS 
	Cube back_chassis(info.back_chassis.x, info.back_chassis.y, info.back_chassis.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back_chassis.transform);
	btVector3 back_chassis_offset(info.back_chassis_offset.x, info.back_chassis_offset.y, info.back_chassis_offset.z);
	back_chassis_offset = back_chassis_offset.rotate(q.getAxis(), q.getAngle());

	back_chassis.transform.M[12] += back_chassis_offset.getX();
	back_chassis.transform.M[13] += back_chassis_offset.getY();
	back_chassis.transform.M[14] += back_chassis_offset.getZ();

	//BACK CHASSIS LEFT
	Cube back_chassis_left(info.back_chassis_left.x, info.back_chassis_left.y, info.back_chassis_left.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back_chassis_left.transform);
	btVector3 back_chassis_left_offset(info.back_chassis_left_offset.x, info.back_chassis_left_offset.y, info.back_chassis_left_offset.z);
	back_chassis_left_offset = back_chassis_left_offset.rotate(q.getAxis(), q.getAngle());

	back_chassis_left.transform.M[12] += back_chassis_left_offset.getX();
	back_chassis_left.transform.M[13] += back_chassis_left_offset.getY();
	back_chassis_left.transform.M[14] += back_chassis_left_offset.getZ();

	//BACK CHASSIS RIGHT
	Cube back_chassis_right(info.back_chassis_right.x, info.back_chassis_right.y, info.back_chassis_right.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back_chassis_right.transform);
	btVector3 back_chassis_right_offset(info.back_chassis_right_offset.x, info.back_chassis_right_offset.y, info.back_chassis_right_offset.z);
	back_chassis_right_offset = back_chassis_right_offset.rotate(q.getAxis(), q.getAngle());

	back_chassis_right.transform.M[12] += back_chassis_right_offset.getX();
	back_chassis_right.transform.M[13] += back_chassis_right_offset.getY();
	back_chassis_right.transform.M[14] += back_chassis_right_offset.getZ();

	//FRONT WHEEL BAR  
	Cube front_wheel_bar(info.front_wheel_bar.x, info.front_wheel_bar.y, info.front_wheel_bar.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&front_wheel_bar.transform);
	btVector3 front_wheel_bar_offset(info.front_wheel_bar_offset.x, info.front_wheel_bar_offset.y, info.front_wheel_bar_offset.z);
	front_wheel_bar_offset = front_wheel_bar_offset.rotate(q.getAxis(), q.getAngle());

	front_wheel_bar.transform.M[12] += front_wheel_bar_offset.getX();
	front_wheel_bar.transform.M[13] += front_wheel_bar_offset.getY();
	front_wheel_bar.transform.M[14] += front_wheel_bar_offset.getZ();

	//BACK WHEEL BAR  
	Cube back_wheel_bar(info.back_wheel_bar.x, info.back_wheel_bar.y, info.back_wheel_bar.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back_wheel_bar.transform);
	btVector3 back_wheel_bar_offset(info.back_wheel_bar_offset.x, info.back_wheel_bar_offset.y, info.back_wheel_bar_offset.z);
	back_wheel_bar_offset = back_wheel_bar_offset.rotate(q.getAxis(), q.getAngle());

	back_wheel_bar.transform.M[12] += back_wheel_bar_offset.getX();
	back_wheel_bar.transform.M[13] += back_wheel_bar_offset.getY();
	back_wheel_bar.transform.M[14] += back_wheel_bar_offset.getZ();

	//SUSPENSION FRONT RIGHT
	Cube suspension_front_right(info.suspension_front_right.x, info.suspension_front_right.y, info.suspension_front_right.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&suspension_front_right.transform);
	btVector3 suspension_front_right_offset(info.suspension_front_right_offset.x, info.suspension_front_right_offset.y, info.suspension_front_right_offset.z);
	suspension_front_right_offset = suspension_front_right_offset.rotate(q.getAxis(), q.getAngle());

	suspension_front_right.transform.M[12] += suspension_front_right_offset.getX();
	suspension_front_right.transform.M[13] += suspension_front_right_offset.getY();
	suspension_front_right.transform.M[14] += suspension_front_right_offset.getZ();

	//SUSPENSION FRONT LEFT
	Cube suspension_front_left(info.suspension_front_left.x, info.suspension_front_left.y, info.suspension_front_left.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&suspension_front_left.transform);
	btVector3 suspension_front_left_offset(info.suspension_front_left_offset.x, info.suspension_front_left_offset.y, info.suspension_front_left_offset.z);
	suspension_front_left_offset = suspension_front_left_offset.rotate(q.getAxis(), q.getAngle());

	suspension_front_left.transform.M[12] += suspension_front_left_offset.getX();
	suspension_front_left.transform.M[13] += suspension_front_left_offset.getY();
	suspension_front_left.transform.M[14] += suspension_front_left_offset.getZ();

	//SUSPENSION BACK RIGHT
	Cube suspension_back_right(info.suspension_back_right.x, info.suspension_back_right.y, info.suspension_back_right.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&suspension_back_right.transform);
	btVector3 suspension_back_right_offset(info.suspension_back_right_offset.x, info.suspension_back_right_offset.y, info.suspension_back_right_offset.z);
	suspension_back_right_offset = suspension_back_right_offset.rotate(q.getAxis(), q.getAngle());

	suspension_back_right.transform.M[12] += suspension_back_right_offset.getX();
	suspension_back_right.transform.M[13] += suspension_back_right_offset.getY();
	suspension_back_right.transform.M[14] += suspension_back_right_offset.getZ();

	//SUSPENSION BACK LEFT
	Cube suspension_back_left(info.suspension_back_left.x, info.suspension_back_left.y, info.suspension_back_left.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&suspension_back_left.transform);
	btVector3 suspension_back_left_offset(info.suspension_back_left_offset.x, info.suspension_back_left_offset.y, info.suspension_back_left_offset.z);
	suspension_back_left_offset = suspension_back_left_offset.rotate(q.getAxis(), q.getAngle());

	suspension_back_left.transform.M[12] += suspension_back_left_offset.getX();
	suspension_back_left.transform.M[13] += suspension_back_left_offset.getY();
	suspension_back_left.transform.M[14] += suspension_back_left_offset.getZ();

	//COLORS
	//front_chassis.color = Red; 
	//front_wheel_bar.color = Red;
	//suspension_front_right.color = Red; 
	//suspension_front_left.color = Red; 

	//RENDERS 
	chassis.Render();
	front_chassis.Render();
	driver_chassis.Render(); 
	back_chassis.Render(); 
	back_chassis_left.Render(); 
	back_chassis_right.Render(); 
	front_wheel_bar.Render(); 
	back_wheel_bar.Render(); 
	suspension_front_right.Render(); 
	suspension_front_left.Render(); 
	suspension_back_right.Render(); 
	suspension_back_left.Render(); 
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}