/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#ifndef SERIAL_H
#define SERIAL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>


class Serial
{
public:
  Serial(std::string _device);
  int s_write(std::string _s, unsigned int _type);
  void stop_motion();

private:
  std::string device_name;  
  std::string * last_values;  
  unsigned int fd;
	
};
#endif
