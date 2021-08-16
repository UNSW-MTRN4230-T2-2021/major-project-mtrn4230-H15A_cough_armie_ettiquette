#include "GazeboController.hpp"

GazeboController::GazeboController(ros::NodeHandle &n):
    mN{n},
    mUserServer{n.advertiseService("userMoveService", &GazeboController::userMoveCallBack, this)},
    mRobotServer{n.advertiseService("robotMoveService", &GazeboController::robotMoveCallBack, this)},
    mOnClient{n.serviceClient<std_srvs::Empty>("/ur5e_epick/epick/on")},
    mOffClient{n.serviceClient<std_srvs::Empty>("/ur5e_epick/epick/off")}
{
    if (!n.getParam("model_path", modelPath)) {
        ROS_ERROR("Model path not found");
    }

    std_srvs::Empty srv;

    mOffClient.call(srv);
    joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    my_plan = moveit::planning_interface::MoveGroupInterface::Plan{};
    ROS_INFO("Planning frame: %s", move_group.getPlanningFrame().c_str());

    // // We can also print the name of the end-effector link for this group.
    ROS_INFO("End effector link: %s", move_group.getEndEffectorLink().c_str());
}


bool GazeboController::robotMoveCallBack(project::RobotMoveService::Request &req,
                                         project::RobotMoveService::Response &res) {
    geometry_msgs::Pose startPose = boardToPose(req.start.x, req.start.y);

    startPose.position.z = BOARD_Z - ROBOT_Z + 0.11;
    startPose.position.x -= ROBOT_X;
    startPose.position.y -= ROBOT_Y;

    startPose.orientation.x=1.0;
    startPose.orientation.y=0.0;
    startPose.orientation.z=0.0;
    startPose.orientation.w=0.0;

    std::cout << req.start.x << ", " << req.start.y << std::endl;
    
    move_group.setPoseTarget(startPose);

    bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    if(!success) {
        ROS_WARN("Unable to plan path. Ensure goal pose is valid or adjust tolerance");
        return false;
    }
    std_srvs::Empty srv;

    move_group.move();
    mOnClient.call(srv);

    geometry_msgs::Pose endPose = gridPositionToPose(req.goal.x, req.goal.y);
    endPose.position.z = BOARD_Z - ROBOT_Z + 0.11;
    endPose.position.x -= ROBOT_X;
    endPose.position.y -= ROBOT_Y;
    endPose.orientation = startPose.orientation;

    geometry_msgs::Pose midPose;
    midPose.position.x = (endPose.position.x + startPose.position.x) / 2.0;
    midPose.position.y = (endPose.position.y + startPose.position.y) / 2.0;
    midPose.position.z = BOARD_Z - ROBOT_Z + 0.4;
    midPose.orientation = startPose.orientation;

    std::vector<geometry_msgs::Pose> waypoints {
        startPose, midPose, endPose
    };

    moveit_msgs::RobotTrajectory trajectory;
    const double jump_threshold = 0.0;
    const double eef_step = 0.01;
    double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);

    my_plan.trajectory_= trajectory;
    move_group.execute(my_plan);

    mOffClient.call(srv);

    return robotHome();
}

bool GazeboController::userMoveCallBack(project::UserMoveService::Request &req,
                                        project::UserMoveService::Response &res) {
    if (req.service == Service::POWER_ON) {
        return robotOn(req.player);
    } else if (req.service == Service::SPAWN_MOVE) {
        geometry_msgs::Pose p{gridPositionToPose(req.goal.x, req.goal.y)};
        std::string pieceName{pieceNames[mPlayer]+std::to_string(mNumPlayer)};
        mNumPlayer++;
        spawnPiece(modelPath+playerPaths[mPlayer], pieceName, p);
        return true;
    } else if (req.service == Service::CLEAR_BOARD) {
        return clearBoard();
    } else if (req.service == Service::SPAWN_TEST) {
        geometry_msgs::Pose p{boardToPose(req.goal.x, req.goal.y)};
        int num;
        if (req.player == mPlayer) {
            num = mNumPlayer;
            mNumPlayer++;
        } else if (req.player == mRobot) {
            num = mNumRobot;
            mNumRobot++;
        } else return false;
        std::string pieceName{pieceNames[req.player]+std::to_string(num)};
        spawnPiece(modelPath+playerPaths[req.player], pieceName, p);
        return true;
    } else return true;
}

bool GazeboController::robotOn(const int &player) {
    std::cout << player << std::endl;
    if (player < Player::X || player > Player::O) return false;
    mPlayer = player;
    mRobot = 1 - player;

    if (!clearBoard()) return false;

    if (!robotHome()) return false;

    geometry_msgs::Pose pose;
    pose.position.x = BOARD_X;
    pose.position.y = BOARD_Y;
    pose.position.z = BOARD_Z;

    tf2::Quaternion myQuaternion;
    myQuaternion.setRPY( 0, 0, 0 );

    pose.orientation = tf2::toMsg(myQuaternion);

    std::string path{modelPath + BASE_PATH};
    
    spawnPiece(path, "b", pose);
    spawnInitialPieces();

    ROS_INFO("POWERED ON");

    return true;


}

geometry_msgs::Pose GazeboController::gridPositionToPose(const float &x, const float &y) {
    geometry_msgs::Pose pose;

    float xBoardPos{y*SQUARE_WIDTH + (float)(SQUARE_WIDTH/2.0) + 
                    BOARD_X - (float)(SQUARE_WIDTH*3.0/2.0)},
          yBoardPos{x*SQUARE_WIDTH + (float)(SQUARE_WIDTH/2.0) + 
                    BOARD_Y - (float)(SQUARE_WIDTH*3.0/2.0)},
          zBoardPos{BOARD_Z + PIECE_HEIGHT};

    pose.position.x = xBoardPos;
    pose.position.y = yBoardPos;
    pose.position.z = zBoardPos;

    tf2::Quaternion myQuaternion;
    myQuaternion.setRPY( 0, 0, 0 );

    return pose;
}

geometry_msgs::Pose GazeboController::boardToPose(const int &x, const int &y) {
    geometry_msgs::Pose pose;

    float xBoardPos{(float)(y/1000.0) - (float)0.3 + BOARD_X},
          yBoardPos{(float)(x/1000.0) - (float)0.3 + BOARD_Y},
          zBoardPos{BOARD_Z + PIECE_HEIGHT};

    pose.position.x = xBoardPos;
    pose.position.y = yBoardPos;
    pose.position.z = zBoardPos;

    tf2::Quaternion myQuaternion;
    myQuaternion.setRPY( 0, 0, 0 );

    return pose;
}

void GazeboController::spawnInitialPieces() {
    // Initialise random seed
    srand(time(NULL));
    std::vector<std::pair<int, int>> points;

    // Randomly Spawn pieces
    for (int i = 0; i < numRobot; ) {
        int edge = rand() % 4;
        int xDiff = rand() % 540 - 270,
            yDiff = rand() % 60 - 30, 
            rotation = 0, x, y;

        if (edge % 2 == 0) {
            x = 300 + xDiff;
            y = edge * 240 + 60 + yDiff;
        } else {
            x = edge * 240 - 180 + yDiff;
            y = 300 + xDiff;
        }

        std::pair<int, int> position{x, y};
        bool tooClose{false};

        for (auto &point : points) {
            if (distance(point, position) < 70) {
                tooClose = true;
                break;
            }
        }

        if (!tooClose) {
            points.push_back(position);
            geometry_msgs::Pose pose{boardToPose(x, y)};
            std::string pieceName{pieceNames[mRobot]+std::to_string(mNumRobot)};
            mNumRobot++;
            spawnPiece(modelPath+playerPaths[mRobot], pieceName, pose);
            i++;
        }
    }
    std::cout << mNumRobot << std::endl;
}

float GazeboController::distance(std::pair<int, int> p1, std::pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
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

bool GazeboController::clearBoard() {
    ros::ServiceClient deleteModel = mN.serviceClient<gazebo_msgs::DeleteModel>("gazebo/delete_model");
    deleteModel.waitForExistence();
    gazebo_msgs::DeleteModel srv;

    for (int i = 0; i < mNumPlayer; i++) {
        std::string pieceName{pieceNames[mPlayer] + std::to_string(i)};
        srv.request.model_name = pieceName;
        deleteModel.call(srv);
        if (!srv.response.success) return false;
    }

    mNumPlayer = 0;

    for (int i = 0; i < mNumRobot; i++) {
        std::string pieceName{pieceNames[mRobot] + std::to_string(i)};
        srv.request.model_name = pieceName;
        deleteModel.call(srv);
        if (!srv.response.success) return false;
    }

    mNumRobot = 0;
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