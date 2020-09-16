#include "Control.h"

void MainControl::Action()
{
  timeCounter->resetTime();

  delay(1000);

  this->startTimer = true;

  if (_stateChanged)
  {
    _signalState = _tempState;
    _stateChanged = false;
  }

  while (timeCounter->time <= 60)
  {
    this->_segControl->timingOps();
    digitalWrite(sec2ctrl, this->_segControl->Fields.States.sec2_state);
    digitalWrite(sec1ctrl, this->_segControl->Fields.States.sec1_state);

    unsigned long tim = millis();

    while (true)
    {
      if ((millis() - tim) > 6)
      {
        break;
      }
    }

    if (_signalState == SignalState::PEDSTOP)
    {
      if (timeCounter->time <= 55)
      {
        this->ResetIndicators();
        digitalWrite(RedLED, HIGH);
      }

      else if (timeCounter->time > 55 && timeCounter->time < 59)
      {
        this->ResetIndicators();
        digitalWrite(YellowLED, HIGH);
      }

      else if (timeCounter->time == 59)
      {
        _stateChanged = true;
        this->ResetIndicators();
        _tempState = SignalState::PEDGO;
        digitalWrite(GreenLED, HIGH);
      }
    }

    else if (_signalState == SignalState::PEDGO)
    {
      if (timeCounter->time == 55)
      {
        this->ResetIndicators();
        digitalWrite(YellowLED, HIGH);
      }

      else if (timeCounter->time == 59)
      {
        _stateChanged = true;
        _tempState = SignalState::PEDSTOP;
      }
    }
  } ///

  this->_segControl->Fields.flags = 0x7;
  this->ResetSegPins();
  this->startTimer = false;
  timeCounter->time = 0;

} ///

void MainControl::ResetSegPins()
{
  digitalWrite(sec2ctrl, LOW);
  digitalWrite(sec1ctrl, LOW);
}

void MainControl::ResetIndicators()
{
  digitalWrite(YellowLED, LOW);
  digitalWrite(GreenLED, LOW);
  digitalWrite(RedLED, LOW);
}