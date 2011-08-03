require 'vizkit'
require 'Qt4'
require 'vizkittypelib'
include Orocos
Orocos.initialize

# loading all base types
Orocos::CORBA.load_typekit('base')

# create an instance of the vizkit main window
# alternatively vizkit::QVizkitWidget could also be used
widget = Vizkit.default_loader.create_widget("vizkit::QVizkitMainWindow")
plugin = widget.createPlugin("rock_tutorial", "RockVisualization")

# use a configuration method of the plugin to activate a label
#plugin.activateRockLabel(true)

# create an instance of the base type Pose
bodyState = Types::Base::Pose.new
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
    plugin.updatePose(bodyState)
end

# start the timer with a timeout of 10 ms
timer.start(10)

widget.show
Vizkit.exec 
