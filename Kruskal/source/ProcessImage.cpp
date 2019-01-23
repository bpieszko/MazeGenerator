#include "ProcessImage.hpp"

using namespace Kruskal;
using namespace cv;

void ProcessImage::addStartEnd(Mat & mat)
{
    struct timeval time;
    gettimeofday(&time, 0);
    srand(time.tv_sec * 1000 + time.tv_usec % 1000);
    auto random = [](const int a, const int b)->int { return a + rand() % (b - a + 1); };

    while (true)
    {
        cv::Point st(1, random(2, mat.cols - 2));
        cv::line(mat, st, st, cv::Scalar(255, 255, 255), 1, cv::LINE_8);
        if (mat.at<cv::Vec3b>(st.y, st.x + 1) == cv::Vec3b(255, 255, 255))
            break;
        cv::line(mat, st, st, cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    }

    while (true)
    {
        cv::Point st(mat.rows - 2, random(2, mat.cols - 2));
        cv::line(mat, st, st, cv::Scalar(255, 255, 255), 1, cv::LINE_8);
        if (mat.at<cv::Vec3b>(st.y, st.x - 1) == cv::Vec3b(255, 255, 255))
            break;
        cv::line(mat, st, st, cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    }
}