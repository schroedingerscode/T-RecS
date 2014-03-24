/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers\Serial.h"


Serial::Serial(unsigned int _baudrate, std::string _device)
{
	baudrate = _baudrate;
	device_name = _device;
	//fd = open(device_name, O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		perror(device_name.c_str());
		exit(-1);
	}
}


Serial::~Serial(void)
{
}
