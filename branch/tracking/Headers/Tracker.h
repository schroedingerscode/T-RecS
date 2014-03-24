/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#ifndef TRACKER_H
#define TRACKER_H

#include "Headers\Common.h"
#include "Headers\Encoder.h"

class Tracker
{
public:
  Tracker(Mat , Mat, Point2f);
  ~Tracker() { delete back_sub; }

  Ptr<BackgroundSubtractorMOG> back_sub;
  Encoder encoder;
  
  void init_bg_history();
  void build_bg_history();

  virtual void get_frame(const Mat) = 0;

  void find_feature(double,double);
  void track();
  
  void reset();  
  void idle();

  unsigned int status() {return tracking_status;}
  bool features_on_frame() { return !no_points; }

protected:
  Mat raw_frame;
  Mat prv_frame;
  Mat cur_frame;
  Mat bg_tmp, back;
  Mat mask;
  
  vector<Point2f> prv_pts;
  vector<Point2f> cur_pts;
  vector<uchar> pts_status;
  vector<float> err;

  Point2f center_frame;			/* Position of center of frame  */
  unsigned int bg_backlog_size;	/* Current size of the backlog 
									for background subtraction      */
  unsigned int tracking_status;	/* State for the tracking subsystem
									as defined in config.h          */
  unsigned int i;				/* Iterator variable */
  bool no_points;
  
  void flush();
};

class Slow_Track : public Tracker 
{
public:
	Slow_Track(Mat _frame1, Mat _frame2, Point2f _center_frame) 
		: Tracker(_frame1 , _frame2, _center_frame){}
	void get_frame(const Mat);
};

class Quick_Track : public Tracker
{
public:
	Quick_Track(Mat _frame1, Mat _frame2, Point2f _center_frame) 
		: Tracker(_frame1 , _frame2, _center_frame){}
	void get_frame(const Mat);
};
#endif