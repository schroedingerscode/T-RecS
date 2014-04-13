/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers/Tracker.h"

/************************************************************************************************** 
    
    Constructor for the tracker: 
    Initializes with 2 consecutive frames, and puts into background-init state.

        - _frame1 
            An unedited frame from a stream
        - _frame2 
            The next chronological frame from a stream
        - _frame_center_width
        - _frame_center_height
            The frames width/height for use in finding center.

**************************************************************************************************/
Tracker::Tracker(Mat _frame1, Mat _frame2, Point2f _center_frame)
{
  Mat frame_p, frame_c;
  frame_p = _frame1;
  frame_c = _frame2;
  center_frame = _center_frame;

  raw_frame = frame_c;  

  cvtColor( frame_p, prv_frame, CV_BGR2GRAY ); 
  cvtColor( frame_c, cur_frame, CV_BGR2GRAY ); 
  
  Point p1( center_frame.x*0, center_frame.y*0 );
  Point p2( center_frame.x*2, center_frame.y*2 );
    
  mask.create(frame_p.size(), CV_8UC1); // Mask that takes up 100% of the frame (will lower later)
  rectangle(mask, p1, p2, 1,CV_FILLED); // This will be applied on the acquisition phase
										// i.e. sights for our scope

  back_sub = new BackgroundSubtractorMOG(BACKGROUND_HISTORY,3,0.01);
  encoder.set_center(center_frame);

  this->init_bg_history();

}
/************************************************************************************************** 
    
    Virtual function that grabs a raw from from the stream:
    Stores a raw frame in the object, propogates the previous frame/points backward, 
    then stores/converts newst frame for use in tracking.

    - _raw_frame 
        An unedited frame from a stream

	Slow variant proccesses it with a background subtractor that filters noise from 
	  static objects with little apparent motion.
	  Removed secondary filtering technique
	    dilate( cur_frame, cur_frame, Mat() , Point(-1,-1), 1 );
        erode(  cur_frame, cur_frame, Mat() , Point(-1,-1), 1 );  
	  which makes corners stronger, but drops image quality. 

    Fast variant just gets the raw frame and converts it

**************************************************************************************************/
void Slow_Track::get_frame(const Mat _raw_frame) 
{ 
  raw_frame = _raw_frame;
  prv_pts   = cur_pts; 
  cur_frame.copyTo(prv_frame); 

  back_sub->operator()(raw_frame, bg_tmp);  
  
  bg_tmp.copyTo(cur_frame);  

}

void Quick_Track::get_frame(const Mat _raw_frame)
{ 
  raw_frame = _raw_frame;
  prv_pts   = cur_pts; 
  cur_frame.copyTo(prv_frame); 
      
  cvtColor(raw_frame, cur_frame, CV_BGR2GRAY); 
}
/************************************************************************************************** 
    
    Finds a feature to track:
    Uses OpenCV's goodFeaturesToTrack to find a 'good feature' on the most current frame.
    http://docs.opencv.org/modules/imgproc/doc/feature_detection.html#goodfeaturestotrack
    If at least one point to track is found, the target is considered acquired.
    Else, the track will idle, and hopefully return with a frame that DOES have features.

    -  _qlt_lvl 
         Parameter characterizing the minimal accepted quality of image corners. The corners 
        with the quality measure less than the product are rejected. For example, if the best 
        corner has the quality measure = 1500, and the qualityLevel=0.01 , then all the corners 
        with the quality measure less than 15 are rejected.
    - _min_dis
        Minimum possible Euclidean distance between the returned corners.


        Following was removed in version 2.0 for speed.
  //Size subPixWinSize(10,10);
  //TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
  //cornerSubPix(cur_frame, cur_pts, subPixWinSize, Size(-1,-1), termcrit); 

**************************************************************************************************/
void Tracker::find_feature(double _qlt_lvl , double _min_dis) 
{
  goodFeaturesToTrack(cur_frame, cur_pts, FEATURES, _qlt_lvl, _min_dis, mask, 3);

  if( cur_pts.size() == 0 ) 
  {
    reset();
  }

  else 
  {
    tracking_status = TRACK_TARGET_ACQUIRED;
	no_points = false;    
  }

}

/************************************************************************************************** 
    
    Idles for the current iteration:
    Should only be called after a non-eventful find_feature(double, double).
    Essentially performs no operation for the iteration on which it is called, so that a new 
    frame can propagate through.

    - No ARGS

**************************************************************************************************/
void Tracker::idle() 
{
  tracking_status = TRACK_SEARCH;
  no_points = true;
}
/************************************************************************************************** 
    
    Flushes variables:
    Clears status & errors of the points array, then the array itself.

    - No ARGS
    
**************************************************************************************************/
void Tracker::flush() 
{ 
  pts_status.clear(); 
  err.clear();
  cur_pts.clear();
  prv_pts.clear();
  no_points = true;
}

/************************************************************************************************** 
    
    Resets the system:
    Flushes variables, and then leaves the system in a state to build a new bg history. 

    - No ARGS
    
**************************************************************************************************/
void Tracker::reset()
{
  std::cout << "\n\nTHE SYSTEM HAS RESET !!\n\n" << std::endl;
  flush();

  bg_backlog_size = BACKGROUND_HISTORY;
  this->init_bg_history();
}
/**************************************************************************************************
    Uses Optical Flow to track changes in feature location:
    Search for change between prv_frame, cur_frame with calcOpticalFlowPyrLK().
    http://docs.opencv.org/modules/video/doc/motion_analysis_and_object_tracking.html
    If all features are lost, change states to search.
    If new points are exactly the same as the old ones, idle for one iteration.
    If any points are in an error state, reset the tracking.
    
    - No ARGS, but check docs for calcOpticalFlowPyrLK
**************************************************************************************************/
void Tracker::track()
{      
  Size winsize(SEARCH_WINDOW,SEARCH_WINDOW);
  calcOpticalFlowPyrLK(prv_frame, cur_frame, prv_pts , cur_pts, pts_status, err,winsize ,4);

  if(cur_pts.size() == 0 )
  {
	reset();
  }

  encoder.init(cur_pts.size());

  if (cur_pts == prv_pts)
    tracking_status = TRACK_IDLE;
  
  for( i = 0; cur_pts.size()-i > 0 ; i++ )
  {
    if( pts_status[i] <= 0 )
    {
      /* Alternatively go to search... test this later */
      tracking_status = TRACK_RESET;
    }
    encoder.new_point(cur_pts[i], NO_PRINT);
  }

}

/************************************************************************************************** 
    
    Characterizes a background for background subtraction:
    Characterizes by taking current frames, and adding them to a backlog. Once the backlog reaches
    size BACKLOG_HISTORY, it finds constants and erases them. Once built, goes to search state.

    - No ARGS.
    
**************************************************************************************************/
void Tracker::build_bg_history()
{
  if ( bg_backlog_size > 0 )
  {
	
    back_sub->operator()(raw_frame, bg_tmp);  
    //erode(bg_tmp,bg_tmp, Mat());
    //dilate(bg_tmp, bg_tmp, Mat());
	bg_tmp.copyTo(cur_frame);
	
    bg_backlog_size--;
    return;
  }

  tracking_status = TRACK_SEARCH;
  return;
}
  
/************************************************************************************************** 
    
    Sets off new background history:
    Reinitializes the background backlog to set a new background basis, then changes states
    to actually build it.

    - No ARGS.
    
**************************************************************************************************/
void Tracker::init_bg_history()
{
  back_sub->initialize(raw_frame.size(), raw_frame.type());
  bg_backlog_size = BACKGROUND_HISTORY;
  tracking_status = TRACK_BUILD_HISTORY;
}
