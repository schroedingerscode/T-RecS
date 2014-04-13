/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers/Common.h"
#include "Headers/Tracker.h"
#include "Headers/Encoder.h"
#include "Headers/Serial.h"
int null()
{

  /******************************************************
					Setup for Video capture.
  
  *******************************************************/
  CvScalar line_color = CV_RGB(255,0,0); 


  int frame_center_w,frame_center_h;

  /* Create an object that decodes the input video stream. */
  // ISS_flyover
  // ISS
  // shower
  VideoCapture main_video(2);
  main_video.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  main_video.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
  main_video.set(CV_CAP_PROP_FPS, 15);
  //main_video.set(CV_CAP_PROP_EXPOSURE, 1000);

  VideoCapture finder_video(1);
  finder_video.set(CV_CAP_PROP_FRAME_WIDTH, 320);
  finder_video.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
  finder_video.set(CV_CAP_PROP_FPS, 15);

  Serial stellaris("/dev/ttyACM0");
  
  namedWindow(MAIN_CAM, CV_WINDOW_KEEPRATIO);
  //namedWindow(FINDER_CAM, CV_WINDOW_KEEPRATIO);

  if (!main_video.isOpened())
    return -1;  // Return -1 defined as error importing video

  if (!finder_video.isOpened())
    return -1;  // Return -1 defined as error importing video


  /* Get the number of frames in the video*/
  double format = main_video.get(CV_CAP_PROP_FORMAT );
  Size S = Size((int) main_video.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                           (int) main_video.get(CV_CAP_PROP_FRAME_HEIGHT));
  frame_center_w = main_video.get(CV_CAP_PROP_FRAME_WIDTH)/2;
  frame_center_h = main_video.get(CV_CAP_PROP_FRAME_HEIGHT)/2;
  Point2f xy_frame_center(frame_center_w , frame_center_h );


  VideoWriter main_video_out("/home/michael/Desktop/result.avi",
                           format, 30, S);

  bool stop_motion = false;
  /******************************************************
					Begin Initialization 
					  
  *******************************************************/

  Mat frame, finder_frame;
  Mat f_buff1,f_buff2, image, finder_image;
    
  main_video >> frame;
  frame.copyTo(f_buff1);

  main_video >> frame;
  frame.copyTo(f_buff2);

  finder_video >> finder_frame;

  Tracker* optTrack = new Quick_Track(f_buff1, f_buff2, xy_frame_center);

  for(;;)
  {   
    main_video >> frame;
    finder_video >> finder_frame;

    finder_frame.copySize(finder_image);
	frame.copyTo(image);
	
    optTrack->get_frame(image);

	switch( optTrack->status() )
	{
	  case TRACK_BUILD_HISTORY:
		optTrack->build_bg_history();
		break;

	  case TRACK_SEARCH:
  	    optTrack->find_feature(.8,.05);
        break;

	  case TRACK_TARGET_ACQUIRED:
	    optTrack->track();
	    break;

	  case TRACK_IDLE:
		  optTrack->idle();
		  break;
		  		
	  case TRACK_RESET: default:
        optTrack->reset();
		break;
	}
	
    if( optTrack->features_on_frame() && !stop_motion )
	{
	
	  for( int i = 0; i < optTrack->encoder.size(); i++)
		line( image, xy_frame_center, optTrack->encoder[i], 
		               line_color, LINE_THICKNESS, CV_AA, 0 );

      optTrack->encoder.average_of_sample();

      stellaris.s_write( optTrack->encoder.x_direction() , X_POS_BUFF );
      stellaris.s_write( optTrack->encoder.x_speed() , X_FREQ_BUFF );

      stellaris.s_write( optTrack->encoder.y_direction() , Y_POS_BUFF);
      stellaris.s_write( optTrack->encoder.y_speed() , Y_FREQ_BUFF);

	}

    imshow(MAIN_CAM, image);
    //imshow(FINDER_CAM, finder_image);
    main_video_out << image;

    char c = (char)waitKey(1);
    if( c == 27 )
      break;
	else if (c == 'r')	
	{
		optTrack->reset();
	}
    else if (c == ' ')
    {
        stop_motion = !stop_motion;
		
		if (stop_motion) 
			stellaris.stop_motion();
    }

  }

  return 1;
}
