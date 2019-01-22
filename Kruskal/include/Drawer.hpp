#pragma once

#include <opencv2/opencv.hpp>

using pii = std::pair<size_t, size_t>;

namespace Kruskal
{

class Drawer
{
public:
    Drawer(const size_t height, const size_t width);

    void drawLine(const pii a, const pii b);
    cv::Mat& getMat();

private:
    size_t m_height;
    size_t m_width;

    cv::Mat m_mat;
};

}