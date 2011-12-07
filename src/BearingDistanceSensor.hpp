#ifndef ROCK_TUTORIAL_BEARING_HEADING_SENSOR
#define ROCK_TUTORIAL_BEARING_HEADING_SENSOR

#include <base/time.h>
#include <base/angle.h>

namespace rock_tutorial
{
    struct BearingDistanceSensor
    {
        base::Time time;
        base::Angle bearing;
        double distance;
    };
}

#endif

