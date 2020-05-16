#ifndef CAMERA_H
#define CAMERA_H

#include "model.h"
#include "changer.h"
#define CAMERA_SPEED 5.0

struct Camera
{
	struct Vertex position;
	struct Vertex pose;
	struct Vertex prev_position;
};

double degree_to_radian(double degree);

void init_camera(struct Camera* camera);

void set_view_point(const struct Camera* camera);

void rotate_camera(struct Camera* camera, double horizontal, double vertical);

void set_clear_camera_pose(struct Camera* camera);

void move_camera_forward(struct Camera* camera, double distance);

void move_camera_backward(struct Camera* camera, double distance);

void step_camera_left(struct Camera* camera, double distance);

void step_camera_right(struct Camera* camera, double distance);

void move_camera_up(struct Camera* camera, double distance);

void move_camera_down(struct Camera* camera, double distance);

void change_room(Changer* changer,int id,int color);

void increase_phase();

void decrease_phase();

#endif 

