/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"

#include <iostream>

#define FEATURES           5	// Top no. of features track
#define SEARCH_WINDOW      40	// Optical Flow's search radii 
#define BACKGROUND_HISTORY 3
#define LINE_THICKNESS     1
#define WINDOW_TRACKING    "Optical Flow Window"

#define PI 3.14159265358979323846

/* 'Magic' Values  */
#define TRACK_BUILD_HISTORY		0x1
#define TRACK_SEARCH			0x2
#define TRACK_TARGET_ACQUIRED   0x3
#define TRACK_IDLE				0x4
#define TRACK_REACQUIRE			0x5
#define TRACK_RESET				0x6

#define NO_PRINT				0x0
#define PRINT_POLAR				0x1
#define PRINT_XY				0x2


using namespace cv;
#endif