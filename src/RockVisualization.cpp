#include "RockVisualization.hpp"
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>

namespace vizkit 
{

RockVisualization::RockVisualization()
{   
    VizPluginRubyAdapter(RockVisualization, base::Pose, Pose)
}

osg::ref_ptr< osg::Node > RockVisualization::createMainNode()
{
    osg::ref_ptr<osg::Group> mainNode = new osg::Group();
    
    osg::ref_ptr<osg::PositionAttitudeTransform> rockModelOffset = new osg::PositionAttitudeTransform();
    rockModelPos = new osg::PositionAttitudeTransform();
    rockModelOffset->addChild(rockModelPos);
    rockModelOffset->setPosition(osg::Vec3d(0.0, 0.0, 0.35));
    mainNode->addChild(rockModelOffset);
    
    // get rock model
    char* osgPath = getenv("OSG_FILE_PATH");
    if (osgPath) 
    {
        std::string filePath(osgPath);
        filePath += "/rock.osg";
        rockModel = osgDB::readNodeFile(filePath);
    }
    if (rockModel.get() == 0)
    {
        rockModel = printPrimitivModel();
    }
    
    rockModelPos->addChild(rockModel);
    
    return mainNode;
}

osg::ref_ptr<osg::Node> RockVisualization::printPrimitivModel()
{
    osg::ref_ptr<osg::Sphere> sp = new osg::Sphere(osg::Vec3d(0,0,0), 0.35);
    osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(sp.get());
    sd->setColor(osg::Vec4(0.5f, 0.5f, 0.5f, 1.0f));
    osg::ref_ptr<osg::Geode> spGeode = new osg::Geode();
    spGeode->addDrawable(sd.get());
    return spGeode;
}

void RockVisualization::updateDataIntern ( const base::Pose& data )
{
    pose = data;
}

void RockVisualization::updateMainNode( osg::Node* node )
{
    position.set(pose.position.x(), pose.position.y(), pose.position.z());
    orientation.set(pose.orientation.x(), pose.orientation.y(), pose.orientation.z(), pose.orientation.w());
    rockModelPos->setPosition(position);
    rockModelPos->setAttitude(orientation);
}

}
