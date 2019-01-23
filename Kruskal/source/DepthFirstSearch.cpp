#include "DepthFirstSearch.hpp"

using namespace Kruskal;
using namespace cv;

bool DepthFirstSearch::run(const size_t y, const size_t x, Mat & mat)
{
   line(mat, Point(x, y), Point(x, y), Scalar(0, 0, 255), 1, LINE_8);

    if (x == mat.rows - 2)
        return true;

    if (y + 1 < mat.cols && isColor(mat.at<Vec3b>(y + 1, x), 255, 255, 255))
    {
        if (run(y + 1, x, mat))
            return true;
    }
    if (y - 1 > 0 && isColor(mat.at<Vec3b>(y - 1, x), 255, 255, 255))
    {
        if (run(y - 1, x, mat))
            return true;
    }
    if (x + 1 < mat.rows && isColor(mat.at<Vec3b>(y, x + 1), 255, 255, 255))
    {
        if (run(y, x + 1, mat))
            return true;
    }
    if (x - 1 > 1 && isColor(mat.at<Vec3b>(y, x - 1), 255, 255, 255))
    {
        if (run(y, x - 1, mat))
            return true;
    }

    line(mat, Point(x, y), Point(x, y), Scalar(255, 255, 255), 1, LINE_8);
    
    return false;
}

bool DepthFirstSearch::isColor(Vec3b color, int b, int g, int r)
{
    return color.val[0] == b && color.val[1] == g && color.val[2] == r;
}