#include "Drawer.hpp"

using namespace Kruskal;
using namespace cv;

Drawer::Drawer(const size_t a_height, const size_t a_width)
{
    m_height = (a_height * 2) - 1;
    m_width = (a_width * 2) - 1;
    m_mat = Mat::zeros(m_height, m_width, CV_8UC3);
    m_mat.setTo(Scalar(0, 0, 0));
}

Mat& Drawer::getMat() {
    return m_mat;
}

using pii = std::pair<size_t, size_t>;
void Drawer::drawLine(const pii a, const pii b)
{
   line(m_mat, Point(a.first, a.second) * 2, Point(b.first, b.second) * 2, Scalar(255, 255, 255), 1, cv::LINE_8);
}