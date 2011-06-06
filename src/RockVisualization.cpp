#include "RockVisualization.hpp"
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osgText/Text>

namespace vizkit 
{

RockVisualization::RockVisualization()
{   
    /* Makes a method updatePose availabe on ruby side, which will call
     * the updateData method for the data type base::Pose.
     * This macro is optional. */ 
    VizPluginRubyAdapter(RockVisualization, base::Pose, Pose)
    
    /* This macro makes the method 'activateRockLabel' with a bool attribute
     * availabe in ruby, for configuration purposes */
    VizPluginRubyConfig(RockVisualization, bool, activateRockLabel)
    
    rockLabelActivated = false;
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
    
    if (rockLabelActivated)
    {
        // print a label that hovers over the rock
        rockLabel = printRockLabel();
        rockModelPos->addChild(rockLabel);
    }
    
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
        if (!image)
        {
            std::cout << "couldn't find texture rock.png" << std::endl;
        }
        else
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

/**
 * This method just provides a label.
 */
osg::ref_ptr<osg::Node> RockVisualization::printRockLabel()
{
       osg::ref_ptr<osgText::Text> label = new osgText::Text();
       osg::ref_ptr<osg::Geode> labelGeode = new osg::Geode();

       labelGeode->addDrawable(label);

       label->setCharacterSize(2);
       label->setText("Rock Tutorial");
       label->setAxisAlignment(osgText::Text::XZ_PLANE);

       label->setDrawMode(osgText::Text::TEXT);
       label->setAlignment(osgText::Text::CENTER_TOP);
       label->setPosition( osg::Vec3(0,0,1.5) );
       label->setColor( osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) );

       return labelGeode;
}

void RockVisualization::activateRockLabel(bool b)
{
    rockLabelActivated = b;
}

void RockVisualization::updateDataIntern ( const base::Pose& data )
{
    pose = data;
}

void RockVisualization::updateMainNode( osg::Node* node )
{
    //set actual position and orientation to the osg model
    position.set(pose.position.x(), pose.position.y(), pose.position.z());
    orientation.set(pose.orientation.x(), pose.orientation.y(), pose.orientation.z(), pose.orientation.w());
    rockModelPos->setPosition(position);
    rockModelPos->setAttitude(orientation);
}

}
