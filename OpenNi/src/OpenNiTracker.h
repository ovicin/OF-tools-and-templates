#pragma once

#include "OpenNi.h"


class ContourRenderer;
class SkeletonRenderer;


class OpenNi
{
public:
    OpenNi();
    void setup(string oni="");
    void close();
    
    void enableUserTracking(int maxUsers=2);
    void enableContourTracking();
    
    void disableUserTracking();
    void disableContourTracking();
    
    void setCalibration(string path);
    
    void setupContourVisuals(int width, int height);
    void setupSkeletonVisuals(int width, int height);
    
    void start() {kinect.start();}
    void stop() {kinect.stop();}
    
    bool update();
    
    void draw();
    void drawCalibratedContours(int width=640, int height=480);
    void drawCalibratedSkeleton(int idx, int width=640, int height=480);
    
    void drawVisuals();
    
    void setMaxUsers(int maxUsers);
    void setNormalizeJoints(bool normalizeJoints) {this->normalizeJoints = normalizeJoints;}
    
    void setGuiPosition(int guiX, int guiY);
    void toggleGuiVisible();
    
    void getCalibratedContour(vector<cv::Point> &points, vector<ofVec2f> &calibratedPoints, int width, int height);

    ContourFinder & getContourFinder() {return contourFinder;}
    RectTracker & getContourTracker() {return contourFinder.getTracker();}
    
    int getNumUsers() {return kinect.getNumTrackedUsers();}
    
    vector<ofVec3f*> & getJoints(int idxUser);
    vector<ofVec3f*> & getNormalizedJoints(int idxUser);
    vector<ofVec2f>  & getProjectedJoints(int idxUser);
    
    string getJointName(int idx) {return jointNames[idx];}
    
private:
    
    void setupControl();
    
    void updateContours();
    void updateUsers();
    
    void checkTrackingOptions();
    void userEvent(ofxOpenNIUserEvent & event);
    
    // kinect
    ofxOpenNI kinect;
    ofxKinectProjectorToolkit kpt;
    ContourFinder contourFinder;
    ofxKinectFeatures featExtractor;
    bool calibrationLoaded;
    
    // kinect data
    vector<string> jointNames;
    vector<vector<ofVec3f*> > joints, normalizedJoints;
    vector<ofVec2f> projectedJoints;
    vector<ofVec3f> userBoundingBoxMin, userBoundingBoxMax;
    ofVec3f jointTorso, jointNeck, jointHead,
        jointLeftShoulder, jointLeftElbow, jointLeftHand,
        jointRightShoulder, jointRightElbow, jointRightHand,
        jointLeftHip, jointLeftKnee, jointLeftFoot,
        jointRightHip, jointRightKnee, jointRightFoot;
    
    Control control;
    int guiX, guiY;
    
    bool trackingContours, trackingUsers, trackingKeypoints;
    bool pTrackingContours, pTrackingUsers, pTrackingKeypoints;
    
    float minArea;
    float maxArea;
    float threshold;
    float persistence;
    float maxDistance;
    float nearThreshold;
    float farThreshold;
    int smoothness;
    bool curved;
    float smoothingRate;
    int maxUsers;
    bool normalizeJoints;
    
    ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage grayThreshNear;
	ofxCvGrayscaleImage grayThreshFar;
    ofShortPixels depthPixels;
    
    // drawing
    ContourRenderer *contourRenderer;
    SkeletonRenderer *skeletonRenderer;
    bool contourVisuals, skeletonVisuals;
};

