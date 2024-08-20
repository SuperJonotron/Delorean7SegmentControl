#ifndef DELOREANSEVENSEGMENTCONTROL_H
#define DELOREANSEVENSEGMENTCONTROL_H

#include <LEDDisplayDriver.h>
#include <Time.h>

const byte numberOfDigits = 4;

#if defined(ESP8266)
	//Confirm these pins are actually correct for the esp8266
	//define shared DIO Pin
	const byte PIN_DIO = 0;

	//define Red Display Pins
	const byte PIN_CLK_Red_1 = 1;//D8; 
	const byte PIN_CLK_Red_2 = 2; 
	const byte PIN_CLK_Red_3 = 3; 

	//define Green Display Pins
	const byte PIN_CLK_Green_1 = 4; 
	const byte PIN_CLK_Green_2 = 5; 
	const byte PIN_CLK_Green_3 = 6; 

	//define Yellow Display Pins
	const byte PIN_CLK_Yellow_1 = 7; 
	const byte PIN_CLK_Yellow_2 = 8;//TX
	const byte PIN_CLK_Yellow_3 = 9;//SDD3
#elif defined(ESP32) //This pintout is not confirmed just placed here to compile
	//define shared DIO Pin
	const byte PIN_DIO = 2;

	//define Red Display Pins
	const byte PIN_CLK_Red_1 = 3;; 
	const byte PIN_CLK_Red_2 = 4; 
	const byte PIN_CLK_Red_3 = 5; 

	//define Green Display Pins
	const byte PIN_CLK_Green_1 = 6; 
	const byte PIN_CLK_Green_2 = 7; 
	const byte PIN_CLK_Green_3 = 8; 

	//define Yellow Display Pins
	const byte PIN_CLK_Yellow_1 = 9; 
	const byte PIN_CLK_Yellow_2 = 10;
	const byte PIN_CLK_Yellow_3 = 11;
#elif defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2040)
	 
	//define shared DIO Pin
	const byte PIN_DIO = 0;

	//define Red Display Pins
	const byte PIN_CLK_Red_1 = 1;
	const byte PIN_CLK_Red_2 = 2; 
	const byte PIN_CLK_Red_3 = 3; 

	//define Green Display Pins
	const byte PIN_CLK_Green_1 = 4; 
	const byte PIN_CLK_Green_2 = 5; 
	const byte PIN_CLK_Green_3 = 6; 

	//define Yellow Display Pins
	const byte PIN_CLK_Yellow_1 = 7; 
	const byte PIN_CLK_Yellow_2 = 8;
	const byte PIN_CLK_Yellow_3 = 9;
#endif

class Delorean7SegmentControl{
    public:
        Delorean7SegmentControl();
        void setDate(int year,int month, int day, LEDDisplayDriver *monthDaySeg, LEDDisplayDriver *yearSeg);
        void setDate(time_t t,LEDDisplayDriver *monthDaySeg,LEDDisplayDriver *yearSeg);
        void setTime(int hour,int minute,LEDDisplayDriver *timeSeg);
        void setTime(time_t t,LEDDisplayDriver *timeSeg, bool twelveHour);
		void start();
        void clearRed(bool monthDay, bool year, bool time);
        void clearYellow(bool monthDay, bool year, bool time);
        void clearGreen(bool monthDay, bool year, bool time);
        void updateAll(time_t red, time_t green, time_t yellow);
        void updateRed(time_t t);
        void updateRed(int year, int month, int day, int hour, int minute);
        void updateGreen(time_t t,bool updateDate, bool updateTime);
        void updateGreen(int year, int month, int day, int hour, int minute);
        void updateYellow(time_t t);
        void updateYellow(int year, int month, int day, int hour, int minute);
    private:
    	void initPins();
    	void startSegmentRow(LEDDisplayDriver *monthDaySeg,
    			LEDDisplayDriver *yearSeg,
    			LEDDisplayDriver *timeSeg);
    };


#endif