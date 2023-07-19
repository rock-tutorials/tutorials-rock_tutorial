#include "RockVisualization.hpp"
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osgText/Text>

namespace vizkit3d
{

struct RockVisualization::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
    base::samples::RigidBodyState data;
};

RockVisualization::RockVisualization()
    : p(new Data)
{   
}

RockVisualization::~RockVisualization()
{
    delete p;
}

osg::ref_ptr< osg::Node > RockVisualization::createMainNode()
{
    osg::ref_ptr<osg::Group> mainNode = new osg::Group();
    
    //correct the offset of the model
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
    // print primitiv model if rock.osg was not found
    if (rockModel.get() == 0)
    {
        rockModel = printPrimitivModel();
    }
    
    rockModelPos->addChild(rockModel);
    
    return mainNode;
}

/**
 * This method provides a primitive model which is a simple sphere.
 */
osg::ref_ptr<osg::Node> RockVisualization::printPrimitivModel()
{
    osg::ref_ptr<osg::Sphere> sp = new osg::Sphere(osg::Vec3d(0,0,0), 0.35);
    osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(sp.get());
    sd->setColor(osg::Vec4(0.5f, 0.5f, 0.5f, 1.0f));
    osg::ref_ptr<osg::Geode> spGeode = new osg::Geode();
    spGeode->addDrawable(sd.get());
    
    // get rock texture
    char* osgPath = getenv("OSG_FILE_PATH");
    if (osgPath) 
    {
        std::string imgPath(osgPath);
        imgPath += "/rock.png";
        osg::Image* image = osgDB::readImageFile(imgPath);
        if (image)
        {
            osg::Texture2D* texture = new osg::Texture2D;
            texture->setDataVariance(osg::Object::DYNAMIC); 
            texture->setImage(image);
            osg::StateSet* stateOne = new osg::StateSet();

            stateOne->setTextureAttributeAndModes
                (0,texture,osg::StateAttribute::ON);

            spGeode->setStateSet(stateOne);
        }
    }
    
    return spGeode;
}

void RockVisualization::updateDataIntern ( base::samples::RigidBodyState const& value )
{
    p->data = value;
}

void RockVisualization::updateMainNode( osg::Node* node )
{
    //set actual position and orientation to the osg model
    position.set(p->data.position.x(), p->data.position.y(), p->data.position.z());
    orientation.set(p->data.orientation.x(), p->data.orientation.y(), p->data.orientation.z(), p->data.orientation.w());
    rockModelPos->setPosition(position);
    rockModelPos->setAttitude(orientation);
}

VizkitQtPluginImpl(RockVisualization)
}
