#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

int main() {
    Mat image;
    image = imread("/home/user/ClionProjects/opencv_my_example/2.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    Mat image1 = image.clone();

    srand (time(NULL));

    for (int y=0;y<image1.rows;y++) {
        for (int x=0;x<image1.cols;x++) {
            int r = rand() % 15;
            if (r == 0) {
                Vec3b intensity = image.at<Vec3b>(x, y);
                unsigned char blue = intensity.val[0];
                unsigned char green = intensity.val[1];
                unsigned char red = intensity.val[2];

                //cout << intensity << endl;

                intensity.val[0]= 255 - (intensity.val[0]/255) * 255;
                intensity.val[1]= 255 - (intensity.val[1]/255) * 255;
                intensity.val[2]= 255 - (intensity.val[2]/255) * 255;

                image1.at<Vec3b>(Point(x, y)) = intensity;
                cout << intensity << endl;
            }

        }
    }
    imshow("Display new window", image1);

    Point2f srcTri[3];
    Point2f dstTri[3];

    Mat rot_mat( 2, 3, CV_32FC1 );
    Mat warp_mat( 2, 3, CV_32FC1 );
    Mat src, warp_dst, warp_rotate_dst;

    /// Load the image
    src = imread("/home/user/ClionProjects/opencv_my_example/2.jpg", 1);

    /// Set the dst image the same type and size as src
    warp_dst = Mat::zeros( src.rows, src.cols, src.type() );
    memset(warp_dst.data, 255, warp_dst.rows * warp_dst.cols * 3);

    /// Set your 3 points to calculate the  Affine Transform
    srcTri[0] = Point2f( 0,0 );
    srcTri[1] = Point2f( src.cols - 1, 0 );
    srcTri[2] = Point2f( 0, src.rows - 1 );

    dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
    dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
    dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );

    /// Get the Affine Transform
    warp_mat = getAffineTransform( srcTri, dstTri );

    /// Apply the Affine Transform just found to the src image
    warpAffine( src, warp_dst, warp_mat, warp_dst.size(), INTER_LINEAR, BORDER_TRANSPARENT  );



    namedWindow("3 example", CV_WINDOW_AUTOSIZE );
    imshow("3 example", warp_dst );
    waitKey(0);
    return 0;
}