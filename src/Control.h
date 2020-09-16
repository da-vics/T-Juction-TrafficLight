#ifndef CONTROL_H
#define CONTROL_H

#include "defines.h"
#include "7Segment.h"

class MainControl
{
  private:
    bool _stateChanged{false};
    enum class SignalState
    {
      PEDSTOP,
      PEDGO
    };

    SignalState _signalState = SignalState::PEDSTOP;
    SignalState _tempState{};
    segmentControl *_segControl{nullptr};
    time_h *timeCounter{nullptr};

    MainControl() {}

  public:
    bool startTimer{false};

    MainControl(segmentControl *segctrl, time_h *counter)
    {
      this->_segControl = segctrl;
      this->timeCounter = counter;
    }

    void Action();
    void ResetIndicators();
    void ResetSegPins();
};

#endif //CONTROL_H
