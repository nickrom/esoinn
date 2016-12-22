#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace cv;
using namespace std;

double PI = 3.1415926;

cv::Point2f rotate2d(const cv::Point2f& inPoint, const double& angRad)
{
    cv::Point2f outPoint;
    //CW rotation
    outPoint.x = std::cos(angRad*PI/180)*inPoint.x - std::sin(angRad*PI/180)*inPoint.y;
    outPoint.y = std::sin(angRad*PI/180)*inPoint.x + std::cos(angRad*PI/180)*inPoint.y;
    return outPoint;
}

cv::Point2f rotatePoint(const cv::Point2f& inPoint, const cv::Point2f& center, const double& angRad)
{
    return rotate2d(inPoint - center, angRad) + center;
}

int main() {
    String dir = "/home/user/Документы/ESOINN/images/";
    String ext = ".jpg";
    string symbols[] = { "a", "i", "u", "e", "o", "ka","ki","ku","ke","ko", "sa","shi","su","se","so", "ta","chi","tsu",
            "te","to", "na","ni","nu","ne","no", "ha","hi","fu","he","ho", "ma","mi","mu","me","mo", "ya","yu","yo" ,
            "ra","ri","ru","re","ro", "wa","wo" , "n", "ga","gi","gu","ge","go", "za","ji","zu","ze","zo", "da","di",
            "du","de","do", "ba","bi","bu","be","bo", "pa","pi","pu","pe","po", "kya","kyu","kyo", "sha","shu","sho",
            "cha","chu","cho", "nya","nyu","nyo", "hya","hyu","hyo" , "mya","myu","myo" , "rya","ryu","ryo" ,
            "gya","gyu","gyo" , "ja","ju","jo" , "bya","byu","byo" , "pya","pyu","pyo"};
    srand(time(NULL));
    for (String symbol : symbols) {
        String path = dir + symbol + "/";
        Mat image;
        image = imread(path + symbol + ext);   // Read the file
        //cout << image.rows << ' ' << image.cols << endl;
        if (!image.data)                              // Check for invalid input
        {
            cout << "Could not open or find the image" << std::endl;
            return -1;
        }
        for (int i = 0; i < 10; i++) {
            Mat image1 = image.clone();

            for (int y = 0; y < image1.rows; y++) {
                for (int x = 0; x < image1.cols; x++) {
                    int r = rand() % 10;
                    if (r == 0) {
                        Vec3b intensity = image.at<Vec3b>(y, x);
                        unsigned char blue = intensity.val[0];
                        unsigned char green = intensity.val[1];
                        unsigned char red = intensity.val[2];

                        intensity.val[0] = 255 - (blue / 255) * 255;
                        intensity.val[1] = 255 - (green / 255) * 255;
                        intensity.val[2] = 255 - (red / 255) * 255;

                        image1.at<Vec3b>(y, x) = intensity;
                    }

                }
            }
            std::string buffer;
            std::stringstream out;
            out << i;
            buffer = out.str();
            Mat new_image1;
            resize(image1,new_image1,cvSize(50,50));
            imwrite(path + "noise" + buffer + ext, new_image1);
            Point2f srcTri[3];
            Point2f dstTri[3];

            Mat rot_mat(2, 3, CV_32FC1);
            Mat warp_mat(2, 3, CV_32FC1);
            Mat src, warp_dst, warp_rotate_dst;

            /// Load the image
            src = imread(path + symbol + ext, -1);

            /// Set the dst image the same type and size as src
            warp_dst = Mat::zeros(src.rows, src.cols, src.type());
            memset(warp_dst.data, 255, warp_dst.rows * warp_dst.cols * 3);

            /// Set your 3 points to calculate the  Affine Transform
            srcTri[0] = Point2f(0, 0);
            srcTri[1] = Point2f(src.cols-1, 0);
            srcTri[2] = Point2f(0, src.rows-1);

            float r1,r2;
            int angle = rand()%25;
            double sign = pow(-1.0, (double)(rand()%2 + 1));
            dstTri[0] = rotatePoint(srcTri[0],cvPoint(src.rows/2,src.rows/2), sign*angle);
            dstTri[1] = rotatePoint(srcTri[1],cvPoint(src.rows/2,src.rows/2), sign*angle);
            dstTri[2] = rotatePoint(srcTri[2],cvPoint(src.rows/2,src.rows/2), sign*angle);

            /// Get the Affine Transform
            warp_mat = getAffineTransform(srcTri, dstTri);

            /// Apply the Affine Transform just found to the src image
            warpAffine(src, warp_dst, warp_mat, warp_dst.size(), INTER_LINEAR, BORDER_TRANSPARENT);

//            angle=rand()%45;
//            dstTri[0]=rotatePoint(srcTri[0],cvPoint(src.cols/2,src.rows/2),angle);
//
//            dstTri[1]=rotatePoint(srcTri[1],cvPoint(src.cols/2,src.rows/2),angle);
//            dstTri[2]=rotatePoint(srcTri[2],cvPoint(src.cols/2,src.rows/2),angle);
//            warp_mat = getAffineTransform(srcTri, dstTri);
//            warpAffine(warp_dst, warp_rotate_dst, warp_mat, warp_rotate_dst.size(), INTER_LINEAR, BORDER_TRANSPARENT);
//            int r3 = (rand()%45);
//            double r4 = (rand()%8)/10.0;
//            double sign = pow(-1.0, (double)(rand()%2 + 1));
//            Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
//            double angle = sign*(double)r3;
//            double scale = r4;
//
//            rot_mat = getRotationMatrix2D( center, angle, scale );
//            warpAffine(src, warp_rotate_dst, rot_mat, warp_rotate_dst.size(),INTER_LINEAR, BORDER_TRANSPARENT);
//            warpAffine(warp_rotate_dst, warp_dst, warp_mat, warp_dst.size(), INTER_LINEAR, BORDER_TRANSPARENT);

            Mat new_image;
            resize(warp_dst,new_image,cvSize(50,50));
            imwrite(path + "transform" + buffer + ext, new_image);
        }
        if (image.rows != image.cols)
            cout << path << " - " <<  "Successed" << endl;
    }
    return 0;
}