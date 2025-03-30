#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    if (client.call(srv)) {
        ROS_INFO("Service call successful");
    }
    else{
        ROS_ERROR("Failed to execute");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    int each_section_width = img.width / 3;
    int hori_pix_posi, section=-1;



    

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    for (size_t i = 0; i < img.height * img.step; i += 3) {  // step: The number of bytes per row (equals width × number of channels).
        int red = img.data[i];
        int green = img.data[i + 1];
        int blue = img.data[i + 2];
 
        // Next check if you found the white color ball

        if (red == 255 && green == 255 && blue == 255) {
            // Found a white pixel, which means finding the ball
            // Next step would be decide how to move based on the
            // calculated pixel position or coordinates in the image
            hori_pix_posi = (i / 3) % img.width;
            section = hori_pix_posi / each_section_width;

            if (section == 0){
                ROS_INFO("Turning LEFT");
                drive_robot(0, 0.5);  //LEFT
            }
            else if (section == 1){
                ROS_INFO("Going STRAIGHT");
                drive_robot(0.5, 0);  //STRAIGHT
            }
            else if (section == 2){
                ROS_INFO("Turning RIGHT");
                drive_robot(0, -0.5);   //RIGHT
            }
            break;

        }
    }
    if (section == -1){
        ROS_INFO("STOPPING");
        drive_robot(0.0, 0.0);   // STOP
    }

}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}