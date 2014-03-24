/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers\Common.h"
#include "Headers\Tracker.h"
#include "Headers\Encoder.h"

int main(void)
{

  /******************************************************
					Setup for Video capture.
  
  *******************************************************/
  CvScalar line_color = CV_RGB(255,0,0); 


  int frame_center_w,frame_center_h;
  long num_of_frames;
  double format;

  /* Create an object that decodes the input video stream. */
  // ISS_flyover
  // ISS
  // shower
  VideoCapture input_video("C:\\ISS_flyover.mp4"); 
  //
  

  namedWindow(WINDOW_TRACKING, CV_WINDOW_KEEPRATIO);
  TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);

  if (!input_video.isOpened())  
    return -1;  // Return -1 defined as error importing video
  Size S = Size((int) input_video.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) input_video.get(CV_CAP_PROP_FRAME_HEIGHT));

  /* Get the number of frames in the video*/
  input_video.set(CV_CAP_PROP_POS_AVI_RATIO,1.0);
  num_of_frames = input_video.get(CV_CAP_PROP_POS_FRAMES);
  
  format = input_video.get(CV_CAP_PROP_FORMAT );
  input_video.set(CV_CAP_PROP_POS_AVI_RATIO,0);
  frame_center_w = input_video.get(CV_CAP_PROP_FRAME_WIDTH)/2;
  frame_center_h = input_video.get(CV_CAP_PROP_FRAME_HEIGHT)/2;
  Point2f xy_frame_center(frame_center_w , frame_center_h );

  VideoWriter output_video( "C:\\ISS_flyover_result.avi" , format, 30, S );


  /******************************************************
					Begin Initialization 
					  
  *******************************************************/

  Mat frame;
  Mat f_buff1,f_buff2, image;
    
  input_video >> frame;
  frame.copyTo(f_buff1);

  input_video >> frame;
  frame.copyTo(f_buff2);

  Tracker* optTrack = new Quick_Track(f_buff1, f_buff2, xy_frame_center);

  for(long i=0; i < num_of_frames-3; i++)
  {   
    input_video >> frame;
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
	
	if( optTrack->features_on_frame() )
	{
	
	  for( int i = 0; i < optTrack->encoder.size(); i++)
		line( image, xy_frame_center, optTrack->encoder[i], 
		               line_color, LINE_THICKNESS, CV_AA, 0 );
	}

    imshow(WINDOW_TRACKING, image);
	output_video << image;

    char c = (char)waitKey(30);
    if( c == 27 )
      break;
	else if (c == 'r')	
	{
		optTrack->reset();
	}

  }

  return 1;
}