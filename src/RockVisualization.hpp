#ifndef ROCKVISUALIZATION_H
#define ROCKVISUALIZATION_H

#include <base/pose.h>
#include <vizkit/VizPlugin.hpp>

#include <osg/Node>
#include <osg/PositionAttitudeTransform>

namespace vizkit 
{
    
class RockVisualization: public vizkit::VizPlugin<base::Pose>
{
    public:
	RockVisualization();

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
	virtual void updateMainNode( osg::Node* node );
	void updateDataIntern ( const base::Pose& data );
        osg::ref_ptr<osg::Node> printPrimitivModel();
        
        base::Pose pose;
        osg::Vec3d position;
        osg::Quat orientation;
        osg::ref_ptr<osg::PositionAttitudeTransform> rockModelPos;
        osg::ref_ptr<osg::Node> rockModel;
};

VizkitQtPlugin(RockVisualization)

}
#endif // ROCKVISUALIZATION_H
