#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace cv;
using namespace std;

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
        cout << image.rows << ' ' << image.cols << endl;
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
            char i0 = i + '0';
            imwrite(path + "noise" + i0 + ext, image1);
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
            srcTri[1] = Point2f(src.cols - 1, 0);
            srcTri[2] = Point2f(0, src.rows - 1);

            float r1,r2;
            r1 = (rand() % 100)/100.0;
            r2= (rand() % 100)/100.0;
            dstTri[0] = Point2f(0, src.rows * r2);
            r1= (rand() % 100)/100.0;
            r2= (rand() % 100)/100.0;
            dstTri[1] = Point2f(src.cols -1, 0);
            r1= (rand() % 100)/100.0;
            r2= (rand() % 100)/100.0;
            dstTri[2] = Point2f(0, src.rows -1);

            /// Get the Affine Transform
            warp_mat = getAffineTransform(srcTri, dstTri);

            /// Apply the Affine Transform just found to the src image
            warpAffine(src, warp_dst, warp_mat, warp_dst.size(), INTER_LINEAR, BORDER_TRANSPARENT);

            imwrite(path + "transform" + i0 + ext, warp_dst);

            cout << path << " - " <<  "Successed" << endl;
        }
    }
    return 0;
}