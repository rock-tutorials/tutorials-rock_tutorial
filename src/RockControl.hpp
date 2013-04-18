#ifndef ROCKCONTROL_H
#define ROCKCONTROL_H

#include <base/motion_command.h>
#include <base/samples/rigid_body_state.h>

namespace rock_tutorial {

class RockControl
{

public:
    RockControl();
    virtual ~RockControl();
    
    base::samples::RigidBodyState computeNextPose(const double &deltaTime, const base::MotionCommand2D &command);

    void setRockRadius(double r) { rockRadius = r; }
    double getRockRadius() { return rockRadius; }

private:
    void constrainAngle(double& angle);
    void constrainValues(base::MotionCommand2D& motionCommand);
    base::samples::RigidBodyState currentPose;
    double currentHeading;
    double currentPitch;
    double rockRadius;

};

}

#endif // ROCKCONTROL_H
