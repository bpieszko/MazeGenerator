#include <iostream>
#include <unistd.h>
#include "Algorithm.hpp"
#include "Board.hpp"
#include "Drawer.hpp"

void showUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t./MazeGenerator [height] [width]" << std::endl;
}

bool isWhite(cv::Vec3b colour)
{
    return colour.val[0] == 255 && colour.val[1] == 255 && colour.val[2] == 255;
}

void depth_first_search(const size_t y, const size_t x, cv::Mat res)
{
    //cv::waitKey(500);
    cv::line(res, cv::Point(x, y), cv::Point(x, y), cv::Scalar(0, 0, 255), 1, cv::LINE_8);
    cv::Mat dst = res;
    //cv::imshow("MazeGenerator", dst);  

    if (x == res.rows - 1) {
        cv::imwrite("generated.jpg", res);
        exit(0);
    }

    if (y + 1 < res.cols && isWhite(res.at<cv::Vec3b>(y + 1, x)))
    {
        depth_first_search(y + 1, x, res);
    }
    if (y - 1 > 0 && isWhite(res.at<cv::Vec3b>(y - 1, x)))
    {
        depth_first_search(y - 1, x, res);
    }
    if (x + 1 < res.rows && isWhite(res.at<cv::Vec3b>(y, x + 1)))
    {
        depth_first_search(y, x + 1, res);
    }
    if (x - 1 > 1 && isWhite(res.at<cv::Vec3b>(y, x - 1)))
    {
        depth_first_search(y, x - 1, res);
    }
    
    
    cv::line(res, cv::Point(x, y), cv::Point(x, y), cv::Scalar(255, 255, 255), 1, cv::LINE_8);

    //cv::imshow("MazeGenerator", dst);
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
        if (res.at<cv::Vec3b>(st.y, st.x + 1) == cv::Vec3b(255, 255, 255))
            break;
        cv::line(res, st, st, cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    }

    while (true)
    {
        cv::Point st(res.rows - 2, r(2, res.cols - 2));
        cv::line(res, st, st, cv::Scalar(255, 255, 255), 1, cv::LINE_8);
        if (res.at<cv::Vec3b>(st.y, st.x - 1) == cv::Vec3b(255, 255, 255))
            break;
        cv::line(res, st, st, cv::Scalar(0, 0, 0), 1, cv::LINE_8);
    }

    cv::imwrite("generated.jpg", res);

    cv::imshow("MazeGenerator", res);

    for (size_t y = 2; y <= res.cols - 2; ++y)
    {
        std::cout << res.at<cv::Vec3b>(y, 1) << std::endl;
        if (res.at<cv::Vec3b>(y, 1) == cv::Vec3b(255, 255, 255))
        {
            depth_first_search(y, 1, res);
            std::cout << "End" << std::endl;
            break;
        }
    }

    cv::waitKey(0);

    return 0;
}