#include "Controller.hpp"

Controller::Controller(ros::NodeHandle &n):
    mImageClient{n.serviceClient<project::ImageService>("image_service")} {
}

BoardState Controller::getNewBoardState() {
    project::ImageService srv;
    srv.request.flag = 0;

    if (mImageClient.call(srv)) {
        BoardState newBoard{srv.response.board};
        // TODO: Process srv.response.pieces (remaining pieces)
        return newBoard;
    } else {
        ROS_ERROR("Failed to call Image Service");
    }
}

void Controller::saveBoardState(BoardState &state) {
    mState.setBoardState(state);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "game_controller");
    ros::NodeHandle n;

    // Random code for testing
    Controller c(n);

    BoardState b {c.getNewBoardState()};

    b.showBoardState();

    // c.showBoardState();
    // BoardState::Board brod{{{' ', 'X', ' '},
    //                         {'O', 'X', ' '},
    //                         {'H', 'T', 'C'}}};
    // BoardState b{brod};
    // c.saveBoardState(b);
    // c.showBoardState();
    // c.showBoardState();

    ros::spin();
}