#ifndef ROCKVISUALIZATION_H
#define ROCKVISUALIZATION_H

#include <boost/noncopyable.hpp>
#include <vizkit/VizPlugin.hpp>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <base/pose.h>

namespace vizkit 
{
    class RockVisualization 
        : public vizkit::VizPlugin<base::Pose>
        , boost::noncopyable
    {
    public:
        RockVisualization();
        ~RockVisualization();

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode( osg::Node* node );
        virtual void updateDataIntern ( base::Pose const& value );
        
        osg::ref_ptr<osg::Node> printPrimitivModel();
        
        osg::Vec3d position;
        osg::Quat orientation;
        osg::ref_ptr<osg::PositionAttitudeTransform> rockModelPos;
        osg::ref_ptr<osg::Node> rockModel;

    private:
        struct Data;
        Data* p;
    };

}
#endif // ROCKVISUALIZATION_H
