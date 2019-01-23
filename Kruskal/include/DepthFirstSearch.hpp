#pragma once

#include <cstdlib>
#include <opencv2/opencv.hpp>

namespace Kruskal
{

class DepthFirstSearch
{
public:
    static bool run(const size_t y, const size_t x, cv::Mat & mat);

private:
    static bool isColor(cv::Vec3b color, int b, int g, int r);

};

}