#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#define DEV_ADDRESS 0x68

#define w 0.98
#define devName "/dev/i2c-0"
#define dt 0.02

float dist(float a,float b)
{
    return sqrt((a*a)+(b*b));
}

float get_y_rotation(float x,float y,float z)
{
  float radians = atan2(x, dist(y,z));
    return (-((radians*180)/M_PI));
}

float get_x_rotation(float x,float y,float z)
{
    float radians = atan2(y, dist(x,z));
    return ((radians*180)/M_PI);
}

float getFiltered(float gyro,float acc,float pre)
{
	return (w*((gyro*dt)+pre)+((1.0-w)*acc));
}

signed short int vertical(signed short int grad,float z)
{	
    if(z>0)
	{
	  if (grad > 0)
	     return (180-grad);
	  else return (-180-grad);
	}
    else
	return grad;
}


int main()
{	
// Open up the I2C bus
int file = open(devName, O_RDWR);
if (file == -1)
{
perror(devName);
exit(1);
}
// Specify the address of the slave device.
if (ioctl(file, I2C_SLAVE, DEV_ADDRESS) < 0)
{
perror("Failed to acquire bus access and/or talk to slave");
exit(1);
}

i2c_smbus_write_byte_data(file,0x6b,0);

float last_y_filtered=0.0;
float last_x_filtered=0.0;
FILE *fileOut;

signed short int gyroskop_xout,gyroskop_yout,gyroskop_zout,beschleunigung_xout,beschleunigung_yout,beschleunigung_zout;

float beschleunigung_xout_skaliert,beschleunigung_yout_skaliert,beschleunigung_zout_skaliert;

float acc_x_rotate,acc_y_rotate,gyro_Y_angle,gyro_X_angle;

while(1)
{ 
gyroskop_xout =(signed short int) i2c_smbus_read_word_data(file,0x43-1);
gyroskop_yout =(signed short int) i2c_smbus_read_word_data(file,0x45-1);
gyroskop_zout =(signed short int) i2c_smbus_read_word_data(file,0x47-1);
 
 
beschleunigung_xout =(signed short int)i2c_smbus_read_word_data(file,0x3b-1);
beschleunigung_yout =(signed short int)i2c_smbus_read_word_data(file,0x3d-1);
beschleunigung_zout =(signed short int)i2c_smbus_read_word_data(file,0x3f-1);
 
beschleunigung_xout_skaliert= ((beschleunigung_xout-928.5252226)/16384.0);
beschleunigung_yout_skaliert= ((beschleunigung_yout-109.1877551)/16384.0);
beschleunigung_zout_skaliert= ((beschleunigung_zout+533.510942)/16384.0);
 

acc_x_rotate = get_x_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert);

acc_y_rotate = get_y_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert);

gyro_Y_angle=((gyroskop_yout-180.5369914)/131.0);

float filteredY= getFiltered(gyro_Y_angle,acc_y_rotate,last_y_filtered);

gyro_X_angle=((gyroskop_xout+305.52)/131.0);

float filteredX= getFiltered(gyro_X_angle,acc_x_rotate,last_x_filtered);

fileOut=fopen ("/tmp/Pos", "w");
fprintf(fileOut,"%d %d",vertical((short int)lround(filteredX),beschleunigung_zout_skaliert),vertical((short int)lround(filteredY),beschleunigung_zout_skaliert));
fclose(fileOut);

last_y_filtered=filteredY;
last_x_filtered=filteredX;
usleep(dt*1000000);
}
}
