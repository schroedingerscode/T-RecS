/*************************************************************************************************
									T-RecS Tracking Code 

**************************************************************************************************/
#include "Headers/Serial.h"
#include "Headers/Common.h"

Serial::Serial(std::string _device)
{

    fd_set write_set;
    struct timeval tv;
      tv.tv_sec = 3;
      tv.tv_usec = 0;

    int _fd = -1;
    int ret = -1;

    device_name = _device;
    do
    {
      _fd = open(device_name.c_str(), O_RDWR | O_NOCTTY  );
      printf("Acquiring file descriptor...\n");
    } while (_fd == -1);

    fd = _fd;

    printf("FD is %d.\n", fd);

    do
    {
      FD_ZERO(&write_set);
      FD_SET(fd, &write_set);
      ret = select(fd+1, NULL, &write_set , NULL, &tv);
      printf("Waiting for device...\n");
        if( ret == -1 )
        {
           perror(" Select has crashed ! \n ");
        }
    } while( ret < 1 );

    if( write(fd, " \r", 2) == 2)
        printf("Device is ready.\n");
    else
        printf("Major Error with serial comm. \n");
		
	last_values = new std::string[4];
	last_values[X_FREQ_BUFF] = "x_freq : 0000\r"
	last_values[Y_FREQ_BUFF] = "y_freq : 0000\r"
	last_values[X_POS_BUFF]  = "x_pos : 0\r"
	last_values[Y_POS_BUFF]  = "y_pos : 0\r"
}


int Serial::s_write(std::string _s, unsigned int _type)
{
	if (last_values[_type] == _s)
		return 0;

    if ((int) write(fd, _s.c_str(), _s.size()) == (int)_s.size() )
    {
        //printf("%s\n", _s.c_str());
        return _s.size();
    }
    printf("ERROR: WRITE INVALID\n");
    return -1;
}

void Serial::stop_motion()
{
    char* output_string;
    std::string _s;

    output_string = (char*) malloc(sizeof(char)*20);

    sprintf(output_string, "x_freq: %d\r", 0); // Does sprintf block?
    _s = output_string;

    write(fd, _s.c_str(), _s.size() );

    sprintf(output_string, "y_freq: %d\r", 0); // Does sprintf block?
    _s = output_string;

    write(fd, _s.c_str(), _s.size() );

    free(output_string);
	
	std::cout << "MOTION STOPED" << std::endl;

}
