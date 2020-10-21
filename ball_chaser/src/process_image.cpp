#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <ball_chaser/DriveToTarget.h>

class ProcessImage
{
	ros::Subscriber sub1;
  	ros::ServiceClient client;
  	ros::NodeHandle n;
	bool moving;
  
  	public:
  
  		ProcessImage()
        {
        	sub1 = n.subscribe<sensor_msgs::Image>("/camera/rgb/image_raw", 10, &ProcessImage::process_image_callback, this);
          	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
          	moving = false;
        }
  
  		void drive_robot(float lin_x, float ang_z)
        {
          	ROS_INFO("Driving robot with requested velocities");
        	ball_chaser::DriveToTarget srv;
          	srv.request.linear_x = lin_x;
          	srv.request.angular_z = ang_z;
          
          	if(! client.call(srv))
              ROS_ERROR("Failed to call service /ball_chaser/command_robot");
        }
  
  		void process_image_callback(const sensor_msgs::Image img)
        {
        	int white_pixel = 255;
          	int one_third = (int) (img.width / 3);
          	int direction = -1; 

          
          	for(int i = 0; i < img.height * img.step; i++)
            {              
              	if(img.data[i] == white_pixel)
                {
                    //to check if the ball is in the left, middle or right, 
                    //divide the image into 3 and check the white pixel number
                    //calculate and decide in which 'third' of the image the pixel falls
                  	printf("White pixel number: %d\n",i);
                  	if((i % img.width) < one_third)
                      	direction = 0;
                    else if((i % img.width) < (one_third*2))
                      	direction = 1;
                    else
                      	direction = 2;
                  	break;
                }
            }
          	//printf("************************"+std::string(direction)+"\n");
          	switch(direction)
            {
              	case 0: drive_robot(0, 0.3);
                		moving = true;
                		break;
                case 1: drive_robot(0.4, 0);
                		moving = true;
                		break;
                case 2: drive_robot(0, -0.3);
                		moving = true;
                		break;
              	default: if(moving)
                  			drive_robot(0,0);
                			moving = false;
            }
        }
  
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "process_image");
  
  	ProcessImage piObj;
  
  	ros::spin();
}


// #include "ros/ros.h"
// #include "ball_chaser/DriveToTarget.h"
// #include <sensor_msgs/Image.h>

// // Define a global client that can request services
// ros::ServiceClient client;

// // This function calls the command_robot service to drive the robot in the specified direction
// void drive_robot(float lin_x, float ang_z)
// {
//     // TODO: Request a service and pass the velocities to it to drive the robot
// }

// // This callback function continuously executes and reads the image data
// void process_image_callback(const sensor_msgs::Image img)
// {

//     int white_pixel = 255;

//     // TODO: Loop through each pixel in the image and check if there's a bright white one
//     // Then, identify if this pixel falls in the left, mid, or right side of the image
//     // Depending on the white ball position, call the drive_bot function and pass velocities to it
//     // Request a stop when there's no white ball seen by the camera
// }

// int main(int argc, char** argv)
// {
//     // Initialize the process_image node and create a handle to it
//     ros::init(argc, argv, "process_image");
//     ros::NodeHandle n;

//     // Define a client service capable of requesting services from command_robot
//     client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

//     // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
//     ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

//     // Handle ROS communication events
//     ros::spin();

//     return 0;
// }