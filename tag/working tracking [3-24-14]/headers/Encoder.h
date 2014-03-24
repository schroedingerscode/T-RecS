/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#ifndef ENCODER_H
#define ENCODER_H

#include "Headers\Common.h"

class Encoder{
public:

  Encoder();

  void init(unsigned int);
  void new_point(Point2f _new_position, unsigned int _print_select = PRINT_POLAR);
  void set_center(Point2f );
  int size() {return samples_size; }

  Point2f average_of_sample(); /* Where we filter and stuff */

  Point2f operator[](int idx) 
  {
	  return backlog[idx];
  }

  Point2f position,center;
  unsigned int index, samples_size;
  double hippo_news, angle;
  Point2f * backlog;
  

private:

	void polar_coordinate()
	{
		angle = 180 * atan2( 
							(double) (position.y - center.y), (double) (position.x - center.x) 
							) / PI;

		hippo_news  = hypot(position.x - center.x, position.y - center.y);

		std::cout	<< "Magnitude : " << hippo_news << "\n"
					<< "Angle     : " << angle      << "\n"
					<< std::endl;
	}

	void xy_coordinate()
	{
		std::cout	<< "X : " << position.x << "\n"
					<< "Y : " << position.y << "\n"
					<< std::endl;
	}
};
#endif