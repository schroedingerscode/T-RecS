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
#define MAIN_CAM    "Main Camera Output"
#define FINDER_CAM  "Finder Camera Output"
#define PI 3.14159265358979323846

#define X_FREQ_BUFF 0	// Must be values 0-3
#define Y_FREQ_BUFF 1	
#define X_POS_BUFF  2	
#define Y_POS_BUFF  3

#define MOUNT_MOV_UP	0
#define MOUNT_MOV_DOWN	1
#define MOUNT_MOV_LEFT	0
#define MOUNT_MOV_RIGHT	1

#define TRACKING_SPEED_REGIONS 7 // Must be ODD
/*
	Regions speed decided by formula 
		f(x) = MAX / ( TRACKING_SPEED_REGIONS / (i^3 + 1) )
		
		0 & 6   900
		1 & 5   450
		2 & 4   100
		  3       0

*/	

#define X_MAX_SPEED 900
#define Y_MAX_SPEED 900

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
