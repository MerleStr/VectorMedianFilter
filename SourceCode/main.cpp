#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <iomanip>


using namespace cv;

// calculating the distanz between four vectors
double sumDis(Vec3b original, Vec3b a, Vec3b b, Vec3b c) {
    double sum;

    double dis1 = norm(original - a);
    double dis2 = norm(original - b);
    double dis3 = norm(original - c);

    sum = dis1 + dis2 + dis3;
    
    //printf("Sum: %lf \n", sum);

    return sum;
}

// calculating the distanz between nine vectors
double sumDis9(Vec3b original, Vec3b a, Vec3b b, Vec3b c, Vec3b d, Vec3b e, Vec3b f, Vec3b g, Vec3b h) {
    double sum;

    double dis1 = norm(original - a);
    double dis2 = norm(original - b);
    double dis3 = norm(original - c);
    double dis4 = norm(original - d);
    double dis5 = norm(original - e);
    double dis6 = norm(original - f);
    double dis7 = norm(original - g);
    double dis8 = norm(original - h);

    sum = dis1 + dis2 + dis3 + dis4 + dis5 + dis6 + dis7 + dis8;

    return sum;
}

// choosing the new vector (VMF, 4 Pixel)
Vec3b disNormal(Vec3b v1, Vec3b v2, Vec3b v3, Vec3b v4) {
    Vec3b p;

    double d1 = sumDis(v1, v2, v3, v4);
    double d2 = sumDis(v2, v1, v3, v4);
    double d3 = sumDis(v3, v1, v2, v4);
    double d4 = sumDis(v4, v1, v2, v3);

    //TODO: when two vectors have the same distant
    //Solution: At the moment the last pixel is the new vector
    if (d1 < d2 && d1 < d3 && d1 < d4) {
        return p = v1;
    }
    else if (d2 < d3 && d2 < d4) {
        return p = v2;
    }
    else if (d3 < d4) {
        return p = v3;
    }
    else {
        return p = v4;
    }
}

// choosing the new vector (VMF, 9 Pixel)
Vec3b disNormal9(Vec3b v1, Vec3b v2, Vec3b v3, Vec3b v4, Vec3b v5, Vec3b v6, Vec3b v7, Vec3b v8, Vec3b v9) {
    Vec3b p;

    double d1 = sumDis9(v1, v2, v3, v4, v5, v6, v7, v8, v9);
    double d2 = sumDis9(v2, v1, v3, v4, v5, v6, v7, v8, v9);
    double d3 = sumDis9(v3, v1, v2, v4, v5, v6, v7, v8, v9);
    double d4 = sumDis9(v4, v1, v2, v3, v5, v6, v7, v8, v9);
    double d5 = sumDis9(v5, v1, v2, v3, v4, v6, v7, v8, v9);
    double d6 = sumDis9(v6, v1, v2, v3, v4, v5, v7, v8, v9);
    double d7 = sumDis9(v7, v1, v2, v3, v4, v5, v6, v8, v9);
    double d8 = sumDis9(v8, v1, v2, v3, v4, v5, v6, v7, v9);
    double d9 = sumDis9(v9, v1, v2, v3, v4, v5, v6, v7, v8);

    if (d1 < d2 && d1 < d3 && d1 < d4 && d1 < d5 && d1 < d6 && d1 < d7 && d1 < d8 && d1 < d9) {
        return p = v1;
    }
    else if (d2 < d3 && d2 < d4 && d2 < d5 && d2 < d6 && d2 < d7 && d2 < d8 && d2 < d9) {
        return p = v2;
    }
    else if (d3 < d4 && d3 < d5 && d3 < d6 && d3 < d7 && d3 < d8 && d3 < d9) {
        return p = v3;
    }
    else if (d4 < d5 && d4 < d6 && d4 < d7 && d4 < d8 && d4 < d9) {
        return p = v4;
    }
    else if (d5 < d6 && d5 < d7 && d5 < d8 && d5 < d9) {
        return p = v5;
    }
    else if (d6 < d7 && d6 < d8 && d6 < d9) {
        return p = v6;
    }
    else if (d7 < d8 && d7 < d9) {
        return p = v7;
    }
    else if (d8 < d9) {
        return p = v8;
    }
    else {
        return p = v9;
    }
}

// choosing the new vector (AVMF, 4 Pixel)
Vec3b disHigh(Vec3b v1, Vec3b v2, Vec3b v3, Vec3b v4) {
    Vec3b p;

    double d1 = sumDis(v1, v2, v3, v4);
    double d2 = sumDis(v2, v1, v3, v4);
    double d3 = sumDis(v3, v1, v2, v4);
    double d4 = sumDis(v4, v1, v2, v3);

    //TODO: when two vectors have the same distant
    if (d1 > d2 && d1 > d3 && d1 > d4) {
        //printf("Eins \n");
        return p = v1;
    }
    else if (d2 > d3 && d2 > d4) {
        //printf("Zwei \n");
        return p = v2;
    }
    else if (d3 > d4) {
        //printf("Drei \n");
        return p = v3;
    }
    else {
        //printf("Vier \n");
        return p = v4;
    }
}

// choosing the new vector (AVMF, 9 Pixel)
Vec3b disHigh9(Vec3b v1, Vec3b v2, Vec3b v3, Vec3b v4, Vec3b v5, Vec3b v6, Vec3b v7, Vec3b v8, Vec3b v9) {
    Vec3b p;

    double d1 = sumDis9(v1, v2, v3, v4, v5, v6, v7, v8, v9);
    double d2 = sumDis9(v2, v1, v3, v4, v5, v6, v7, v8, v9);
    double d3 = sumDis9(v3, v1, v2, v4, v5, v6, v7, v8, v9);
    double d4 = sumDis9(v4, v1, v2, v3, v5, v6, v7, v8, v9);
    double d5 = sumDis9(v5, v1, v2, v3, v4, v6, v7, v8, v9);
    double d6 = sumDis9(v6, v1, v2, v3, v4, v5, v7, v8, v9);
    double d7 = sumDis9(v7, v1, v2, v3, v4, v5, v6, v8, v9);
    double d8 = sumDis9(v8, v1, v2, v3, v4, v5, v6, v7, v9);
    double d9 = sumDis9(v9, v1, v2, v3, v4, v5, v6, v7, v8);

    if (d1 > d2 && d1 > d3 && d1 > d4 && d1 > d5 && d1 > d6 && d1 > d7 && d1 > d8 && d1 > d9) {
        return p = v1;
    }
    else if (d2 > d3 && d2 > d4 && d2 > d5 && d2 > d6 && d2 > d7 && d2 > d8 && d2 > d9) {
        return p = v2;
    }
    else if (d3 > d4 && d3 > d5 && d3 > d6 && d3 > d7 && d3 > d8 && d3 > d9) {
        return p = v3;
    }
    else if (d4 > d5 && d4 > d6 && d4 > d7 && d4 > d8 && d4 > d9) {
        return p = v4;
    }
    else if (d5 > d6 && d5 > d7 && d5 > d8 && d5 > d9) {
        return p = v5;
    }
    else if (d6 > d7 && d6 > d8 && d6 > d9) {
        return p = v6;
    }
    else if (d7 > d8 && d7 > d9) {
        return p = v7;
    }
    else if (d8 > d9) {
        return p = v8;
    }
    else {
        return p = v9;
    }
}

void scaling(Mat imgIn, Mat imgOut, std::string o) {

    int multiRows = (int) imgIn.rows / imgOut.rows;
    int multiCols = (int) imgIn.cols / imgOut.cols;

    for (int r = 0; r < imgOut.rows; r++) {
        for (int c = 0; c < imgOut.cols; c++) {
            Vec3b p;
            
            Vec3b vector1 = imgIn.at<Vec3b>(r * multiRows, c * multiCols);
            Vec3b vector2 = imgIn.at<Vec3b>(r * multiRows, c * multiCols + 1);
            Vec3b vector3 = imgIn.at<Vec3b>(r * multiRows + 1, c * multiCols);
            Vec3b vector4 = imgIn.at<Vec3b>(r * multiRows + 1, c * multiCols + 1);

            if (o == "0") {
                p = disNormal(vector1, vector2, vector3, vector4);
            } else if (o == "1") {
                p = disHigh(vector1, vector2, vector3, vector4);
            }
            else if (o == "2") {
                int col = c * multiCols;
                int row = r * multiRows;
                if (imgIn.cols <= (col + 2)) {
                     col = c * multiCols - 1;
                }
                if (imgIn.rows <= (row + 2)) {
                    row = r * multiRows - 1;
                }

                Vec3b vector5 = imgIn.at<Vec3b>(row, col + 2);
                Vec3b vector6 = imgIn.at<Vec3b>(row + 1, col + 2);
                Vec3b vector7 = imgIn.at<Vec3b>(row + 2, col);
                Vec3b vector8 = imgIn.at<Vec3b>(row + 2, col + 1);
                Vec3b vector9 = imgIn.at<Vec3b>(row + 2, col + 2);
                p = disNormal9(vector1, vector2, vector3, vector4, vector5, vector6, vector7, vector8, vector9);
            }
            else if (o == "3") {
                int col = c * multiCols;
                int row = r * multiRows;
                if (imgIn.cols <= (col + 2)) {
                    col = c * multiCols - 1;
                }
                if (imgIn.rows <= (row + 2)) {
                    row = r * multiRows - 1;
                }
                Vec3b vector5 = imgIn.at<Vec3b>(row, col + 2);
                Vec3b vector6 = imgIn.at<Vec3b>(row + 1, col + 2);
                Vec3b vector7 = imgIn.at<Vec3b>(row + 2, col);
                Vec3b vector8 = imgIn.at<Vec3b>(row + 2, col + 1);
                Vec3b vector9 = imgIn.at<Vec3b>(row + 2, col + 2);
                p = disHigh9(vector1, vector2, vector3, vector4, vector5, vector6, vector7, vector8, vector9);
            }

            imgOut.at<Vec3b>(r, c) = p;
        }
    }
}


int main(int ac, char** av)
{  
    std::cout << "Image Path: " << std::endl;
    std::string imagePath;
    std::getline(std::cin, imagePath);

    std::cout << "Safe Path: " << std::endl;
    std::string safePath;
    std::getline(std::cin, safePath);

    std::cout << "Operator: VMF=0, AVMF=1. 9 Pixel: VMF=2, AMVF=3: " << std::endl;
    std::string o;
    std::getline(std::cin, o);
    
    Mat imgIn = imread(imagePath, IMREAD_COLOR);
    Mat imgOut;
    Mat imgSize = imread(safePath + "bicubic.png", IMREAD_COLOR); // for size comparison

    
    if (imgIn.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    //int rowsSize = imgIn.rows * 0.25; // testing with different scalings
    //int colsSize = imgIn.cols * 0.25;
    int rowsSize = imgSize.rows;
    int colsSize = imgSize.cols;
    
    // calculating the actual image size, because of errors in calculating the vectors 
    if (imgIn.rows % imgSize.rows == 0) {
        rowsSize = imgSize.rows;
    }
    else {
        int rowsCount = (int)imgIn.rows / imgSize.rows;
        rowsSize = imgIn.rows / rowsCount;
    }

    if (imgIn.cols % imgSize.cols == 0) {
        colsSize = imgSize.cols;
    }
    else {
        int colsCount = (int)imgIn.cols / imgSize.cols;
        colsSize = imgIn.cols / colsCount;
    }

    std::cout << "Cols: " << colsSize << std::endl;
    std::cout << "Rows: " << rowsSize << std::endl;

    resize(imgIn, imgOut, Size(colsSize, rowsSize));

    scaling(imgIn, imgOut, o);
    
    Mat upscale;
    resize(imgOut, upscale, Size(imgIn.cols, imgIn.rows), INTER_NEAREST);

    imshow("Display window", imgIn);
    imshow("Resized", imgOut);
    imshow("Upscale", upscale);
    
    std::string endPath;
    if (o == "0") {
        endPath = "vmf";
    }
    else if (o == "1") {
        endPath = "avmf";
    }
    else if (o == "2") {
        endPath = "vmf9";
    }
    else if (o == "3") {
        endPath = "avmf9";
    }

    int k = waitKey(0);
    if (k == 's')
    {   
        std::string safe = safePath + endPath + ".png";
        imwrite(safe, imgOut);

        std::string up = safePath + "/Upscaled/" + endPath + "_upscaled.png";
        imwrite(up, upscale);
    }
    return 0;
}