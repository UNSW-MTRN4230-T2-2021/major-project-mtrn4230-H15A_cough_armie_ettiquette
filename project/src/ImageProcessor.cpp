#include "ImageProcessor.hpp"

ImageProcessor::ImageProcessor(ros::NodeHandle &n): 
    // mPub{n.advertise<project::BoardInfo>("processed_image", 100)},
    mIt{n},
    mGameRequest{n.advertiseService("imageRequest", &ImageProcessor::imageRequestCallBack, this)} {
    mImageSub = mIt.subscribe("camera/image_raw", 1, &ImageProcessor::processImageCallBack, this);

    // Temporary
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

    if (req.service == Request::SETUP)
        handleSetUp(image);
    else if (req.service == Request::PROCESS)
        res.info = processImage(image);

    return true;
}

cv::Point2f ImageProcessor::findContourCentre(const std::vector<cv::Point> &contour) {
    int minX, maxX, minY, maxY;
    minX = maxX = contour[0].x;
    minY = maxY = contour[0].y;

    for (auto &point : contour) {
        if (point.x < minX) minX = point.x;
        else if (point.x > maxX) maxX = point.x;
        if (point.y < minY) minY = point.y;
        else if (point.y > maxY) maxY = point.y;
    }

    return cv::Point2f((minX + maxX)/2, (minY + maxY)/2);;
}

void ImageProcessor::sortCorners(std::array<cv::Point2f, 4> &corners) {
    std::sort(corners.begin(), corners.end(),
              [](cv::Point2f &point1, cv::Point2f &point2) {
                  return point1.y < point2.y;
              });

    if (corners[0].x > corners[1].x)
        std::iter_swap(corners.begin(), corners.begin() + 1);
    if (corners[3].x > corners[2].x)
        std::iter_swap(corners.rbegin(), corners.rbegin() + 1);
}

void ImageProcessor::handleSetUp(cv::Mat &image) {
    cv::Mat hsv_image, magenta_threshold;
    cv::cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);

    cv::Scalar min_magenta{135, 0.2*255, 0.2*255};
    cv::Scalar max_magenta{165, 255, 255};

    cv::inRange(hsv_image, min_magenta, max_magenta, magenta_threshold);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(magenta_threshold, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::sort(contours.begin(), contours.end(),
              [](std::vector<cv::Point> &contour1, std::vector<cv::Point> &contour2) {
                  return cv::contourArea(cv::Mat(contour2)) < cv::contourArea(cv::Mat(contour1));
              });

    std::array<cv::Point2f, 4> inputCorners;

    for (int i = 0; i < 4; i++)
        inputCorners[i] = findContourCentre(contours[i]);

    sortCorners(inputCorners);

    for (auto &corner : inputCorners)
        std::cout << corner.x << ", " << corner.y <<std::endl;

    // TODO: These numbers part of enum
    std::array<cv::Point2f, 4> outputCorners {
        cv::Point2f{120, 120}, cv::Point2f{480, 120},
        cv::Point2f{480, 480}, cv::Point2f{120, 480}
    };

    cv::Mat output;

    mH = cv::getPerspectiveTransform(inputCorners, outputCorners);
}

void ImageProcessor::findBinaryPieces(std::vector<Piece> &points, cv::Mat &threshold,
                                      const char &letter) {
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cvSize(5, 5));
    cv::morphologyEx(threshold, threshold, cv::MORPH_OPEN, element);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(threshold, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (auto &contour : contours)
        if (cv::contourArea(contour) > 500)
            points.push_back(Piece(findContourCentre(contour), letter));
}

void ImageProcessor::findRedPieces(std::vector<Piece> &points, cv::Mat &image) {
    cv::Mat temp, reverseHsvImage, redThreshold;
    cv::cvtColor(image, temp, cv::COLOR_BGR2RGB);
    cv::cvtColor(temp, reverseHsvImage, cv::COLOR_BGR2HSV);

    cv::Scalar redMin{112, 0.2*255, 0.2*255};
    cv::Scalar redMax{127, 255, 255};

    cv::inRange(reverseHsvImage, redMin, redMax, redThreshold);

    findBinaryPieces(points, redThreshold, 'x');
}

void ImageProcessor::findBluePieces(std::vector<Piece> &points, cv::Mat &image) {
    cv::Mat hsvImage, blueThreshold;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    cv::Scalar redMin{75, 0.2*255, 0.2*255};
    cv::Scalar redMax{105, 255, 255};

    cv::inRange(hsvImage, redMin, redMax, blueThreshold);

    findBinaryPieces(points, blueThreshold, 'o');
}

project::BoardInfo ImageProcessor::processImage(cv::Mat &image) {
    // TODO
    // Red Range (reversed) [105, 0.2*255, 0.2*255] -> [135, 255, 255]
    // Blue Range [75, 0.2*255, 0.2*255] -> [105, 255, 255]
    // Magenta Range [135, 0.2 * 255, 0.2 * 255] -> [165, 255, 255]
    std::vector<Piece> points;

    cv::Mat correctedImage;
    cv::warpPerspective(image, correctedImage, mH, cv::Size(600, 600));

    findRedPieces(points, correctedImage);
    findBluePieces(points, correctedImage);

    for (auto &piece : points) {
        std::cout << piece.getX() << ", " << piece.getY() << ", " << piece.getLetter() << std::endl;
        cv::circle(correctedImage, cv::Point(piece.getX(), piece.getY()), 3, cv::Scalar(0, 255, 0), -1);
    }
    return processPieces(points);
}

project::BoardInfo ImageProcessor::processPieces(std::vector<Piece> &points) {
     // Temporary piece points
    // std::vector<Piece> points {Piece(0, 1, 'X'), Piece(20, 30, 'X'), Piece(100, 50, 'O'),
    //                            Piece(50, 70, 'O'), Piece(80, 90, 'X'), Piece(11, 60, 'O')};

    // TODO: Change to Enum
    const float yMin{120.0}, yMax{480.0}, xMin{120.0}, xMax{480.0};

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
    // TODO: add conversion from piece on board to board FoR
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_process");
    ros::NodeHandle n;

    ImageProcessor ip(n);

    ros::spin();

    // return 0;
}
