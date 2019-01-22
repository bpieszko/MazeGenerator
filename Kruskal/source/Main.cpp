#include <iostream>
#include "Algorithm.hpp"
#include "Board.hpp"
#include "Drawer.hpp"

void showUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t./MazeGenerator [height] [width]" << std::endl;
}

int main (int argc, char * argv[])
{
    if (argc != 3)
    {
        showUsage();
        return -1;
    }

    Kruskal::Algorithm alg(atoi(argv[1]), atoi(argv[2]));
    alg.generateMaze();
    Kruskal::Board board = alg.getBoard();

    cv::namedWindow("MazeGenerator", cv::WINDOW_AUTOSIZE);

    Kruskal::Drawer dr(atoi(argv[1]), atoi(argv[2]));
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

    struct timeval time;
    gettimeofday(&time, 0);
    srand(time.tv_sec * 1000 + time.tv_usec % 1000);
    auto r = [](const int a, const int b)->int { return a + rand() % (b - a + 1); };
    
    while (true)
    {
        cv::Point st(1, r(2, res.cols - 2));
        cv::line(res, st, st, cv::Scalar(255, 255, 255), 1, cv::LINE_8);
        if (res.at<cv::Vec4b>(st.x + 1, st.y) == cv::Vec4b(255, 255, 255, 255))
            break;
        cv::line(res, st, st, cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    }

    while (true)
    {
        cv::Point st(res.rows - 2, r(2, res.cols - 2));
        cv::line(res, st, st, cv::Scalar(255, 255, 255), 1, cv::LINE_8);
        if (res.at<cv::Vec4b>(st.x - 1, st.y) == cv::Vec4b(255, 255, 255, 255))
            break;
        cv::line(res, st, st, cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    }

    cv::imshow("MazeGenerator", res);
    cv::imwrite("generated.jpg", res);

    cv::waitKey(0);

    return 0;
}