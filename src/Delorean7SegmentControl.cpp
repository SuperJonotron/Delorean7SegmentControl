#include "Delorean7SegmentControl.h"

/* Create the display driver objects to control the various LED displays
   Turn auto update off, this is never required, but makes the code a bit faster
 */
LEDDisplayDriver redTime(PIN_DIO,PIN_CLK_Red_1,false,numberOfDigits);// Month an Day
LEDDisplayDriver redYear(PIN_DIO,PIN_CLK_Red_2,false,numberOfDigits);// Year
LEDDisplayDriver redMonthDay(PIN_DIO,PIN_CLK_Red_3,false,numberOfDigits);// Time

LEDDisplayDriver greenTime(PIN_DIO,PIN_CLK_Green_1,false,numberOfDigits);// Month an Day
LEDDisplayDriver greenYear(PIN_DIO,PIN_CLK_Green_2,false,numberOfDigits);// Year
LEDDisplayDriver greenMonthDay(PIN_DIO,PIN_CLK_Green_3,false,numberOfDigits);// Time

LEDDisplayDriver yellowTime(PIN_DIO,PIN_CLK_Yellow_1,false,numberOfDigits);// Month an Day
LEDDisplayDriver yellowYear(PIN_DIO,PIN_CLK_Yellow_2,false,numberOfDigits);// Year
LEDDisplayDriver yellowMonthDay(PIN_DIO,PIN_CLK_Yellow_3,false,numberOfDigits);// Time

/*----------------------------------------------------------------------*
 * Create a DeloriaClockDisplay object to control the                   *
 * Seven Segment Displays.                                              *
 *----------------------------------------------------------------------*/
Delorean7SegmentControl::Delorean7SegmentControl(){
  //initPins();
}

void Delorean7SegmentControl::initPins(){
  Serial.println("Initializing pins");
  pinMode(PIN_DIO,OUTPUT);
  pinMode(PIN_CLK_Red_1,OUTPUT);
  pinMode(PIN_CLK_Red_2,OUTPUT);
  pinMode(PIN_CLK_Red_3,OUTPUT);
  pinMode(PIN_CLK_Green_1,OUTPUT);
  pinMode(PIN_CLK_Green_2,OUTPUT);
  pinMode(PIN_CLK_Green_3,OUTPUT);
  pinMode(PIN_CLK_Yellow_1,OUTPUT);
  pinMode(PIN_CLK_Yellow_2,OUTPUT);
  pinMode(PIN_CLK_Yellow_3,OUTPUT);
}

void Delorean7SegmentControl::start(){
  Serial.println("Starting segment control");
  startSegmentRow(&redMonthDay,&redYear,&redTime);
  startSegmentRow(&greenMonthDay,&greenYear,&greenTime);
  startSegmentRow(&yellowMonthDay,&yellowYear,&yellowTime);

  int futureYear = 2015;
  int futureMonth=10;
  int futureDay=21;
  //Future Time Travled to in B2F2 - 2015-10-21T16:29:00
  setDate(futureYear,futureMonth,futureDay,&redMonthDay,&redYear);
  setTime(4,29,&redTime);

  int currentYear=1985;
  int currentMonth=10;
  int currentDay=26;
  //Curren Time - Time from B2F of first time travel (confirm from movie)
  setDate(futureYear,futureMonth,futureDay,&greenMonthDay,&greenYear);
  setTime(1,21,&greenTime);

  int pastYear=1955;
  int pastMonth=11;
  int pastDay=5;
  //Past Time Travled to in B2F - 1955-11-05T6:00:00
  setDate(futureYear,futureMonth,futureDay,&yellowMonthDay,&yellowYear);
  setTime(6,0,&yellowTime);
}

void Delorean7SegmentControl::startSegmentRow(LEDDisplayDriver *monthDaySeg,
   LEDDisplayDriver *yearSeg,LEDDisplayDriver *timeSeg){
   timeSeg->setDp(1);//Turn colon on
   monthDaySeg->setDp(1);//Turn colon on
   yearSeg->setDp(0);//Turn colon off
}

void Delorean7SegmentControl::setDate(int year,int month, int day, 
  LEDDisplayDriver *monthDaySeg, LEDDisplayDriver *yearSeg){
  monthDaySeg->showNum2LeftLZ(month);
  monthDaySeg->showNum2RightLZ(day);
  yearSeg->showNum4Left(year);
  //Update the displays
  monthDaySeg->update();
  yearSeg->update();
}

void Delorean7SegmentControl::setTime(int hour,int minute,LEDDisplayDriver *timeSeg){
  timeSeg->showNum2LeftLZ(hour); //Show 2 digits left justified with leading zeros
  timeSeg->showNum2RightLZ(minute); //Show 2 digits right justified with leading zeros
  timeSeg->update();
}

void Delorean7SegmentControl::setTime(time_t t,LEDDisplayDriver *dateSeg, 
   bool twelveHour){
  int hr = hour(t)>12 && twelveHour?hour(t)-12:hour(t);
  setTime(hr,minute(t),dateSeg);
}

void Delorean7SegmentControl::setDate(time_t t,LEDDisplayDriver *monthDaySeg,
   LEDDisplayDriver *yearSeg){
   setDate(year(t),month(t),day(t),monthDaySeg,yearSeg);
}

void Delorean7SegmentControl::updateAll(time_t red, time_t green, time_t yellow){
  updateRed(red);
  updateGreen(green,true,true);
  updateYellow(yellow);
 }

void Delorean7SegmentControl::updateRed(time_t t){
  setDate(t,&redMonthDay,&redYear);
  setTime(t,&redTime,true);
}

void Delorean7SegmentControl::updateRed(int year, int month, int day, int hour, int minute){
  setDate(year,month,day,&redMonthDay,&redYear);
  setTime(hour,minute,&redTime);
}

void Delorean7SegmentControl::clearRed(bool monthDay, bool year, bool time){
  if(monthDay){
    redMonthDay.clear();
  }
  if(year){
    redYear.clear();
  }
  if(time){
    redTime.clear();
  }
}

void Delorean7SegmentControl::clearYellow(bool monthDay, bool year, bool time){
  if(monthDay){
    yellowMonthDay.clear();
  }
  if(year){
    yellowYear.clear();
  }
  if(time){
    yellowTime.clear();
  }
}

void Delorean7SegmentControl::clearGreen(bool monthDay, bool year, bool time){
  if(monthDay){
    greenMonthDay.clear();
  }
  if(year){
    greenYear.clear();
  }
  if(time){
    greenTime.clear();
  }
}

void Delorean7SegmentControl::updateGreen(time_t t, bool updateDate, bool updateTime){
  if(updateDate){
    setDate(t,&greenMonthDay,&greenYear);
  }
  if(updateTime){
    setTime(t,&greenTime,true);
  }
  bool am = hour(t)<12;
  // digitalWrite(greenAM,am);
  // digitalWrite(greenPM,!am);
}

void Delorean7SegmentControl::updateGreen(int year, int month, int day, int hour, int minute){
  setDate(year,month,day,&greenMonthDay,&greenYear);
  setTime(hour,minute,&greenTime);
}

void Delorean7SegmentControl::updateYellow(time_t t){
  setDate(t,&yellowMonthDay,&yellowYear);
  setTime(t,&yellowTime,true);
}

void Delorean7SegmentControl::updateYellow(int year, int month, int day, int hour, int minute){
  setDate(year,month,day,&yellowMonthDay,&yellowYear);
  setTime(hour,minute,&yellowTime);
}