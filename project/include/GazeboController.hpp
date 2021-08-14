#ifndef GAZCON_H
#define GAZCON_H

#include "ros/ros.h"

#include "project/UserMoveService.h"
#include "project/RobotMoveService.h"
#include "project/Point.h"

#include "tf2/LinearMath/Quaternion.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

#include "std_srvs/Empty.h"
#include "std_msgs/String.h"
#include <std_msgs/Float64.h>

#include "gazebo_msgs/SpawnModel.h" 
#include "gazebo_msgs/DeleteModel.h"
#include "geometry_msgs/Pose.h" 
#include "geometry_msgs/Point.h" 
#include "geometry_msgs/Quaternion.h" 

#include <moveit/move_group_interface/move_group_interface.h>
// These are for the various ROS message formats we need
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <sstream>
#include <fstream>
#include <math.h>

#include <ctime>
#include <chrono>
#include <thread>
#include <utility>

constexpr double pi = 3.1415926535;

constexpr auto deg_to_rad(double deg) -> double {
    return deg * pi/180.0;
}

/* The planning group can be found in the ur5e_epick_moveit_config/config/ur5e.srdf */
static const std::string PLANNING_GROUP = "manipulator";

class GazeboController {
public:
    struct {
        float BOARD_X = 1.3,
        BOARD_Y = 0.1,
        BOARD_Z = 0.775,
        BOARD_WIDTH = 0.6,
        SQUARE_WIDTH = 0.12,
        PIECE_HEIGHT = 0.055,
        ROBOT_X = 0.8,
        ROBOT_Y = 0.0,
        ROBOT_Z = 0.675;
    };

    enum Service {
        POWER_ON = 0,
        SPAWN_MOVE,
        CLEAR_BOARD
    };

    enum Player {
        X=0,
        O,
        NUM_PLAYERS
    };

    static constexpr int numRobot{5};

private:
    ros::NodeHandle mN;
    ros::ServiceServer mUserServer, mRobotServer;
    ros::ServiceClient mOnClient, mOffClient;
    std::string modelPath;
    int mPlayer{0}, mRobot{1};
    int mNumPlayer{0}, mNumRobot{0};
    moveit::planning_interface::MoveGroupInterface move_group{PLANNING_GROUP};
    const moveit::core::JointModelGroup *joint_model_group;
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

    const std::string BASE_PATH{"/base_model/base_model.sdf"};
    const std::array<std::string, Player::NUM_PLAYERS> playerPaths {
        "/x_textured/x_textured.sdf",
        "/o_textured/o_textured.sdf"
    };
    const std::array<std::string, Player::NUM_PLAYERS> pieceNames {
        "x",
        "o"
    };

    bool robotMoveCallBack(project::RobotMoveService::Request &req,
                           project::RobotMoveService::Response &res);
    bool userMoveCallBack(project::UserMoveService::Request &req,
                          project::UserMoveService::Response &res);

    bool robotOn(const int &player);
    geometry_msgs::Pose gridPositionToPose(const float &x, const float &y);
    geometry_msgs::Pose boardToPose(const int &x, const int &y);
    void spawnInitialPieces();
    float distance(std::pair<int, int> p1, std::pair<int, int> p2);

    bool robotHome();

    bool clearBoard();

public:
    GazeboController(ros::NodeHandle &n);

    void spawnPiece(const std::string &filePath, const std::string &modelName,
                    geometry_msgs::Pose &pose);
};

#endif
