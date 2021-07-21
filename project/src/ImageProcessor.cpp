#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(ros::NodeHandle &n): 
    mService{n.advertiseService("image_service", &ImageProcessor::serviceHandler, this)} {
}

// Dummy Service Handler
bool ImageProcessor::serviceHandler(project::ImageService::Request &req,
                                    project::ImageService::Response &res) {
    // TODO: Camera get image

    // Temporary piece points
    std::vector<Piece> points {Piece(0, 1, 'X'), Piece(20, 30, 'X'), Piece(100, 50, 'O'),
                               Piece(50, 70, 'O'), Piece(80, 90, 'X'), Piece(11, 60, 'O')};

    // Board 2-7, 2-7
    // TODO: Move this out
    BoardState board;
    project::Point point_msg;
    project::PointArray point_array_msg;

    for (auto &piece : points) {
        if (piece.inGrid()) {
            float gridLength = (100.0 - 10.0) / 3.0;
            int xPos { (int)((piece.getX() - 10.0) / gridLength) };
            int yPos{ (int)((piece.getY() - 10.0) / gridLength) };

            if (!board.addPiece(xPos, yPos, piece.getLetter())) {
                ROS_INFO("Error: Two pieces in the same square!");
            }
        } else {
            // point_msg.
            point_msg.x = piece.getX();
            point_msg.y = piece.getY();
            point_msg.letter = piece.getLetter();
            point_array_msg.data.push_back(point_msg);
        }
    }

    res.board = board.boardToString();
    res.pieces = point_array_msg;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_process");
    ros::NodeHandle n;

    // float gridLength = (10.0 - 2.0) / 3.0;
    // int x { (int)ceil((2.1 - 2.0) / gridLength) };
    // int y{ (int)ceil((9.9 - 2.0) / gridLength) };

    // std::cout << gridLength << x << " " << y << std::endl;

    ImageProcessor ip(n);
    // ros::ServiceServer service = n.advertiseService("image_service", &ImageProcessor::serviceHandler, &ip);

    ros::spin();

    return 0;
}