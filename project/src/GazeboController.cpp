#include "GazeboController.hpp"

GazeboController::GazeboController(ros::NodeHandle &n):
    mN{n},
    mUserServer{n.advertiseService("userMoveService", &GazeboController::userMoveCallBack, this)},
    mRobotServer{n.advertiseService("robotMoveService", &GazeboController::robotMoveCallBack, this)},
    mOnClient{n.serviceClient<std_srvs::Empty>("/ur5e_epick/epick/on")},
    mOffClient{n.serviceClient<std_srvs::Empty>("/ur5e_epick/epick/off")}
    // mSpinner{ros::AsyncSpinner(2)}
    // joint_model_group{move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP)}
{
    if (!n.getParam("model_path", modelPath)) {
        ROS_ERROR("Model path not found");
    }
    // mSpinner.start();
    // if (n.getParam("model_path", hey)) {
    //     ROS_ERROR("heeeeyyy");
    //     std::cout << hey << std::endl;
    // }

    std_srvs::Empty srv;

    mOffClient.call(srv);
    joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    my_plan = moveit::planning_interface::MoveGroupInterface::Plan{};
    ROS_INFO("Planning frame: %s", move_group.getPlanningFrame().c_str());

    // // We can also print the name of the end-effector link for this group.
    ROS_INFO("End effector link: %s", move_group.getEndEffectorLink().c_str());

    // std::string name {"/home/mtrn4230/lab_workspaces/project_ws/src/project/models/base_model/base_model.sdf"};

    // geometry_msgs::Pose pose;
    // pose.position.x = 1.71;
    // pose.position.y = 0.1348;
    // pose.position.z = 0.775;

    // tf2::Quaternion myQuaternion;
    // myQuaternion.setRPY( 0, 0, 0 );

    // pose.orientation = tf2::toMsg(myQuaternion);

    // ROS_ERROR("BEFORE");
    // spawnPiece(name, "b", pose);
    // ROS_ERROR("AFTER");
}


bool GazeboController::robotMoveCallBack(project::RobotMoveService::Request &req,
                                         project::RobotMoveService::Response &res) {
    int a = 1;
}

bool GazeboController::userMoveCallBack(project::UserMoveService::Request &req,
                                        project::UserMoveService::Response &res) {
    if (req.service == Service::POWER_ON) {
        return robotOn(req.player);
    } else {
        geometry_msgs::Pose p{boardToPose(req.goal.x, req.goal.y)};
        // spawnPiece(O_PATH, p);
        return true;
    }
}

bool GazeboController::robotOn(const int &player) {
    std::cout << player << std::endl;
    if (player < Player::X || player > Player::O) return false;

    if (!robotHome()) return false;

    geometry_msgs::Pose pose;
    pose.position.x = BOARD_X;
    pose.position.y = BOARD_Y;
    pose.position.z = BOARD_Z;
    pose.position.x = 1.71;
    pose.position.y = 0.1348;
    pose.position.z = 0.775;

    tf2::Quaternion myQuaternion;
    myQuaternion.setRPY( 0, 0, 0 );

    pose.orientation = tf2::toMsg(myQuaternion);

    std::string path{modelPath + BASE_PATH};
    
    spawnPiece(path, "b", pose);

    ROS_INFO("DONE");

    return true;
}

geometry_msgs::Pose GazeboController::boardToPose(const float &x, const float &y) {
    geometry_msgs::Pose p;

    return p;
}

void GazeboController::spawnPiece(const std::string &filePath, const std::string &modelName,
                                  geometry_msgs::Pose &pose) {
    ros::ServiceClient spawnModel = mN.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_sdf_model");
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

bool GazeboController::robotHome() {
    auto group_state{"home"};
    move_group.setNamedTarget(group_state);

    // Check if plan is possible
    auto success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    if (!success) {
        ROS_WARN("Unable to plan path. Ensure goal pose is valid or adjust tolerance");
        return false;
    }

    ROS_INFO("Found path to %s, moving robot...", group_state);
    move_group.move();

    return true;
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "gazebo_controller");
    ros::NodeHandle n;

    ros::AsyncSpinner spinner(2);
    spinner.start();

    GazeboController gc(n);

    // ros::spin();
    
    ros::waitForShutdown();
}