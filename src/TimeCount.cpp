#include "TimeCount.h"

void time_h::count_timer()
{
  if (time_now->time_sec_value1 > 9)
  {
    time_now->time_sec_value1 = 0;
    ++time_now->time_sec_value2;

    if (time_now->time_sec_value2 > 5)
    {
      time_now->time_sec_value2 = 0;
    } ///
  }   ///
}

void time_h::resetTime()
{
  time_now->time_sec_value1 = 0;
  time_now->time_sec_value2 = 0;
}
