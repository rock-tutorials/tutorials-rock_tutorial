#ifndef ROCKCONTROL_H
#define ROCKCONTROL_H

#include <base/commands/Motion2D.hpp>
#include <base/samples/RigidBodyState.hpp>

namespace rock_tutorial {

class RockControl
{

public:
    RockControl();
    virtual ~RockControl();
    
    base::samples::RigidBodyState computeNextPose(const double &deltaTime, const base::commands::Motion2D &command);

    void setRockRadius(double r) { rockRadius = r; }
    double getRockRadius() { return rockRadius; }

private:
    void constrainAngle(double& angle);
    void constrainValues(base::commands::Motion2D& motionCommand);
    base::samples::RigidBodyState currentPose;
    double currentHeading;
    double currentPitch;
    double rockRadius;

};

}

#endif // ROCKCONTROL_H
