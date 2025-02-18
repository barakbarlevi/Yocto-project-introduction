// Include header files which are linked to libraries that should come with the core-image-minimal linux image.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main()
{
	// Settings
	//
	// To get the address of the tmp sensor, bitbake and flash the image onto the board, and use i2cdetect.
	const unsigned char tmp117_addr = 0x48; // ASSUMED I2C address of the TMP117
	
	// Address of the temperature register, which is where we can read the temperature from, is given in its datasheet and is 00h.
	//  This register is 16-bit (2 bytes). It stores the output of the most recent temperature conversion in the sensor,
	//  which we can read in i2c.
	const unsigned char reg_temp = 0x00; // Address of the temperature register
	

	// Address of the i2c device file that we enabled earlier, which points to the actual location of i2c
	// port 5 which is where we have the sensor connected.
	const char filename[] = "/dev/i2c-1"; // Location of the i2c device file
	

	// Handle to the file that we’re about to open. In order to work with that i2c device file,
	// we do it with a file like we would do with every file on linux.
	int file;
	int i;
	int flag = 1;


	// Small buffer that we can send and receive data to and from the sensor
	unsigned char buf[5];
	
	
	// Temperature buffer that we’ll use to do a little math to get a temperature reading in celsius
	uint16_t temp_buf;
	uint16_t temp_buf2;
	
	
	// Floating point variable for reading in celsius
	float temp_c;
	float temp_c2;

	
	
	
	// Open the device file for read/write  and store a handle in file variable.
	// Opening for reading and writing since we’re going to have to both read and write
	// in order to communicate over i2c.
	if ((file = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the bus.\n");
		exit(1);
	}


	// Change to i2c address of TMP117
	// To work with our i2c device file, we need to change its address, using the ioctrl function,
	// so that it points to the i2c device’s address (0x48). When we go to R/W that file, it sends out
	// a command to that particular device on the bus.
	if (ioctl(file, I2C_SLAVE, tmp117_addr) < 0) {
		printf("Failed to acquire bus access or talk to device.\n");
		exit(1);
	}


	// Start the read process by writing the location of the temperature sensor. We do that by writing the
	// address out on the line using the write command. In this case we write to the file using our buffer and we
	// give it the number of bytes from that buffer to write out to the file, that gets written out to the i2c lines.
	// If the write command fails it should return something other than 1.
	// The function should return the number of bytes written to the file.
	buf[0] = 0x00;
	if (write(file, buf, 1) != 1)
	{
		printf("Could not write to i2c device.\n");
		exit(1);
	}


	// Read temperature - Once we finish that writing command we then read from the file,
	// in this case we tell it to read two bytes and store them into our buffer.
	// The number of bytes read should be returned.
	if (read(file, buf, 2) != 2)
	{
		printf("Could not read from i2c device.\n");
		exit(1);
	}


	
	// The i2c timing diagrams in the sensor’s datasheet tell us how to read and write to it.
	// We send out the address and then we send out the register address. And then from there we can read however many
	// bytes from that address in a consecutive fashion
	// which is how we can read 2 bytes that give us the temperature information.
	
	
	
		
	printf("buf[0]: %X\n", buf[0]);
	printf("buf[1]: %X\n", buf[1]);

	printf("buf[0]: ");
	for (i = 0; i < 8; i++) {
	printf("%d", !!((buf[0] << i) & 0x80));
	}
	printf("\n");

	printf("buf[1]: ");
	for (i = 0; i < 8; i++) {
	printf("%d", !!((buf[1] << i) & 0x80));
	}
	printf("\n");


	temp_buf = buf[0] << 8 | buf[1];
	printf("temp_buf =%u\n", temp_buf);
	printf("temp_buf: ");

	for (i = 0; i < 16; i++) {
	printf("%d", !!((temp_buf << i) & 0x80));
	if (i == 7)
	printf(" ");
	}
	printf("\n");

	if (temp_buf > 0x8000)
	{
	temp_buf = ~temp_buf + 0x1;
	flag = -1;
	printf("Considered negative\n");
	}
	else printf("Considered positive\n");

	printf("temp_buf =%u\n", temp_buf);
	printf("temp_buf: ");

	for (i = 0; i < 16; i++) {
	printf("%d", !!((temp_buf << i) & 0x80));
	if (i == 7)
	printf(" ");
	}
	printf("\n");

	temp_c = temp_buf * 0.0078125 * flag;
	printf("temp_c =%.2f\n\n", temp_c);



	

	temp_buf2 = (buf[0] << 4 | buf[1] >> 4);
	printf("temp_buf2 =%u\n", temp_buf2);
	printf("temp_buf2: ");

	for (i = 0; i < 16; i++) {
	printf("%d", !!((temp_buf2 << i) & 0x80));
	if (i == 7)
	printf(" ");
	}
	printf("\n");

	if (temp_buf2 > 0x7FF)
	{
	temp_buf2 |= 0xF000;
	printf("2 Considered negative\n");
	}
	else printf("2 Considered positive\n");

	printf("temp_buf2 =%u\n", temp_buf2);
	printf("temp_buf2: ");

	for (i = 0; i < 16; i++) {
	printf("%d", !!((temp_buf2 << i) & 0x80));
	if (i == 7)
	printf(" ");
	}
	printf("\n");

	temp_c2 = temp_buf2 * 0.0625;
	printf("temp_c2 =%.2f\n", temp_c2);










	// Combine received bytes to single 16-bit value
	// We’ll use the datasheet to see how to do it corretly. 
	// temp_buf = (buf[0] << 4) | (buf[1] >> 4);
	
	// temp_buf = (buf[0]) | (buf[1]);
	
	// If value os negative (2s complement), pad empty 4 bits with 1s
	// if (temp_buf > 0x7FF)
	// {
	//	temp_buf |= 0xF000;
	// }

	
	
	// Convert sensor reading to temperature (celsius)
	// temp_c = temp_buf * 0.0078125;


	// Print results
	// printf("%.2f deg C\n", temp_c);


	return 0;
}
