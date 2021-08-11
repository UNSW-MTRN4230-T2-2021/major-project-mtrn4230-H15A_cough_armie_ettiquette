#include "ros/ros.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#include "std_srvs/Empty.h"
#include "std_msgs/String.h"
#include <std_msgs/Float64.h>

#include "gazebo_msgs/SpawnModel.h" 
#include "geometry_msgs/Pose.h" 
#include "geometry_msgs/Point.h" 
#include "geometry_msgs/Quaternion.h" 

#include <sstream>
#include <fstream>
#include <math.h>

#include <chrono>
#include <thread>


void spawn_x(ros::NodeHandle n, geometry_msgs::Pose pose) {

    //INSERT CODE HERE (HINT: look into the gazebo/spawn_sdf_model)
    ros::ServiceClient spawnModel = n.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_sdf_model");
    spawnModel.waitForExistence();

    std::stringstream buffer;
    gazebo_msgs::SpawnModel srv;
    std::ifstream fd{"src/project/models/x_textured/x_textured.sdf"};

    buffer << fd.rdbuf();

    srv.request.model_xml = buffer.str();
    srv.request.model_name = "x1";
    srv.request.initial_pose = pose;
    srv.request.robot_namespace = "/";
    srv.request.reference_frame = "world";

    fd.close();

    spawnModel.call(srv);
}

void spawn_o(ros::NodeHandle &n, geometry_msgs::Pose &pose) {
    ros::ServiceClient spawnModel = n.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_sdf_model");
    spawnModel.waitForExistence();

    std::stringstream buffer;
    gazebo_msgs::SpawnModel srv;
    std::ifstream fd{"src/project/models/o_textured/o_textured.sdf"};

    buffer << fd.rdbuf();

    srv.request.model_xml = buffer.str();
    srv.request.model_name = "o1";
    srv.request.initial_pose = pose;
    srv.request.robot_namespace = "/";
    srv.request.reference_frame = "world";

    fd.close();

    spawnModel.call(srv);
}

void spawn_base(const std::string &filePath, const std::string &modelName, 
                ros::NodeHandle &n, geometry_msgs::Pose &pose) {
    ros::ServiceClient spawnModel = n.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_sdf_model");
    spawnModel.waitForExistence();

    std::stringstream buffer;
    gazebo_msgs::SpawnModel srv;
    std::ifstream fd{filePath};

    buffer << fd.rdbuf();

    srv.request.model_xml = buffer.str();
    srv.request.model_name = modelName.c_str();
    srv.request.initial_pose = pose;
    srv.request.robot_namespace = "/";
    srv.request.reference_frame = "world";

    fd.close();

    spawnModel.call(srv);
}

bool serviceCallBack(std_srvs::Empty::Request &req,
                     std_srvs::Empty::Response &res) {
    ros::NodeHandle n;
    geometry_msgs::Pose pose;
    pose.position.x = 1.71;
    pose.position.y = 0.1348;
    pose.position.z = 0.775;

    tf2::Quaternion myQuaternion;
    myQuaternion.setRPY( 0, 0, 0 );

    pose.orientation = tf2::toMsg(myQuaternion);

    std::cout << "generating box (students to do)" << std::endl;

    std::string basePath {"src/project/models/base_model/base_model.sdf"};
    ROS_INFO("BEFORE");
    spawn_base(basePath, "b", n, pose);
    ROS_INFO("AFTER");
    // pose.position.x = 1.71;
    // pose.position.y = 0.1348;
    // pose.position.z = 0.83;
    // spawn_x(n,pose);

    // pose.position.x = 1.59;
    // pose.position.y = 0.2548;
    // pose.position.z = 0.83;
    // spawn_o(n, pose);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "lab08_cpp");
    ros::NodeHandle n;

    // ros::ServiceClient client{n.serviceClient<std_srvs::Empty>("hi")};
    ros::ServiceServer server{n.advertiseService("hi", serviceCallBack)};

    // ros::spin();
    ros::AsyncSpinner spinner(2);
    spinner.start();

    // std_srvs::Empty srv;
    // client.call(srv);

    ros::waitForShutdown();
   
    return 0;
}
