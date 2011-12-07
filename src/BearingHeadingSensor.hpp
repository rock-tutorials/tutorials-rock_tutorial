#ifndef ROCK_TUTORIAL_BEARING_HEADING_SENSOR
#define ROCK_TUTORIAL_BEARING_HEADING_SENSOR

namespace rock_tutorial
{
    struct BearingHeadingSensor
    {
        base::Time time;
        base::Angle bearing;
        double distance;
    };
}

#endif

