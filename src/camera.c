#include "camera.h"
#include "model.h"
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define size 700

int loc = 0;
int phase = 3;


double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

void can_move(struct Camera* camera)
{

    if(camera->position.x>size || camera->position.x<-size || camera->position.z<-size || camera->position.z>size)
    {
		camera->position=camera->prev_position;
	}

	else if((camera->position.x>48 && camera->position.x< 52) &&(camera->position.z >-500 && camera->position.z <500)) 
	{
		camera->position=camera->prev_position;
	}

	else if((camera->position.z <-48 && camera->position.z >-52) && (camera->position.x <500 && camera->position.x >-500))
	{
		camera->position=camera->prev_position;
	}

	// door trigger 0
	if((camera->position.x>49 && camera->position.x< 51) && camera->position.z < 500) 
	{

		if(loc == 0)
		{
			loc++;

			change_room(&changer,3,phase);
			increase_phase();
		}
		else
		{
			loc--;
			change_room(&changer,2,phase);
			decrease_phase();
		}
		
		//printf("loc: %d\n",loc);
	}

	// door trigger 1
	if((camera->position.z<-49 && camera->position.z>-51) && camera->position.x > -500) 
	{
		if(loc == 1){
			loc++;
			change_room(&changer,0,phase);
			increase_phase();
		}
		else
		{
			loc--;
			change_room(&changer,3,phase);
			decrease_phase();
		}
		//printf("loc: %d\n",loc);
	}

	// door trigger 2
	if((camera->position.x>49 && camera->position.x< 51) && camera->position.z > -500) 
	{
		if(loc == 2){
			loc++;
			change_room(&changer,1,phase);
			increase_phase();
		}
		else
		{
			loc--;
			change_room(&changer,0,phase);
			decrease_phase();
		}
		//printf("loc: %d\n",loc);
	}

	// door trigger 3
	if((camera->position.z<-48 && camera->position.z>-52) && camera->position.x < 500) 
	{
		if(loc == 3){
			loc = 0;
			change_room(&changer,2,phase);
			increase_phase();
		}
		else
		{
			loc = 3;
			change_room(&changer,1,phase);
			decrease_phase();
		}
	}
       
}

void change_room(Changer* changer,int id,int color)
{
	*changer->walls[id] = load_texture(changer->names[color]);
	*changer->grounds[id] = load_texture(changer->names[color]);
	*changer->layer2s[id] = load_texture(changer->names[color]);
	//printf("%s\n",changer->names[color]);
}

void increase_phase()
{
	phase++;

	if(phase > 7)
	{
		phase = 0;
	}
}

void decrease_phase()
{
	phase--;

	if(phase < 0)
	{
		phase = 7;
	}
}

void init_camera(struct Camera* camera)
{
	
	camera->position.x = 0;
	camera->position.y = 100;
	camera->position.z = -600;

	camera->pose.x = 0;
	camera->pose.y = 0;
	camera->pose.z = 180;

	
}

void set_view_point(const struct Camera* camera)
{
	glRotatef(-(camera->pose.x), 1.0, 0, 0);
	glRotatef(-(camera->pose.z), 0, 1.0, 0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);

}

void rotate_camera(struct Camera* camera, double horizontal, double vertical)
{
	double fallbackPoseOfX;

	if(camera->pose.x >= 0 && camera->pose.x <= 90)
	{
		fallbackPoseOfX = 90;
	}
	else {
		fallbackPoseOfX = 270;
	}

	if(camera->pose.x + vertical > 90 && camera->pose.x + vertical < 270)
	{
		camera->pose.x = fallbackPoseOfX;
	}
	else {
		camera->pose.x += vertical;
	}

	if(camera->pose.x  > 90 && camera->pose.x < 270)
	{
		set_clear_camera_pose(camera);
	}


	// Horizontal
	camera->pose.z += horizontal;

	if (camera->pose.z < 0) {
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0) {
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0) {
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0) {
		camera->pose.x -= 360.0;
	}
}

void set_clear_camera_pose(struct Camera* camera)
{
	camera->pose.x = 0;
}

void move_camera_forward(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
	
}

void move_camera_backward(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z += cos(angle) * distance;
	camera->position.x += sin(angle) * distance;
    can_move(camera);
}

void step_camera_left(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z + 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void step_camera_right(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z - 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void move_camera_up(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
    if(camera->position.y<size-10)
	camera->position.y += distance;
    can_move(camera);
}

void move_camera_down(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	if(camera->position.y>10)
	camera->position.y -= distance;
    can_move(camera);
}
