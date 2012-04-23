require 'vizkit'
require 'Qt4'
require 'vizkittypelib'
include Orocos
Orocos.initialize

# create an instance of the vizkit main window
# alternatively vizkit::QVizkitWidget could also be used
plugin = Vizkit.default_loader.RockVisualization

# create an instance of the base type Pose
bodyState = Types::Base::Samples::RigidBodyState.new
# set initial values
bodyState.position.initialize
bodyState.orientation = Eigen::Quaternion.new(1, 0, 0, 0)

# a global index
i = 0.0
# initialize timer
timer = Qt::Timer.new
timer.connect(SIGNAL('timeout()')) do
    i += 1.0
    j = i / 100.0
    bodyState.position.x = Math::cos(j) * j
    bodyState.position.y = Math::sin(j) * j
    plugin.updateRigidBodyState(bodyState)
end

# start the timer with a timeout of 10 ms
timer.start(10)

Vizkit.exec 
