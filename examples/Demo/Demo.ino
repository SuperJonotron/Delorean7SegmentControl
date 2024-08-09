#include <Delorean7SegmentControl.h>

Delorean7SegmentControl segCtrl; 

void setup() {
  Serial.begin(115200);
  Serial.println("Delorean Demo sketch started");
  segCtrl.start();

}

void loop(){
	
}
