#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(ros::NodeHandle &n): 
    mPub{n.advertise<project::BoardInfo>("processed_image", 100)} {
}

// Dummy Service Handler
void ImageProcessor::imageRequestCallBack(/* TODO: Implement subscriber callbback here */ ) {
    // TODO: Camera get image

    // Temporary piece points
    std::vector<Piece> points {Piece(0, 1, 'X'), Piece(20, 30, 'X'), Piece(100, 50, 'O'),
                               Piece(50, 70, 'O'), Piece(80, 90, 'X'), Piece(11, 60, 'O')};

    const float yMin{10.0}, yMax{100.0}, xMin{10.0}, xMax{100.0};

    // TODO: Move this out
    BoardState board;
    project::BoardInfo msg;
    project::Point point_msg;

    for (auto &piece : points) {
        if (piece.inGrid(xMin, xMax, yMin, yMax)) {
            float gridLength = (yMax - yMin) / 3.0;
            int xPos { (int)((piece.getX() - xMin) / gridLength) };
            int yPos{ (int)((piece.getY() - yMin) / gridLength) };

            if (!board.addPiece(xPos, yPos, piece.getLetter())) {
                ROS_INFO("Error: Two pieces in the same square!");
            }
        } else {
            // point_msg.
            point_msg.x = piece.getX();
            point_msg.y = piece.getY();
            point_msg.letter = piece.getLetter();
            msg.pieces.push_back(point_msg);
        }
    }

    msg.board = board.boardToString();

    // THIS part can be removed in the future
    while (ros::ok()) {
        if (mPub.getNumSubscribers() > 0) {
            mPub.publish(msg);
            break;
        }
        ros::spinOnce();
    }
    // TODO: add conversion from piece on board to board FoR
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_process");
    ros::NodeHandle n;

    ImageProcessor ip(n);

    // This is for testing
    ip.imageRequestCallBack();

    ros::spin();

    return 0;
}