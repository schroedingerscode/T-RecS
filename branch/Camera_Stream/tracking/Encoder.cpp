/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers/Encoder.h"
#include <stdio.h>


Encoder::Encoder()
{
	samples_size = 4;
	backlog = new Point2f[samples_size];
}

void Encoder::set_center(Point2f _center) 
{
	center = _center;
	
	/* Set the region, frequency, and direction spaces for x-axis */
    x_regions  = new int[TRACKING_SPEED_REGIONS];
	x_freqs    = new int[TRACKING_SPEED_REGIONS];
	x_dirs     = new int[TRACKING_SPEED_REGIONS];
	
    int x_max  = ((int) center.x) * 2;
    int x_divs = (int) x_max / TRACKING_SPEED_REGIONS;

    for(int i = 0; i < TRACKING_SPEED_REGIONS; i++)
        x_regions[i] = x_divs*(i+1);
	  
	for(int i = 0; i < (int)(TRACKING_SPEED_REGIONS/2); i++)
	{
	  x_freqs[i] 						   = X_MAX_SPEED/ ((i*i*i)+1);
	  x_freqs[TRACKING_SPEED_REGIONS - i]  = X_MAX_SPEED/ ((i*i*i)+1);
	}
	x_freqs[(TRACKING_SPEED_REGIONS/2)+1]  = 0;
	
	for(int i = 0; i < (int)(TRACKING_SPEED_REGIONS/2); i++)
	{
		x_dirs[i]                          = MOUNT_MOV_UP;
		x_dirs[TRACKING_SPEED_REGIONS - i] = MOUNT_MOV_DOWN;
	}
	x_dirs[(TRACKING_SPEED_REGIONS/2)+1]   = MOUNT_MOV_DOWN;
	
    y_regions  = new int[TRACKING_SPEED_REGIONS];
	y_freqs    = new int[TRACKING_SPEED_REGIONS];
	y_dirs     = new int[TRACKING_SPEED_REGIONS];
	
	/* Set the region, frequency, and direction spaces for y-axis */
    int y_max  = ((int) center.y) * 2;
    int y_divs = (int) y_max / TRACKING_SPEED_REGIONS;

    for(int i = 0; i < TRACKING_SPEED_REGIONS; i++)
		y_regions[i] = y_divs *(i+1);
  
	for(int i = 0; i < (int)(TRACKING_SPEED_REGIONS/2); i++)
	{
	  y_freqs[i] 						   = Y_MAX_SPEED/ ((i*i*i)+1);
	  y_freqs[TRACKING_SPEED_REGIONS - i]  = Y_MAX_SPEED/ ((i*i*i)+1);
	}
	y_freqs[(TRACKING_SPEED_REGIONS/2)+1] = 0;
	
  	for(int i = 0; i < (int)(TRACKING_SPEED_REGIONS/2); i++)
	{
		y_dirs[i]                          = MOUNT_MOV_UP;
		y_dirs[TRACKING_SPEED_REGIONS - i] = MOUNT_MOV_DOWN;
	}
	y_dirs[(TRACKING_SPEED_REGIONS/2)+1]   = MOUNT_MOV_DOWN;
  
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

Point2f Encoder::average_of_sample()
{
  float x_sum = 0, y_sum = 0;

  for (int i=0; i < (int) samples_size; i++)
  {
    x_sum += backlog[i].x;
    y_sum += backlog[i].y;
  }

  x_sum/=samples_size;
  y_sum/=samples_size;

  AoS = Point2f(x_sum, y_sum);

  return AoS;
}


string Encoder::x_speed()
{
    int x = (int) AoS.x;
    int freq;
	
	if (x >= 0 && x < x_regions[0]) 
		freq = freq_array[0];
	else
	{
		for(int i= 0; i< TRACKING_SPEED_REGIONS-1; i++)
		{
			if(x >= x_regions[i] && x < x_regions[i+1])
			{
				freq = x_freqs[i+1];
				break;
			}	
			freq = 0;
		}
	}
	
    char* output_string;
    output_string = (char*) malloc(sizeof(char)*20);
    sprintf(output_string, "x_freq: %d\r", freq);
    string _s = output_string;
    free(output_string);

    return _s;
}

string Encoder::x_direction()
{
    int x = (int) AoS.x;
    int dirs;

	if (x >= 0 && x < x_regions[0]) 
		dirs = x_dirs[0];
	else
	{
		for(int i= 0; i< TRACKING_SPEED_REGIONS-1; i++)
		{
			if(x >= x_regions[i] && x < x_regions[i+1])
			{
				dirs = x_dirs[i+1];
				break;
			}	
			dirs = 0;
		}
	}

    char* output_string;
    output_string = (char*) malloc(sizeof(char)*20);
    sprintf(output_string, "x_pos: %d\r", dirs);
    string _s = output_string;
    free(output_string);


    return _s;
}
string Encoder::y_speed()
{
    int y = (int) AoS.y;
    int freq;

	if (y >= 0 && y < y_regions[0]) 
		freq = freq_array[0];
	else
	{
		for(int i= 0; i< TRACKING_SPEED_REGIONS-1; i++)
		{
			if(y >= y_regions[i] && y < y_regions[i+1])
			{
				freq = y_freqs[i+1];
				break;
			}
			freq = 0;
		}
	}

    char* output_string;
    output_string = (char*) malloc(sizeof(char)*20);
    sprintf(output_string, "y_freq: %d\r", freq);
    string _s = output_string;
    free(output_string);

    return _s;
}

string Encoder::y_direction()
{
    int y = (int) AoS.y;
    int dirs;

	if (y >= 0 && y < y_regions[0]) 
		dirs = y_dirs[0];
	else
	{
		for(int i= 0; i< TRACKING_SPEED_REGIONS-1; i++)
		{
			if(y >= y_regions[i] && y < y_regions[i+1])
			{
				dirs = y_dirs[i+1];
				break;
			}	
			dirs = 0;
		}
	}

    char* output_string;
    output_string = (char*) malloc(sizeof(char)*20);
    sprintf(output_string, "y_pos: %d\r", dirs);
    string _s = output_string;
    free(output_string);


    return _s;
}
