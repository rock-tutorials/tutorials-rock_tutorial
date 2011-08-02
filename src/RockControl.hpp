#ifndef ROCKCONTROL_H
#define ROCKCONTROL_H

#include <base/motion_command.h>
#include <base/pose.h>

namespace rock_tutorial {

class RockControl
{

public:
    RockControl();
    virtual ~RockControl();
    
    base::Pose computeNextPose(const double &deltaTime, const base::MotionCommand2D &command);

private:
    void constrainAngle(double& angle);
    void constrainValues(base::MotionCommand2D& motionCommand);
    base::Pose currentPose;
    double currentHeading;
    double currentRoll;
    double taskPeriod;

};

}

#endif // ROCKCONTROL_H
