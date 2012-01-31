#ifndef ROCKVISUALIZATION_H
#define ROCKVISUALIZATION_H

#include <boost/noncopyable.hpp>
#include <osg/Geode>
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <base/samples/rigid_body_state.h>
#include <vizkit/Vizkit3DPlugin.hpp>

namespace vizkit 
{
    class RockVisualization 
        : public vizkit::Vizkit3DPlugin<base::samples::RigidBodyState>
        , boost::noncopyable
    {
    public:
        RockVisualization();
        ~RockVisualization();

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode( osg::Node* node );
        virtual void updateDataIntern ( base::samples::RigidBodyState const& value );
        
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
