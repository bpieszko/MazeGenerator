#include <iostream>
#include <unistd.h>
#include "Algorithm.hpp"
#include "Board.hpp"
#include "Drawer.hpp"
#include "ProcessImage.hpp"
#include "DepthFirstSearch.hpp"

void showUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t./MazeGenerator [size]" << std::endl;
}

int main (int argc, char * argv[])
{
    if (argc != 2)
    {
        showUsage();
        return -1;
    }

    Kruskal::Algorithm alg(atoi(argv[1]), atoi(argv[1]));
    alg.generateMaze();
    Kruskal::Board board = alg.getBoard();

    cv::namedWindow("MazeGenerator", cv::WINDOW_AUTOSIZE);

    Kruskal::Drawer dr(atoi(argv[1]), atoi(argv[1]));
    for (int i = 0; i < board.getHeight(); ++i)
    {
        for (int j = 0; j < board.getWidth(); ++j)
        {
            std::vector<bool> neighbour = board.getCell(i, j).getNeighbour();

            if (neighbour.at(Kruskal::RIGHT))
                dr.drawLine({i, j}, {i + 1, j});

            if (neighbour.at(Kruskal::UP))
                dr.drawLine({i, j}, {i, j + 1});
        }
    }

    cv::Mat dst = cv::Mat::zeros(dr.getMat().cols + 2, dr.getMat().rows + 2, CV_8UC3);
    dst.setTo(cv::Scalar(0, 0, 0));
    dr.getMat().copyTo(dst(cv::Rect(1, 1, dr.getMat().cols, dr.getMat().rows)));

    cv::Mat res = cv::Mat::zeros(dst.cols + 2, dst.rows + 2, CV_8UC3);
    res.setTo(cv::Scalar(255, 255, 255));
    dst.copyTo(res(cv::Rect(1, 1, dst.cols, dst.rows)));

    Kruskal::ProcessImage::addStartEnd(res);

    for (size_t y = 2; y <= res.cols - 2; ++y)
    {
        if (res.at<cv::Vec3b>(y, 1) == cv::Vec3b(255, 255, 255))
        {
            Kruskal::DepthFirstSearch::run(y, 1, res);
            break;
        }
    }

    cv::imwrite("generated.jpg", res);

    return 0;
}