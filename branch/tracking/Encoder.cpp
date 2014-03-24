/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers\Encoder.h"

Encoder::Encoder()
{
	samples_size = 4;
	backlog = new Point2f[samples_size];
}

void Encoder::set_center(Point2f _center) 
  {
	  center = _center;
  }

void Encoder::init(unsigned int _samples_size)
{

	if (samples_size < _samples_size) 
	{
		delete backlog;
		backlog = new Point2f[_samples_size];
	}
	
	samples_size = _samples_size;
	index = 0;
}

void Encoder::new_point(Point2f _new_position, unsigned int _print_select)
  {
	  position = _new_position;
	  backlog[index % samples_size] = position;
	  index = (index+1) % samples_size;

	  switch(_print_select)
	  {
		  case PRINT_POLAR:
			  polar_coordinate();
			  break;

		  case PRINT_XY:
			  xy_coordinate();
			  break;

		  case NO_PRINT: default:
			  break;
	  }
  }