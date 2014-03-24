/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#ifndef SERIAL_H
#define SERIAL_H

#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


class Serial
{
public:
  Serial(unsigned int _baudrate, std::string _device);
  ~Serial(void);

private:
	std::string device_name;
	unsigned int baudrate;
	unsigned int fd;
};
#endif