#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>


int main(int argc, char** argv)
{
    const auto modelFile = "face_detection_yunet_2023mar_int8.onnx";
    auto detector = cv::FaceDetectorYN::create(modelFile, "", cv::Size(320, 320));

    const auto image = cv::imread("input.jpg");

    cv::Mat workImage;
    {
        auto size = std::max(image.rows, image.cols);
        auto scale = 640.0f / size;
        auto width = static_cast<int>(image.cols * scale);
        auto height = static_cast<int>(image.rows * scale);
        cv::resize(image, workImage, cv::Size(width, height));
    }
    std::cout << image.size() << std::endl;

    detector->setInputSize(workImage.size());

    cv::Mat faces;
    detector->detect(workImage, faces);

    if (faces.rows == 0) {
        std::cout << "no faces are detected." << std::endl;
    }
    
    faces.convertTo(faces, CV_32S);

    for (auto i = 0; i < faces.rows; ++i) {
        auto face = faces.row(i);
        std::cout << face << std::endl;
        cv::rectangle(workImage, 
            cv::Rect(face.at<int>(0), face.at<int>(1), face.at<int>(2), face.at<int>(3)), 
            cv::Scalar(0, 0, 255), 2);
    }

    cv::imwrite("result.png", workImage);

    return 0;
}