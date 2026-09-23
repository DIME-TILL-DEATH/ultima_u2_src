/******************************************************************************
SFE_LSM9DS0.h
SFE_LSM9DS0 Library Header File
Jim Lindblom @ SparkFun Electronics
Original Creation Date: February 14, 2014 (Happy Valentines Day!)
https://github.com/sparkfun/LSM9DS0_Breakout

This file prototypes the LSM9DS0 class, implemented in SFE_LSM9DS0.cpp. In
addition, it defines every register in the LSM9DS0 (both the Gyro and Accel/
Magnetometer registers).

Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Pro 3.3V/8MHz
	LSM9DS0 Breakout Version: 1.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/
#ifndef __SFE_LSM9DS0_H__
#define __SFE_LSM9DS0_H__

////////////////////////////
// LSM9DS0 Gyro Registers //
////////////////////////////
#define WHO_AM_I_G			0x0F
#define CTRL_REG1_G			0x20
#define CTRL_REG2_G			0x21
#define CTRL_REG3_G			0x22
#define CTRL_REG4_G			0x23
#define CTRL_REG5_G			0x24
#define REFERENCE_G			0x25
#define STATUS_REG_G		0x27
#define OUT_X_L_G			0x28
#define OUT_X_H_G			0x29
#define OUT_Y_L_G			0x2A
#define OUT_Y_H_G			0x2B
#define OUT_Z_L_G			0x2C
#define OUT_Z_H_G			0x2D
#define FIFO_CTRL_REG_G		0x2E
#define FIFO_SRC_REG_G		0x2F
#define INT1_CFG_G			0x30
#define INT1_SRC_G			0x31
#define INT1_THS_XH_G		0x32
#define INT1_THS_XL_G		0x33
#define INT1_THS_YH_G		0x34
#define INT1_THS_YL_G		0x35
#define INT1_THS_ZH_G		0x36
#define INT1_THS_ZL_G		0x37
#define INT1_DURATION_G		0x38

//////////////////////////////////////////
// LSM9DS0 Accel/Magneto (XM) Registers //
//////////////////////////////////////////
#define OUT_TEMP_L_XM		0x05
#define OUT_TEMP_H_XM		0x06
#define STATUS_REG_M		0x07
#define OUT_X_L_M			0x08
#define OUT_X_H_M			0x09
#define OUT_Y_L_M			0x0A
#define OUT_Y_H_M			0x0B
#define OUT_Z_L_M			0x0C
#define OUT_Z_H_M			0x0D
#define WHO_AM_I_XM			0x0F
#define INT_CTRL_REG_M		0x12
#define INT_SRC_REG_M		0x13
#define INT_THS_L_M			0x14
#define INT_THS_H_M			0x15
#define OFFSET_X_L_M		0x16
#define OFFSET_X_H_M		0x17
#define OFFSET_Y_L_M		0x18
#define OFFSET_Y_H_M		0x19
#define OFFSET_Z_L_M		0x1A
#define OFFSET_Z_H_M		0x1B
#define REFERENCE_X			0x1C
#define REFERENCE_Y			0x1D
#define REFERENCE_Z			0x1E
#define CTRL_REG0_XM		0x1F
#define CTRL_REG1_XM		0x20
#define CTRL_REG2_XM		0x21
#define CTRL_REG3_XM		0x22
#define CTRL_REG4_XM		0x23
#define CTRL_REG5_XM		0x24
#define CTRL_REG6_XM		0x25
#define CTRL_REG7_XM		0x26
#define STATUS_REG_A		0x27
#define OUT_X_L_A			0x28
#define OUT_X_H_A			0x29
#define OUT_Y_L_A			0x2A
#define OUT_Y_H_A			0x2B
#define OUT_Z_L_A			0x2C
#define OUT_Z_H_A			0x2D
#define FIFO_CTRL_REG		0x2E
#define FIFO_SRC_REG		0x2F
#define INT_GEN_1_REG		0x30
#define INT_GEN_1_SRC		0x31
#define INT_GEN_1_THS		0x32
#define INT_GEN_1_DURATION	0x33
#define INT_GEN_2_REG		0x34
#define INT_GEN_2_SRC		0x35
#define INT_GEN_2_THS		0x36
#define INT_GEN_2_DURATION	0x37
#define CLICK_CFG			0x38
#define CLICK_SRC			0x39
#define CLICK_THS			0x3A
#define TIME_LIMIT			0x3B
#define TIME_LATENCY		0x3C
#define TIME_WINDOW			0x3D
#define ACT_THS				0x3E
#define ACT_DUR				0x3F

// The LSM9DS0 functions over both I2C or SPI. This library supports both.
// But the interface mode used must be sent to the LSM9DS0 constructor. Use
// one of these two as the first parameter of the constructor.
enum interface_mode
{
	MODE_SPI,
	MODE_I2C,
};

class LSM9DS0
{
public:

       typedef void (*io_init_t)();
       typedef void (*io_read_bytes_t)(uint8_t reg, uint8_t* dest, uint8_t count);
       typedef void (*io_write_bytes_t)(uint8_t reg, uint8_t* src, uint8_t count);
       typedef void (*io_transac_bytest)(uint8_t* src, uint8_t* dest, uint8_t count);
       typedef void (*io_dealy_mc_t)(uint32_t val );

       typedef struct
       {
	 io_init_t init ;

	 io_read_bytes_t     gyro_read_bytes ;
	 io_write_bytes_t    gyro_write_bytes ;
	 io_transac_bytest   gyro_transact ;

	 io_read_bytes_t     accel_mag_read_bytes ;
	 io_write_bytes_t    accel_mag_write_bytes ;


	 io_dealy_mc_t delay_mc ;
       } io_t ;



	// gyro_scale defines the possible full-scale ranges of the gyroscope:
	enum gyro_scale
	{
		G_SCALE_245DPS,		// 00:  245 degrees per second
		G_SCALE_500DPS,		// 01:  500 dps
		G_SCALE_2000DPS,	// 10:  2000 dps
	};
	// accel_scale defines all possible FSR's of the accelerometer:
	enum accel_scale
	{
		A_SCALE_2G,	// 000:  2g
		A_SCALE_4G,	// 001:  4g
		A_SCALE_6G,	// 010:  6g
		A_SCALE_8G,	// 011:  8g
		A_SCALE_16G	// 100:  16g
	};
	// mag_scale defines all possible FSR's of the magnetometer:
	enum mag_scale
	{
		M_SCALE_2GS,	// 00:  2Gs
		M_SCALE_4GS, 	// 01:  4Gs
		M_SCALE_8GS,	// 10:  8Gs
		M_SCALE_12GS,	// 11:  12Gs
	};
	// gyro_odr defines all possible data rate/bandwidth combos of the gyro:
	enum gyro_odr
	{							// ODR (Hz) --- Cutoff
		G_ODR_95_BW_125  = 0x0, //   95         12.5
		G_ODR_95_BW_25   = 0x1, //   95          25
		// 0x2 and 0x3 define the same data rate and bandwidth
		G_ODR_190_BW_125 = 0x4, //   190        12.5
		G_ODR_190_BW_25  = 0x5, //   190         25
		G_ODR_190_BW_50  = 0x6, //   190         50
		G_ODR_190_BW_70  = 0x7, //   190         70
		G_ODR_380_BW_20  = 0x8, //   380         20
		G_ODR_380_BW_25  = 0x9, //   380         25
		G_ODR_380_BW_50  = 0xA, //   380         50
		G_ODR_380_BW_100 = 0xB, //   380         100
		G_ODR_760_BW_30  = 0xC, //   760         30
		G_ODR_760_BW_35  = 0xD, //   760         35
		G_ODR_760_BW_50  = 0xE, //   760         50
		G_ODR_760_BW_100 = 0xF, //   760         100
	};
	// accel_oder defines all possible output data rates of the accelerometer:
	enum accel_odr
	{
		A_POWER_DOWN, 	// Power-down mode (0x0)
		A_ODR_3125,		// 3.125 Hz	(0x1)
		A_ODR_625,		// 6.25 Hz (0x2)
		A_ODR_125,		// 12.5 Hz (0x3)
		A_ODR_25,		// 25 Hz (0x4)
		A_ODR_50,		// 50 Hz (0x5)
		A_ODR_100,		// 100 Hz (0x6)
		A_ODR_200,		// 200 Hz (0x7)
		A_ODR_400,		// 400 Hz (0x8)
		A_ODR_800,		// 800 Hz (9)
		A_ODR_1600		// 1600 Hz (0xA)
	};

      // accel_abw defines all possible anti-aliasing filter rates of the accelerometer:
	enum accel_abw
	{
		A_ABW_773,		// 773 Hz (0x0)
		A_ABW_194,		// 194 Hz (0x1)
		A_ABW_362,		// 362 Hz (0x2)
		A_ABW_50,		//  50 Hz (0x3)
	};


	// mag_oder defines all possible output data rates of the magnetometer:
	enum mag_odr
	{
		M_ODR_3125,	// 3.125 Hz (0x00)
		M_ODR_625,	// 6.25 Hz (0x01)
		M_ODR_125,	// 12.5 Hz (0x02)
		M_ODR_25,	// 25 Hz (0x03)
		M_ODR_50,	// 50 (0x04)
		M_ODR_100,	// 100 Hz (0x05)
	};

	// We'll store the gyro, accel, and magnetometer readings in a series of
	// public class variables. Each sensor gets three variables -- one for each
	// axis. Call readGyro(), readAccel(), and readMag() first, before using
	// these variables!
	// These values are the RAW signed 16-bit readings from the sensors.
	int16_t gx, gy, gz; // x, y, and z axis readings of the gyroscope
	int16_t ax, ay, az; // x, y, and z axis readings of the accelerometer
	int16_t mx, my, mz; // x, y, and z axis readings of the magnetometer
        int16_t temperature;
	float abias[3];
        float gbias[3];
        uint8_t gTest ;		// Read the gyro WHO_AM_I
       	uint8_t xmTest ;	// Read the accel/mag WHO_AM_I

	// LSM9DS0 -- LSM9DS0 class constructor
	// The constructor will set up a handful of private variables, and set the
	// communication mode as well.
	// Input:
	//	- interface = Either MODE_SPI or MODE_I2C, whichever you're using
	//				to talk to the IC.
	//	- gAddr = If MODE_I2C, this is the I2C address of the gyroscope.
	// 				If MODE_SPI, this is the chip select pin of the gyro (CSG)
	//	- xmAddr = If MODE_I2C, this is the I2C address of the accel/mag.
	//				If MODE_SPI, this is the cs pin of the accel/mag (CSXM)
	inline LSM9DS0( const io_t& io ): io(io)
           {
           }
	
	// begin() -- Initialize the gyro, accelerometer, and magnetometer.
	// This will set up the scale and output rate of each sensor. It'll also
	// "turn on" every sensor and every axis of every sensor.
	// Input:
	//	- gScl = The scale of the gyroscope. This should be a gyro_scale value.
	//	- aScl = The scale of the accelerometer. Should be a accel_scale value.
	//	- mScl = The scale of the magnetometer. Should be a mag_scale value.
	//	- gODR = Output data rate of the gyroscope. gyro_odr value.
	//	- aODR = Output data rate of the accelerometer. accel_odr value.
	//	- mODR = Output data rate of the magnetometer. mag_odr value.
	// Output: The function will return an unsigned 16-bit value. The most-sig
	//		bytes of the output are the WHO_AM_I reading of the accel. The
	//		least significant two bytes are the WHO_AM_I reading of the gyro.
	// All parameters have a defaulted value, so you can call just "begin()".
	// Default values are FSR's of:  245DPS, 2g, 2Gs; ODRs of 95 Hz for 
	// gyro, 100 Hz for accelerometer, 100 Hz for magnetometer.
	// Use the return value of this function to verify communication.
	inline uint16_t begin(gyro_scale gScl = G_SCALE_245DPS, 
				accel_scale aScl = A_SCALE_2G, mag_scale mScl = M_SCALE_2GS,
				gyro_odr gODR = G_ODR_95_BW_125, accel_odr aODR = A_ODR_50, 
				mag_odr mODR = M_ODR_50)
           {
	       	// Store the given scales in class variables. These scale variables
	       	// are used throughout to calculate the actual g's, DPS,and Gs's.
	       	gScale = gScl;
	       	aScale = aScl;
	       	mScale = mScl;
	
	       // Once we have the scale values, we can calculate the resolution
	       // of each sensor. That's what these functions are for. One for each sensor
	       calcgRes(); // Calculate DPS / ADC tick, stored in gRes variable
	       calcmRes(); // Calculate Gs / ADC tick, stored in mRes variable
	       calcaRes(); // Calculate g / ADC tick, stored in aRes variable
	
	       io.init();

	       // To verify communication, we can read from the WHO_AM_I register of
	       // each device. Store those in a variable so we can return them.
	       gTest = gReadByte(WHO_AM_I_G);		// Read the gyro WHO_AM_I
	       xmTest = xmReadByte(WHO_AM_I_XM);	// Read the accel/mag WHO_AM_I
	
	       // Gyro initialization stuff:
	       initGyro();	// This will "turn on" the gyro. Setting up interrupts, etc.
	       setGyroODR(gODR); // Set the gyro output data rate and bandwidth.
	       setGyroScale(gScale); // Set the gyro range
	
	       // Accelerometer initialization stuff:
	       initAccel(); // "Turn on" all axes of the accel. Set up interrupts, etc.
	       setAccelODR(aODR); // Set the accel data rate.
	       setAccelScale(aScale); // Set the accel range.
	
	       // Magnetometer initialization stuff:
	       initMag(); // "Turn on" all axes of the mag. Set up interrupts, etc.
	       setMagODR(mODR); // Set the magnetometer output data rate.
	       setMagScale(mScale); // Set the magnetometer's range.
	
	       // Once everything is initialized, return the WHO_AM_I registers we read:
	       return (xmTest << 8) | gTest;
           }
	
	// readGyro() -- Read the gyroscope output registers.
	// This function will read all six gyroscope output registers.
	// The readings are stored in the class' gx, gy, and gz variables. Read
	// those _after_ calling readGyro().
	inline void readGyro()
           {
	       uint8_t temp[6]; // We'll read six bytes from the gyro into temp
	       gReadBytes(OUT_X_L_G, temp, 6); // Read 6 bytes, beginning at OUT_X_L_G
	       gx = (temp[1] << 8) | temp[0]; // Store x-axis values into gx
	       gy = (temp[3] << 8) | temp[2]; // Store y-axis values into gy
	       gz = (temp[5] << 8) | temp[4]; // Store z-axis values into gz
           }
	
	// readAccel() -- Read the accelerometer output registers.
	// This function will read all six accelerometer output registers.
	// The readings are stored in the class' ax, ay, and az variables. Read
	// those _after_ calling readAccel().
	inline void readAccel()
           {
              uint8_t temp[6]; // We'll read six bytes from the accelerometer into temp	
              xmReadBytes(OUT_X_L_A, temp, 6); // Read 6 bytes, beginning at OUT_X_L_A
              ax = (temp[1] << 8) | temp[0]; // Store x-axis values into ax
              ay = (temp[3] << 8) | temp[2]; // Store y-axis values into ay
              az = (temp[5] << 8) | temp[4]; // Store z-axis values into az
           }
	
	// readMag() -- Read the magnetometer output registers.
	// This function will read all six magnetometer output registers.
	// The readings are stored in the class' mx, my, and mz variables. Read
	// those _after_ calling readMag().
	inline void readMag()
           {
              uint8_t temp[6]; // We'll read six bytes from the mag into temp	
              xmReadBytes(OUT_X_L_M, temp, 6); // Read 6 bytes, beginning at OUT_X_L_M
              mx = (temp[1] << 8) | temp[0]; // Store x-axis values into mx
              my = (temp[3] << 8) | temp[2]; // Store y-axis values into my
              mz = (temp[5] << 8) | temp[4]; // Store z-axis values into mz
           }

	// readTemp() -- Read the temperature output register.
	// This function will read two temperature output registers.
	// The combined readings are stored in the class' temperature variables. Read
	// those _after_ calling readTemp().
	inline void readTemp()
           {
              uint8_t temp[2]; // We'll read two bytes from the temperature sensor into temp	
              xmReadBytes(OUT_TEMP_L_XM, temp, 2); // Read 2 bytes, beginning at OUT_TEMP_L_M
              temperature = (((int16_t) temp[1] << 12) | temp[0] << 4 ) >> 4; // Temperature is a 12-bit signed integer
           }
	

	inline void readSensors()
	   {
	      readGyro();
	      readAccel();
	      readMag();
	   }

	// calcGyro() -- Convert from RAW signed 16-bit value to degrees per second
	// This function reads in a signed 16-bit value and returns the scaled
	// DPS. This function relies on gScale and gRes being correct.
	// Input:
	//	- gyro = A signed 16-bit raw reading from the gyroscope.
	inline float calcGyro(int16_t gyro)
           {
              // Return the gyro raw reading times our pre-calculated DPS / (ADC tick):
              return gRes * gyro; 
           }
	
	// calcAccel() -- Convert from RAW signed 16-bit value to gravity (g's).
	// This function reads in a signed 16-bit value and returns the scaled
	// g's. This function relies on aScale and aRes being correct.
	// Input:
	//	- accel = A signed 16-bit raw reading from the accelerometer.
	inline float calcAccel(int16_t accel)
           {
              // Return the accel raw reading times our pre-calculated g's / (ADC tick):
              return aRes * accel;
           }
	
	// calcMag() -- Convert from RAW signed 16-bit value to Gauss (Gs)
	// This function reads in a signed 16-bit value and returns the scaled
	// Gs. This function relies on mScale and mRes being correct.
	// Input:
	//	- mag = A signed 16-bit raw reading from the magnetometer.
	inline float calcMag(int16_t mag)
           {
	      // Return the mag raw reading times our pre-calculated Gs / (ADC tick):
	      return mRes * mag;
           }
	
	// setGyroScale() -- Set the full-scale range of the gyroscope.
	// This function can be called to set the scale of the gyroscope to 
	// 245, 500, or 200 degrees per second.
	// Input:
	// 	- gScl = The desired gyroscope scale. Must be one of three possible
	//		values from the gyro_scale enum.
	inline void setGyroScale(gyro_scale gScl)
           {
	      // We need to preserve the other bytes in CTRL_REG4_G. So, first read it:
	      uint8_t temp = gReadByte(CTRL_REG4_G);
	      // Then mask out the gyro scale bits:
	      temp &= 0xFF^(0x3 << 4);
	      // Then shift in our new scale bits:
	      temp |= gScl << 4;
	      // And write the new register value back into CTRL_REG4_G:
	      gWriteByte(CTRL_REG4_G, temp);
	
	      // We've updated the sensor, but we also need to update our class variables
	      // First update gScale:
	      gScale = gScl;
	      // Then calculate a new gRes, which relies on gScale being set correctly:
	      calcgRes();
           }
	
	// setAccelScale() -- Set the full-scale range of the accelerometer.
	// This function can be called to set the scale of the accelerometer to
	// 2, 4, 6, 8, or 16 g's.
	// Input:
	// 	- aScl = The desired accelerometer scale. Must be one of five possible
	//		values from the accel_scale enum.
	inline void setAccelScale(accel_scale aScl)
           {
	      // We need to preserve the other bytes in CTRL_REG2_XM. So, first read it:
	      uint8_t temp = xmReadByte(CTRL_REG2_XM);
	      // Then mask out the accel scale bits:
	      temp &= 0xFF^(0x3 << 3);
	      // Then shift in our new scale bits:
	      temp |= aScl << 3;
	      // And write the new register value back into CTRL_REG2_XM:
	      xmWriteByte(CTRL_REG2_XM, temp);
	
	      // We've updated the sensor, but we also need to update our class variables
	      // First update aScale:
	      aScale = aScl;
	      // Then calculate a new aRes, which relies on aScale being set correctly:
	      calcaRes();
           }
	
	// setMagScale() -- Set the full-scale range of the magnetometer.
	// This function can be called to set the scale of the magnetometer to
	// 2, 4, 8, or 12 Gs.
	// Input:
	// 	- mScl = The desired magnetometer scale. Must be one of four possible
	//		values from the mag_scale enum.
	inline void setMagScale(mag_scale mScl)
           {
	      // We need to preserve the other bytes in CTRL_REG6_XM. So, first read it:
	      uint8_t temp = xmReadByte(CTRL_REG6_XM);
	      // Then mask out the mag scale bits:
	      temp &= 0xFF^(0x3 << 5);
	      // Then shift in our new scale bits:
	      temp |= mScl << 5;
	      // And write the new register value back into CTRL_REG6_XM:
	      xmWriteByte(CTRL_REG6_XM, temp);
	
	      // We've updated the sensor, but we also need to update our class variables
	      // First update mScale:
	      mScale = mScl;
	      // Then calculate a new mRes, which relies on mScale being set correctly:
	      calcmRes();
           }
	
	// setGyroODR() -- Set the output data rate and bandwidth of the gyroscope
	// Input:
	//	- gRate = The desired output rate and cutoff frequency of the gyro.
	//		Must be a value from the gyro_odr enum (check above, there're 14).
	inline void setGyroODR(gyro_odr gRate)
           {
	      // We need to preserve the other bytes in CTRL_REG1_G. So, first read it:
	      uint8_t temp = gReadByte(CTRL_REG1_G);
	      // Then mask out the gyro ODR bits:
	      temp &= 0xFF^(0xF << 4);
	      // Then shift in our new ODR bits:
	      temp |= (gRate << 4);
	      // And write the new register value back into CTRL_REG1_G:
	      gWriteByte(CTRL_REG1_G, temp);
           }
	
	// setAccelODR() -- Set the output data rate of the accelerometer
	// Input:
	//	- aRate = The desired output rate of the accel.
	//		Must be a value from the accel_odr enum (check above, there're 11).
	inline void setAccelODR(accel_odr aRate)
           {
              // We need to preserve the other bytes in CTRL_REG1_XM. So, first read it:
              uint8_t temp = xmReadByte(CTRL_REG1_XM);
              // Then mask out the accel ODR bits:
              temp &= 0xFF^(0xF << 4);
              // Then shift in our new ODR bits:
              temp |= (aRate << 4);
              // And write the new register value back into CTRL_REG1_XM:
              xmWriteByte(CTRL_REG1_XM, temp);
           } 	

        // setAccelABW() -- Set the anti-aliasing filter rate of the accelerometer
	// Input:
	//	- abwRate = The desired anti-aliasing filter rate of the accel.
	//		Must be a value from the accel_abw enum (check above, there're 4).
	inline void setAccelABW(accel_abw abwRate)
           {
              // We need to preserve the other bytes in CTRL_REG2_XM. So, first read it:
              uint8_t temp = xmReadByte(CTRL_REG2_XM);
              // Then mask out the accel ABW bits:
              temp &= 0xFF^(0x3 << 7);
              // Then shift in our new ODR bits:
              temp |= (abwRate << 7);
              // And write the new register value back into CTRL_REG2_XM:
              xmWriteByte(CTRL_REG2_XM, temp);
           }

	
	// setMagODR() -- Set the output data rate of the magnetometer
	// Input:
	//	- mRate = The desired output rate of the mag.
	//		Must be a value from the mag_odr enum (check above, there're 6).
	inline void setMagODR(mag_odr mRate)
           {
	      // We need to preserve the other bytes in CTRL_REG5_XM. So, first read it:
	      uint8_t temp = xmReadByte(CTRL_REG5_XM);
	      // Then mask out the mag ODR bits:
	      temp &= 0xFF^(0x7 << 2);
	      // Then shift in our new ODR bits:
	      temp |= (mRate << 2);
	      // And write the new register value back into CTRL_REG5_XM:
	      xmWriteByte(CTRL_REG5_XM, temp);
           }	

	// configGyroInt() -- Configure the gyro interrupt output.
	// Triggers can be set to either rising above or falling below a specified
	// threshold. This function helps setup the interrupt configuration and 
	// threshold values for all axes.
	// Input:
	//	- int1Cfg = A 8-bit value that is sent directly to the INT1_CFG_G
	//		register. This sets AND/OR and high/low interrupt gen for each axis
	//	- int1ThsX = 16-bit interrupt threshold value for x-axis
	//	- int1ThsY = 16-bit interrupt threshold value for y-axis
	//	- int1ThsZ = 16-bit interrupt threshold value for z-axis
	//	- duration = Duration an interrupt holds after triggered. This value
	// 		is copied directly into the INT1_DURATION_G register.
	// Before using this function, read about the INT1_CFG_G register and
	// the related INT1* registers in the LMS9DS0 datasheet.
	void configGyroInt(uint8_t int1Cfg, uint16_t int1ThsX = 0,  uint16_t int1ThsY = 0, uint16_t int1ThsZ = 0, uint8_t duration = 0)
           {
	      gWriteByte(INT1_CFG_G, int1Cfg);
	      gWriteByte(INT1_THS_XH_G, (int1ThsX & 0xFF00) >> 8);
	      gWriteByte(INT1_THS_XL_G, (int1ThsX & 0xFF));
	      gWriteByte(INT1_THS_YH_G, (int1ThsY & 0xFF00) >> 8);
	      gWriteByte(INT1_THS_YL_G, (int1ThsY & 0xFF));
	      gWriteByte(INT1_THS_ZH_G, (int1ThsZ & 0xFF00) >> 8);
	      gWriteByte(INT1_THS_ZL_G, (int1ThsZ & 0xFF));
	      if (duration)
		   gWriteByte(INT1_DURATION_G, 0x80 | duration);
	      else
		   gWriteByte(INT1_DURATION_G, 0x00);
           }

	// This is a function that uses the FIFO to accumulate sample of accelerometer and gyro data, average
	// them, scales them to  gs and deg/s, respectively, and then passes the biases to the main sketch
	// for subtraction from all subsequent data. There are no gyro and accelerometer bias registers to store
	// the data as there are in the ADXL345, a precursor to the LSM9DS0, or the MPU-9150, so we have to
	// subtract the biases ourselves. This results in a more accurate measurement in general and can
	// remove errors due to imprecise or varying initial placement. Calibration of sensor data in this manner
	// is good practice.
	inline void calLSM9DS0(float * gbias, float * abias)
           {  
              uint8_t data[6] = {0, 0, 0, 0, 0, 0};
              int16_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};
              int samples, ii;
  
              // First get gyro bias
              uint8_t c = gReadByte(CTRL_REG5_G);
              gWriteByte(CTRL_REG5_G, c | 0x40);         // Enable gyro FIFO  
              io.delay_mc(20);                                 // Wait for change to take effect
              gWriteByte(FIFO_CTRL_REG_G, 0x20 | 0x1F);  // Enable gyro FIFO stream mode and set watermark at 32 samples
              io.delay_mc(1000);  // delay 1000 milliseconds to collect FIFO samples
  
              samples = (gReadByte(FIFO_SRC_REG_G) & 0x1F); // Read number of stored samples

              for(ii = 0; ii < samples ; ii++)
                {            // Read the gyro data stored in the FIFO
                   gReadBytes(OUT_X_L_G,  &data[0], 6);
                   gyro_bias[0] += (((int16_t)data[1] << 8) | data[0]);
                   gyro_bias[1] += (((int16_t)data[3] << 8) | data[2]);
                   gyro_bias[2] += (((int16_t)data[5] << 8) | data[4]);
                }  

              gyro_bias[0] /= samples; // average the data
              gyro_bias[1] /= samples; 
              gyro_bias[2] /= samples; 
  
              gbias[0] = (float)gyro_bias[0]*gRes;  // Properly scale the data to get deg/s
              gbias[1] = (float)gyro_bias[1]*gRes;
              gbias[2] = (float)gyro_bias[2]*gRes;
  
              c = gReadByte(CTRL_REG5_G);
              gWriteByte(CTRL_REG5_G, c & ~0x40);  // Disable gyro FIFO  
              io.delay_mc(20);
              gWriteByte(FIFO_CTRL_REG_G, 0x00);   // Enable gyro bypass mode
  

              //  Now get the accelerometer biases
              c = xmReadByte(CTRL_REG0_XM);
              xmWriteByte(CTRL_REG0_XM, c | 0x40);      // Enable accelerometer FIFO  
              io.delay_mc(20);                                // Wait for change to take effect
              xmWriteByte(FIFO_CTRL_REG, 0x20 | 0x1F);  // Enable accelerometer FIFO stream mode and set watermark at 32 samples
              io.delay_mc(1000);  // delay 1000 milliseconds to collect FIFO samples

              samples = (xmReadByte(FIFO_SRC_REG) & 0x1F); // Read number of stored accelerometer samples

              for(ii = 0; ii < samples ; ii++) 
                {          // Read the accelerometer data stored in the FIFO
                   xmReadBytes(OUT_X_L_A, &data[0], 6);
                   accel_bias[0] += (((int16_t)data[1] << 8) | data[0]);
                   accel_bias[1] += (((int16_t)data[3] << 8) | data[2]);
                   accel_bias[2] += (((int16_t)data[5] << 8) | data[4]) - (int16_t)(1./aRes); // Assumes sensor facing up!
                }  

              accel_bias[0] /= samples; // average the data
              accel_bias[1] /= samples; 
              accel_bias[2] /= samples; 
  
              abias[0] = (float)accel_bias[0]*aRes; // Properly scale data to get gs
              abias[1] = (float)accel_bias[1]*aRes;
              abias[2] = (float)accel_bias[2]*aRes;

              c = xmReadByte(CTRL_REG0_XM);
              xmWriteByte(CTRL_REG0_XM, c & ~0x40);    // Disable accelerometer FIFO  
              io.delay_mc(20);
              xmWriteByte(FIFO_CTRL_REG, 0x00);       // Enable accelerometer bypass mode
           }


//private:
	// xmAddress and gAddress store the I2C address or SPI chip select pin
	// for each sensor.
	uint8_t xmAddress, gAddress;
	// interfaceMode keeps track of whether we're using SPI or I2C to talk
	interface_mode interfaceMode;
	
	// gScale, aScale, and mScale store the current scale range for each 
	// sensor. Should be updated whenever that value changes.
	gyro_scale gScale;
	accel_scale aScale;
	mag_scale mScale;
	
	// gRes, aRes, and mRes store the current resolution for each sensor. 
	// Units of these values would be DPS (or g's or Gs's) per ADC tick.
	// This value is calculated as (sensor scale) / (2^15).
	float gRes, aRes, mRes;
	
	// initGyro() -- Sets up the gyroscope to begin reading.
	// This function steps through all five gyroscope control registers.
	// Upon exit, the following parameters will be set:
	//	- CTRL_REG1_G = 0x0F: Normal operation mode, all axes enabled. 
	//		95 Hz ODR, 12.5 Hz cutoff frequency.
	//	- CTRL_REG2_G = 0x00: HPF set to normal mode, cutoff frequency
	//		set to 7.2 Hz (depends on ODR).
	//	- CTRL_REG3_G = 0x88: Interrupt enabled on INT_G (set to push-pull and
	//		active high). Data-ready output enabled on DRDY_G.
	//	- CTRL_REG4_G = 0x00: Continuous update mode. Data LSB stored in lower
	//		address. Scale set to 245 DPS. SPI mode set to 4-wire.
	//	- CTRL_REG5_G = 0x00: FIFO disabled. HPF disabled.
	inline void initGyro()
           {
              /* CTRL_REG1_G sets output data rate, bandwidth, power-down and enables
              Bits[7:0]: DR1 DR0 BW1 BW0 PD Zen Xen Yen
                     DR[1:0] - Output data rate selection
		00=95Hz, 01=190Hz, 10=380Hz, 11=760Hz
              BW[1:0] - Bandwidth selection (sets cutoff frequency)
              	 Value depends on ODR. See datasheet table 21.
              PD - Power down enable (0=power down mode, 1=normal or sleep mode)
              Zen, Xen, Yen - Axis enable (o=disabled, 1=enabled)	*/
              gWriteByte(CTRL_REG1_G, 0x0F); // Normal mode, enable all axes
	
              /* CTRL_REG2_G sets up the HPF
              Bits[7:0]: 0 0 HPM1 HPM0 HPCF3 HPCF2 HPCF1 HPCF0
              HPM[1:0] - High pass filter mode selection
              	00=normal (reset reading HP_RESET_FILTER, 01=ref signal for filtering,
              	10=normal, 11=autoreset on interrupt
              HPCF[3:0] - High pass filter cutoff frequency
              	Value depends on data rate. See datasheet table 26.
              */
              gWriteByte(CTRL_REG2_G, 0x00); // Normal mode, high cutoff frequency
	
              /* CTRL_REG3_G sets up interrupt and DRDY_G pins
              Bits[7:0]: I1_IINT1 I1_BOOT H_LACTIVE PP_OD I2_DRDY I2_WTM I2_ORUN I2_EMPTY
              I1_INT1 - Interrupt enable on INT_G pin (0=disable, 1=enable)
              I1_BOOT - Boot status available on INT_G (0=disable, 1=enable)
              H_LACTIVE - Interrupt active configuration on INT_G (0:high, 1:low)
              PP_OD - Push-pull/open-drain (0=push-pull, 1=open-drain)
              I2_DRDY - Data ready on DRDY_G (0=disable, 1=enable)
              I2_WTM - FIFO watermark interrupt on DRDY_G (0=disable 1=enable)
              I2_ORUN - FIFO overrun interrupt on DRDY_G (0=disable 1=enable)
              I2_EMPTY - FIFO empty interrupt on DRDY_G (0=disable 1=enable) */
              // Int1 enabled (pp, active low), data read on DRDY_G:
              gWriteByte(CTRL_REG3_G, 0x88); 
	
              /* CTRL_REG4_G sets the scale, update mode
              Bits[7:0] - BDU BLE FS1 FS0 - ST1 ST0 SIM
              BDU - Block data update (0=continuous, 1=output not updated until read
              BLE - Big/little endian (0=data LSB @ lower address, 1=LSB @ higher add)
              FS[1:0] - Full-scale selection
              	00=245dps, 01=500dps, 10=2000dps, 11=2000dps
              ST[1:0] - Self-test enable
              	00=disabled, 01=st 0 (x+, y-, z-), 10=undefined, 11=st 1 (x-, y+, z+)
              SIM - SPI serial interface mode select
              	0=4 wire, 1=3 wire */
              gWriteByte(CTRL_REG4_G, 0x00); // Set scale to 245 dps
	
              /* CTRL_REG5_G sets up the FIFO, HPF, and INT1
              Bits[7:0] - BOOT FIFO_EN - HPen INT1_Sel1 INT1_Sel0 Out_Sel1 Out_Sel0
              BOOT - Reboot memory content (0=normal, 1=reboot)
              FIFO_EN - FIFO enable (0=disable, 1=enable)
              HPen - HPF enable (0=disable, 1=enable)
              INT1_Sel[1:0] - Int 1 selection configuration
              Out_Sel[1:0] - Out selection configuration */
              gWriteByte(CTRL_REG5_G, 0x00);
	
              // Temporary !!! For testing !!! Remove !!! Or make useful !!!
              configGyroInt(0x2A, 0, 0, 0, 0); // Trigger interrupt when above 0 DPS...
}
	
	// initAccel() -- Sets up the accelerometer to begin reading.
	// This function steps through all accelerometer related control registers.
	// Upon exit these registers will be set as:
	//	- CTRL_REG0_XM = 0x00: FIFO disabled. HPF bypassed. Normal mode.
	//	- CTRL_REG1_XM = 0x57: 100 Hz data rate. Continuous update.
	//		all axes enabled.
	//	- CTRL_REG2_XM = 0x00:  2g scale. 773 Hz anti-alias filter BW.
	//	- CTRL_REG3_XM = 0x04: Accel data ready signal on INT1_XM pin.
	inline void initAccel()
           {
              /* CTRL_REG0_XM (0x1F) (Default value: 0x00)
              Bits (7-0): BOOT FIFO_EN WTM_EN 0 0 HP_CLICK HPIS1 HPIS2
              BOOT - Reboot memory content (0: normal, 1: reboot)
              FIFO_EN - Fifo enable (0: disable, 1: enable)
              WTM_EN - FIFO watermark enable (0: disable, 1: enable)
              HP_CLICK - HPF enabled for click (0: filter bypassed, 1: enabled)
              HPIS1 - HPF enabled for interrupt generator 1 (0: bypassed, 1: enabled)
              HPIS2 - HPF enabled for interrupt generator 2 (0: bypassed, 1 enabled)   */
              xmWriteByte(CTRL_REG0_XM, 0x00);
	
              /* CTRL_REG1_XM (0x20) (Default value: 0x07)
              Bits (7-0): AODR3 AODR2 AODR1 AODR0 BDU AZEN AYEN AXEN
              AODR[3:0] - select the acceleration data rate:
              	0000=power down, 0001=3.125Hz, 0010=6.25Hz, 0011=12.5Hz, 
              	0100=25Hz, 0101=50Hz, 0110=100Hz, 0111=200Hz, 1000=400Hz,
              	1001=800Hz, 1010=1600Hz, (remaining combinations undefined).
              BDU - block data update for accel AND mag
              	0: Continuous update
              	1: Output registers aren't updated until MSB and LSB have been read.
              AZEN, AYEN, and AXEN - Acceleration x/y/z-axis enabled.
              	0: Axis disabled, 1: Axis enabled									 */	
              xmWriteByte(CTRL_REG1_XM, 0x57); // 100Hz data rate, x/y/z all enabled
	
              //Serial.println(xmReadByte(CTRL_REG1_XM));
              /* CTRL_REG2_XM (0x21) (Default value: 0x00)
              Bits (7-0): ABW1 ABW0 AFS2 AFS1 AFS0 AST1 AST0 SIM
              ABW[1:0] - Accelerometer anti-alias filter bandwidth
              	00=773Hz, 01=194Hz, 10=362Hz, 11=50Hz
              AFS[2:0] - Accel full-scale selection
              	000=+/-2g, 001=+/-4g, 010=+/-6g, 011=+/-8g, 100=+/-16g
              AST[1:0] - Accel self-test enable
              	00=normal (no self-test), 01=positive st, 10=negative st, 11=not allowed
              SIM - SPI mode selection
              	0=4-wire, 1=3-wire													 */
              xmWriteByte(CTRL_REG2_XM, 0x00); // Set scale to 2g
	
              /* CTRL_REG3_XM is used to set interrupt generators on INT1_XM
              Bits (7-0): P1_BOOT P1_TAP P1_INT1 P1_INT2 P1_INTM P1_DRDYA P1_DRDYM P1_EMPTY
              */
              // Accelerometer data ready on INT1_XM (0x04)
              xmWriteByte(CTRL_REG3_XM, 0x04); 
           }
	
	// initMag() -- Sets up the magnetometer to begin reading.
	// This function steps through all magnetometer-related control registers.
	// Upon exit these registers will be set as:
	//	- CTRL_REG4_XM = 0x04: Mag data ready signal on INT2_XM pin.
	//	- CTRL_REG5_XM = 0x14: 100 Hz update rate. Low resolution. Interrupt
	//		requests don't latch. Temperature sensor disabled.
	//	- CTRL_REG6_XM = 0x00:  2 Gs scale.
	//	- CTRL_REG7_XM = 0x00: Continuous conversion mode. Normal HPF mode.
	//	- INT_CTRL_REG_M = 0x09: Interrupt active-high. Enable interrupts.
	inline void initMag()
           {
               /* CTRL_REG5_XM enables temp sensor, sets mag resolution and data rate
               Bits (7-0): TEMP_EN M_RES1 M_RES0 M_ODR2 M_ODR1 M_ODR0 LIR2 LIR1
               TEMP_EN - Enable temperature sensor (0=disabled, 1=enabled)
               M_RES[1:0] - Magnetometer resolution select (0=low, 3=high)
               M_ODR[2:0] - Magnetometer data rate select
               	000=3.125Hz, 001=6.25Hz, 010=12.5Hz, 011=25Hz, 100=50Hz, 101=100Hz
               LIR2 - Latch interrupt request on INT2_SRC (cleared by reading INT2_SRC)
               	0=interrupt request not latched, 1=interrupt request latched
               LIR1 - Latch interrupt request on INT1_SRC (cleared by readging INT1_SRC)
               	0=irq not latched, 1=irq latched 									 */
               xmWriteByte(CTRL_REG5_XM, 0x94); // Mag data rate - 100 Hz, enable temperature sensor
	
               /* CTRL_REG6_XM sets the magnetometer full-scale
               Bits (7-0): 0 MFS1 MFS0 0 0 0 0 0
               MFS[1:0] - Magnetic full-scale selection
               00:+/-2Gauss, 01:+/-4Gs, 10:+/-8Gs, 11:+/-12Gs							 */
               xmWriteByte(CTRL_REG6_XM, 0x00); // Mag scale to +/- 2GS
	
               /* CTRL_REG7_XM sets magnetic sensor mode, low power mode, and filters
               AHPM1 AHPM0 AFDS 0 0 MLP MD1 MD0
               AHPM[1:0] - HPF mode selection
               	00=normal (resets reference registers), 01=reference signal for filtering, 
               	10=normal, 11=autoreset on interrupt event
               AFDS - Filtered acceleration data selection
               	0=internal filter bypassed, 1=data from internal filter sent to FIFO
               MLP - Magnetic data low-power mode
               	0=data rate is set by M_ODR bits in CTRL_REG5
               	1=data rate is set to 3.125Hz
               MD[1:0] - Magnetic sensor mode selection (default 10)
               	00=continuous-conversion, 01=single-conversion, 10 and 11=power-down */
               xmWriteByte(CTRL_REG7_XM, 0x00); // Continuous conversion mode
	
               /* CTRL_REG4_XM is used to set interrupt generators on INT2_XM
               Bits (7-0): P2_TAP P2_INT1 P2_INT2 P2_INTM P2_DRDYA P2_DRDYM P2_Overrun P2_WTM
               */
               xmWriteByte(CTRL_REG4_XM, 0x04); // Magnetometer data ready on INT2_XM (0x08)
	
               /* INT_CTRL_REG_M to set push-pull/open drain, and active-low/high
               Bits[7:0] - XMIEN YMIEN ZMIEN PP_OD IEA IEL 4D MIEN
               XMIEN, YMIEN, ZMIEN - Enable interrupt recognition on axis for mag data
               PP_OD - Push-pull/open-drain interrupt configuration (0=push-pull, 1=od)
               IEA - Interrupt polarity for accel and magneto
               	0=active-low, 1=active-high
               IEL - Latch interrupt request for accel and magneto
		0=irq not latched, 1=irq latched
               4D - 4D enable. 4D detection is enabled when 6D bit in INT_GEN1_REG is set
               MIEN - Enable interrupt generation for magnetic data
               	0=disable, 1=enable) */
               xmWriteByte(INT_CTRL_REG_M, 0x09); // Enable interrupts for mag, active-low, push-pull
            }
	
	// gReadByte() -- Reads a byte from a specified gyroscope register.
	// Input:
	// 	- subAddress = Register to be read from.
	// Output:
	// 	- An 8-bit value read from the requested address.
	inline uint8_t gReadByte(uint8_t reg)
           {
               uint8_t tmp ;
               io.gyro_read_bytes (reg , &tmp , 1) ;
               return tmp ;
           }
	
	// gReadBytes() -- Reads a number of bytes -- beginning at an address
	// and incrementing from there -- from the gyroscope.
	// Input:
	// 	- subAddress = Register to be read from.
	// 	- * dest = A pointer to an array of uint8_t's. Values read will be
	//		stored in here on return.
	//	- count = The number of bytes to be read.
	// Output: No value is returned, but the `dest` array will store
	// 	the data read upon exit.
	inline void gReadBytes(uint8_t reg, uint8_t * dest, uint8_t count)
           {
	      io.gyro_read_bytes (reg , dest , count) ;
           }
	
	// gWriteByte() -- Write a byte to a register in the gyroscope.
	// Input:
	//	- subAddress = Register to be written to.
	//	- data = data to be written to the register.
	inline void gWriteByte(uint8_t reg, uint8_t data)
           {
	      io.gyro_write_bytes (reg , &data , 1) ;
           }
	
	// xmReadByte() -- Read a byte from a register in the accel/mag sensor
	// Input:
	//	- subAddress = Register to be read from.
	// Output:
	//	- An 8-bit value read from the requested register.
	inline uint8_t xmReadByte(uint8_t reg)
           {
	      uint8_t tmp ;
	      io.accel_mag_read_bytes (reg , &tmp , 1) ;
	      return tmp ;

           }
	
	// xmReadBytes() -- Reads a number of bytes -- beginning at an address
	// and incrementing from there -- from the accelerometer/magnetometer.
	// Input:
	// 	- subAddress = Register to be read from.
	// 	- * dest = A pointer to an array of uint8_t's. Values read will be
	//		stored in here on return.
	//	- count = The number of bytes to be read.
	// Output: No value is returned, but the `dest` array will store
	// 	the data read upon exit.
	inline void xmReadBytes(uint8_t reg, uint8_t * dest, uint8_t count)
           {
              io.accel_mag_read_bytes (reg , dest , count) ;
           }
	
	// xmWriteByte() -- Write a byte to a register in the accel/mag sensor.
	// Input:
	//	- subAddress = Register to be written to.
	//	- data = data to be written to the register.
	inline void xmWriteByte(uint8_t reg, uint8_t data)
           {
	      io.accel_mag_write_bytes (reg , &data , 1) ;
           }
	
	// calcgRes() -- Calculate the resolution of the gyroscope.
	// This function will set the value of the gRes variable. gScale must
	// be set prior to calling this function.
	inline void calcgRes()
           {
	   // Possible gyro scales (and their register bit settings) are:
	   // 245 DPS (00), 500 DPS (01), 2000 DPS (10). Here's a bit of an algorithm
	   // to calculate DPS/(ADC tick) based on that 2-bit value:
           switch (gScale)
              {
                case G_SCALE_245DPS:
           	   gRes = 245.0 / 32768.0;
           	break;
                case G_SCALE_500DPS:
           	   gRes = 500.0 / 32768.0;
           	break;
                case G_SCALE_2000DPS:
           	   gRes = 2000.0 / 32768.0;
           	break;
              }
           }
	
	// calcmRes() -- Calculate the resolution of the magnetometer.
	// This function will set the value of the mRes variable. mScale must
	// be set prior to calling this function.
	inline void calcmRes()
           {
              // Possible magnetometer scales (and their register bit settings) are:
              // 2 Gs (00), 4 Gs (01), 8 Gs (10) 12 Gs (11). Here's a bit of an algorithm
              // to calculate Gs/(ADC tick) based on that 2-bit value:
              mRes = mScale == M_SCALE_2GS ? 2.0 / 32768.0 : 
	         (float) (mScale << 2) / 32768.0;
           }
	
	// calcaRes() -- Calculate the resolution of the accelerometer.
	// This function will set the value of the aRes variable. aScale must
	// be set prior to calling this function.
	inline void calcaRes()
           {
	      // Possible accelerometer scales (and their register bit settings) are:
	      // 2 g (000), 4g (001), 6g (010) 8g (011), 16g (100). Here's a bit of an 
	      // algorithm to calculate g/(ADC tick) based on that 3-bit value:
	      aRes = aScale == A_SCALE_16G ? 16.0 / 32768.0 : 
		   (((float) aScale + 1.0) * 2.0) / 32768.0;
           }

#if 0  //использовать при написании шаблона имплиментации интерфейса io
	///////////////////
	// SPI Functions //
	///////////////////
	// initSPI() -- Initialize the SPI hardware.
	// This function will setup all SPI pins and related hardware.
	inline void initSPI()
           {
	      pinMode(gAddress, OUTPUT);
	      digitalWrite(gAddress, HIGH);
	      pinMode(xmAddress, OUTPUT);
	      digitalWrite(xmAddress, HIGH);

	      SPI.begin();
	      // Maximum SPI frequency is 10MHz, could divide by 2 here:
	      SPI.setClockDivider(SPI_CLOCK_DIV4);
	      // Data is read and written MSb first.
	      SPI.setBitOrder(MSBFIRST);
	      // Data is captured on rising edge of clock (CPHA = 0)
	      // Base value of the clock is HIGH (CPOL = 1)
	      SPI.setDataMode(SPI_MODE1);
           }
	
	// SPIwriteByte() -- Write a byte out of SPI to a register in the device
	// Input:
	//	- csPin = The chip select pin of the slave device.
	//	- subAddress = The register to be written to.
	//	- data = Byte to be written to the register.
	inline void SPIwriteByte(uint8_t csPin, uint8_t subAddress, uint8_t data)
           {
              digitalWrite(csPin, LOW); // Initiate communication
	
              // If write, bit 0 (MSB) should be 0
              // If single write, bit 1 should be 0
              SPI.transfer(subAddress & 0x3F); // Send Address
              SPI.transfer(data); // Send data
	
              digitalWrite(csPin, HIGH); // Close communication
           }
	
	// SPIreadByte() -- Read a single byte from a register over SPI.
	// Input:
	//	- csPin = The chip select pin of the slave device.
	//	- subAddress = The register to be read from.
	// Output:
	//	- The byte read from the requested address.
	inline uint8_t SPIreadByte(uint8_t csPin, uint8_t subAddress)
          {
	     uint8_t temp;
	     // Use the multiple read function to read 1 byte. 
	     // Value is returned to `temp`.
	     SPIreadBytes(csPin, subAddress, &temp, 1);
	     return temp;
          }
	
	// SPIreadBytes() -- Read a series of bytes, starting at a register via SPI
	// Input:
	//	- csPin = The chip select pin of a slave device.
	//	- subAddress = The register to begin reading.
	// 	- * dest = Pointer to an array where we'll store the readings.
	//	- count = Number of registers to be read.
	// Output: No value is returned by the function, but the registers read are
	// 		all stored in the *dest array given.
	inline void SPIreadBytes(uint8_t csPin, uint8_t subAddress, uint8_t * dest, uint8_t count)
           {
	      digitalWrite(csPin, LOW); // Initiate communication
	      // To indicate a read, set bit 0 (msb) to 1
	      // If we're reading multiple bytes, set bit 1 to 1
	      // The remaining six bytes are the address to be read
	      if (count > 1)
	      	SPI.transfer(0xC0 | (subAddress & 0x3F));
	      else
	      	SPI.transfer(0x80 | (subAddress & 0x3F));
	      for (int i=0; i<count; i++)
	      {
	      	dest[i] = SPI.transfer(0x00); // Read into destination array
	      }
	      digitalWrite(csPin, HIGH); // Close communication
           }
#endif
	

	const io_t& io ;
};


//---------------------------------------------------------------------------------------------------------------------------

#endif // SFE_LSM9DS0_H //

