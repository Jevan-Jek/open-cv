// Include files for required libraries
#include <stdio.h>

#include "opencv_aee.hpp"
#include "main.hpp"     // You can use this file for declaring defined values and functions
using namespace cv;
void setup(void)
{
    /// Setup camera won't work if you don't have a compatible webcam
    //setupCamera(320, 240);  // Enable the camera for OpenCV
}

int main( int argc, char** argv )
{
    setup();    // Call a setup function to prepare IO and devices

    namedWindow("Photo");   // Create a GUI window called photo

    while(1)    // Main loop to perform image processing
    {
        Mat frame;

        // Can't capture frames without a camera attached. Use static images instead
        while(frame.empty())
        {
            /// Can't capture frames without a camera attached. Use static images instead
            //frame = captureFrame(); // Capture a frame from the camera and store in a new matrix variable
            frame = imread("Images/BlueApple.bmp");


            //detect red
            int min_color_array[5] = {0, 20, 35, 81, 126};
            int max_color_array[5] = {19, 34, 80, 125, 180};

            int i;
            int minimum;
            int maximum;
            int actual_nonZero = 0;
            int nonZeroVar = 0;

            int maximum_var;
            int minimum_var;

            Mat frame_HSV;
            cvtColor(frame, frame_HSV, COLOR_BGR2HSV); // Convert the image to HSV
            Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
            morphologyEx(frame_HSV, frame_HSV, MORPH_OPEN, kernel);

            for (i = 0 ; i < 4 ; i++)
            {

               Mat frame_GREY;

               minimum = min_color_array[i];
               maximum = max_color_array[i];

               //printf("\nMin: %d\nMax: %d\n", minimum, maximum);


               inRange(frame_HSV, Scalar(minimum, 68, 57), Scalar(maximum, 255, 255), frame_GREY);

               nonZeroVar = countNonZero(frame_GREY);

               if (nonZeroVar > actual_nonZero)
               {
                   maximum_var = maximum;
                   minimum_var = minimum;
                   actual_nonZero = nonZeroVar;
               }

            }

                if (minimum_var >= 0 && maximum_var < 20)
                {
                    printf("\nRed");
                }
                else if(minimum_var >= 20 && maximum_var < 35)
                {
                    printf("\nYellow");
                }
                else if(minimum_var >= 35 && maximum_var < 81)
                {
                    printf("\nGreen");
                }
                else if(minimum_var >= 81 && maximum_var < 127)
                {
                    printf("\nBlue");
                }
                else if(minimum_var >= 127 && maximum_var < 181)
                {
                    printf("\nPink");
                }

            //printf("\nMin_VAR: %d\nMax_VAR: %d", minimum_var, maximum_var);



        }


        imshow("Photo", frame); //Display the image in the window

        int key = waitKey(1);   // Wait 1ms for a keypress (required to update windows)

        key = (key==255) ? -1 : key;    // Check if the ESC key has been pressed
        if (key == 27)
            break;
	}

	closeCV();  // Disable the camera and close any windows

	return 0;
}



