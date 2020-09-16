#include "Control.h"

const short SegmentPins[MAX_SegmentPins] = {13, 12, 11, 10, 9, 8, 7};

#pragma region Instances
time_compute dynamicTime;
segmentControl DisplaySegments(SegmentPins, &dynamicTime);
time_h initiate_time(&dynamicTime);

MainControl ControlElements(&DisplaySegments, &initiate_time);
#pragma endregion

volatile int seconds_counter = 0; /// seconds  indicator

int main()
{
#pragma region
  pinMode(sec2ctrl, OUTPUT);
  pinMode(sec1ctrl, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);

  ControlElements.ResetSegPins();

  for (int i = 0; i < MAX_SegmentPins; ++i)
  {
    pinMode(SegmentPins[i], OUTPUT);
  }

#pragma endregion

#pragma region Timer0 Setup
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
#pragma endregion

  while (true)
  {
    ControlElements.Action();
  }
}

#pragma region Timer Interrupt Service Routin
SIGNAL(TIMER0_COMPA_vect)
{
  if (ControlElements.startTimer == true)
  {
    ++seconds_counter;

    if (seconds_counter >= 1000) /// 1 sec
    {
      ++initiate_time.time;
      seconds_counter = 0;
      ++dynamicTime.time_sec_value1;
      initiate_time.count_timer();
    }
  }

  else
  {
    initiate_time.time = 0;
    seconds_counter = 0;
    dynamicTime.time_sec_value1 = 0;
    dynamicTime.time_sec_value2 = 0;
  }

} ///<<
#pragma endregion
