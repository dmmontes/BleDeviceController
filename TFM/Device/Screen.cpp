#include "Screen.h"

#include "DeviceLogger.h"

Screen::Screen()
    : resetPin_{17},
      dataCommandPin_{31},
      chipSelectPin_{13},
      backlightPin_{39},
      screen_{resetPin_, dataCommandPin_, chipSelectPin_, backlightPin_}
{
    LOG_DEBUG("Screen::Screen()");

    screen_.begin();
};

Screen::~Screen()
{
    LOG_DEBUG("Screen::~Screen()");

    screen_.setDisplay(false);
    screen_.setBacklight(false);
};
