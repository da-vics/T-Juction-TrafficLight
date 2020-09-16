#ifndef TIMECOUNT_H
#define TIMECOUNT_H

#include "Timing.h"

class time_h
{
  private:
    time_compute *time_now{nullptr};

    time_h() {}

  public:
    volatile short time {};
    time_h(time_compute *timee)
    {
      this->time_now = timee;
    }

    void count_timer();
    void resetTime();
};

#endif /// TIMECOUNT_H
