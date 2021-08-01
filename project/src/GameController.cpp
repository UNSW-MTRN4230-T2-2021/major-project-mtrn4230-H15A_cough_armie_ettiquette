#include "GameController.hpp"

GameController::GameController(ros::NodeHandle &n):
    mImageSub{n.subscribe("processed_image", 100, &GameController::imageCallBack, this)} {
}

void GameController::imageCallBack(const project::BoardInfo::ConstPtr &msg) {
    BoardState newBoard(msg->board);

    newBoard.showBoardState();
}


// BoardState GameController::getNewBoardState() {
//     project::ImageService srv;
//     srv.request.flag = 0;

//     if (mImageClient.call(srv)) {
//         BoardState newBoard{srv.response.board};
//         // TODO: Process srv.response.pieces (remaining pieces)
//         return newBoard;
//     } else {
//         ROS_ERROR("Failed to call Image Service");
//     }
// }

void GameController::saveBoardState(BoardState &state) {
    mState.setBoardState(state);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "game_controller");
    ros::NodeHandle n;

    // Random code for testing
    GameController c(n);

    ros::spin();
}