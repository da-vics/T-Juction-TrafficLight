#ifndef SEGMENT_H
#define SEGMENT_H

#include <Arduino.h>
#include "TimeCount.h"

#define MAX_SegmentPins 7

class segmentControl
{
private:
  time_compute *time_now{nullptr};

  union SegmentField
  {

    struct segment_states
    {
      uint8_t sec1_state : 1;
      uint8_t sec2_state : 1;
      uint8_t seconds_state : 1; /// for second indicator digital state
    } States;

    uint8_t flags;
  };

  void lightNumber(const int &) const;
  short segA{};
  short segB{};
  short segC{};
  short segD{};
  short segE{};
  short segF{};
  short segG{};
  short *segint[MAX_SegmentPins] = {&segA, &segB, &segC, &segD, &segE, &segF, &segG};

  segmentControl() {}

public:
  short switch_seg{0};
  SegmentField Fields;

  segmentControl(short const *ptr, time_compute *tnow)
  {
    this->Fields.flags = 0;

    this->time_now = tnow;

    for (int i = 0; i < MAX_SegmentPins; ++i, ++ptr)
    {
      *segint[i] = *ptr;
    }
  }

  void clear_segments() const;
  void switch_seg_States() const;
  void segFastSwitch();
  void timingOps();
};

#endif ///7SEGMENT_H
