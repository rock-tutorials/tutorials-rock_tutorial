#include "RockControl.hpp"
#include <math.h>

namespace rock_tutorial {

RockControl::RockControl()
{
    // set variables to zero
    taskPeriod = 0;
    currentHeading = 0;
    currentPitch = 0;
    currentPose.orientation = base::Quaterniond::Identity();
    currentPose.position = base::Vector3d::Zero();
}

RockControl::~RockControl()
{

}

/**
 * Makes sure that angles are between PI and -PI.
 */
void RockControl::constrainAngle(double& angle)
{
    if (angle < -M_PI)
        angle = angle + 2 * M_PI;
    else if (angle > M_PI)
        angle = angle - 2 * M_PI;
}

/**
 * This method constrains the relativ rotation and translation 
 * of a 2d motion command.
 * Rotation should be between PI an -PI.
 * Translation should be between 10 and -10.
 */
void RockControl::constrainValues(base::MotionCommand2D& motionCommand)
{
    if (motionCommand.rotation > M_PI)
        motionCommand.rotation = M_PI;
    else if (motionCommand.rotation < -M_PI)
        motionCommand.rotation = -M_PI;
    
    if (motionCommand.translation > 10)
        motionCommand.translation = 10;
    else if (motionCommand.translation < -10)
        motionCommand.translation = -10;
}

base::samples::RigidBodyState RockControl::computeNextPose(const double &deltaTime, const base::MotionCommand2D &inputCommand)
{
    base::MotionCommand2D command = inputCommand;
    constrainValues(command);
    
        //translation and rotation relativ to the task period
    double delta_translation  = command.translation * deltaTime;
    double delta_rotation  = command.rotation * deltaTime;
    
    // set current yaw and pitch (the rock is rolling)
    currentHeading += delta_rotation;
    currentPitch += delta_translation * -2;
    constrainAngle(currentHeading);
    constrainAngle(currentPitch);
    
    // calculate new absolut values for position and orientation
    currentPose.position += Eigen::AngleAxisd(currentHeading, Eigen::Vector3d::UnitZ()) * Eigen::Vector3d(delta_translation, 0, 0);
    currentPose.orientation = Eigen::AngleAxisd(currentHeading, Eigen::Vector3d::UnitZ()) * Eigen::AngleAxisd(currentPitch, Eigen::Vector3d::UnitY());
    currentPose.orientation.normalize();

    return currentPose;
}

}
