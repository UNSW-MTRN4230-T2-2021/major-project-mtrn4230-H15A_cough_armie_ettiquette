#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(ros::NodeHandle &n): 
    // mPub{n.advertise<project::BoardInfo>("processed_image", 100)},
    mIt{n},
    mGameRequest{n.advertiseService("imageRequest", &ImageProcessor::imageRequestCallBack, this)} {
    mImageSub = mIt.subscribe("camera/image_raw", 1, &ImageProcessor::processImageCallBack, this);

    // Temporary
    cv_bridge::CvImagePtr cv_ptr;
    cv::namedWindow("HEHE");
}

void ImageProcessor::processImageCallBack(const sensor_msgs::ImageConstPtr &msg) {
    mImage = msg;
}

// Dummy Service Handler
bool ImageProcessor::imageRequestCallBack(project::ImageRequest::Request &req,
                                          project::ImageRequest::Response &res) {
    cv_bridge::CvImagePtr cvPtr;

    try {
        cvPtr = cv_bridge::toCvCopy(mImage, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return true;
    }

    cv::Mat image {cvPtr->image};

    // IMPROVE into ENUM
    if (req.service == 0)
        handleSetUp(image);
    else if (req.service == 1) {
        // std::vector<Pieces> = processImage??
        processImage(image);
        res.info = processPieces();
    }

    return true;
}

void ImageProcessor::handleSetUp(cv::Mat &image) {
    cv::Mat hsv_image, magenta_threshold;
    cv::cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);

    cv::Scalar min_magenta{135, 0.2*255, 0.2*255};
    cv::Scalar max_magenta{165, 255, 255};

    cv::inRange(hsv_image, min_magenta, max_magenta, magenta_threshold);

    cv::imshow("HEHE", magenta_threshold);
}

void ImageProcessor::processImage(cv::Mat &image) {
    // TODO
    // Red Range [165, 0.2*255, 0.2*255] -> [15, 255, 255]
    // Blue Range [75, 0.2*255, 0.2*255] -> [105, 255, 255]
    // Magenta Range [135, 0.2 * 255, 0.2 * 255] -> [165, 255, 255]

}

project::BoardInfo ImageProcessor::processPieces() {
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

            // TODO: THROW ERROR
            if (!board.addPiece(xPos, yPos, piece.getLetter())) {
                ROS_ERROR("Error: Two pieces in the same square!");
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

    return msg;

    // THIS part can be removed in the future
    // while (ros::ok()) {
    //     if (mPub.getNumSubscribers() > 0) {
    //         mPub.publish(msg);
    //         break;
    //     }
    //     ros::spinOnce();
    // }
    // TODO: add conversion from piece on board to board FoR
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_process");
    ros::NodeHandle n;

    ImageProcessor ip(n);

    ros::spin();

    // return 0;
}