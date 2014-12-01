### Tools and templates for OpenFrameworks

This repository contains a series of “tools” and “templates” for my projects involving [OpenFrameworks](openframeworks.cc). Tools and templates are analogous to [addons](http://www.ofxaddons.com) and examples in OF.

Tools contain classes for generating visual and audio content, organizing and handling parameters and interfaces, creating GUIs, communicating and interactivity with peripherals and other applications, etc. Like addons, they can be included with any OF project — the difference is that tools are higher-level and so less general than addons, being mostly specific to routines in my own work. 

Templates are to tools as examples are to addons. They are complete OF projects which demo the tools in simple ways. 


#### License

Everything in this repository is licensed [GNU General Public License v3](http://www.gnu.org/copyleft/gpl.html).


#### Tools/features

Control
 - base class of other tools for handling parameter sets
 - automatically generate gui (using ofxUI), handle OSC communication and generate TouchOSC layouts
 - modulate parameters with a sequencer
 - save and load presets

Visuals, Canvas, ProjectionMapping
 - visual content, shaders, movie/image player
 - manages a sequence of layers which create and modulate visual content in a quad
 - handles projection mapping of visual content
 - integration with [Syphon](http://syphon.v002.info/)
 - save and load presets of Canvas layer sequences and parameters

OpenNi, Kinect
 - routines for getting data from the kinect
 - track contours/blobs and skeleton features, create masks and visual content based on the data
 - calibrate to a projector with ofxKinectProjectorToolkit
 - get statistical features with ofxKinectFeatures

Learn
 - a patch-bay using machine learning to modulate a set of output parameters from a series of input parameters, based on [ofxLearn](https://github.com/genekogan/ofxLearn)

AudioUnit, SuperCollider
 - working with sound using [OSX AudioUnits](https://github.com/admsyn/ofxAudioUnit) and [SuperCollider](supercollider.sourceforge.net)
 

Algorithms
 - point generators (evenly spaced, circle packing, delaunay triangulation)
 - recursively subdivide a 2d polygon
 - time-based behaviors

LeapMotion
 - derive high-level features from [LeapMotion data](https://www.leapmotion.com/)

Manta
 - interface with the [Manta](www.snyderphonics.com/products.htm) touch controller


#### Usage

To use these in an OF project, the best place to put this repo is in your OF root folder, so that it is at the same level from your root folder as addons.

Many of the tools and templates require additional addons to function. This is a complete list of addons used in any of the templates, though not all templates require all addons.

Addons
 - [ofxUI (fork)](https://github.com/genekogan/ofxUI)
 - [ofxSecondWindow](https://github.com/genekogan/ofxSecondWindow)
 - [ofxCv](https://github.com/kylemcdonald/ofxCv)
 - [ofxOpenNi](https://github.com/gameoverhack/ofxOpenNI)
 - [ofxKinectProjectorToolkit](https://github.com/genekogan/ofxKinectProjectorToolkit)
 - [ofxKinectFeatures](https://github.com/asarasua/ofxKinectFeatures)
 - [ofxLearn](https://github.com/genekogan/ofxLearn)
 - [ofxSelfOrganizingMap](https://github.com/genekogan/ofxSelfOrganizingMap)
 - [ofxGMM](https://github.com/genekogan/ofxGMM)
 - [ofxSpreadsheet](https://github.com/genekogan/ofxSpreadsheet)
 - [ofxPointInPolyline](https://github.com/genekogan/ofxPointInPolyline)
 - [ofxTouchOsc](https://github.com/genekogan/ofxTouchOsc)
 - [ofxSequencer](https://github.com/genekogan/ofxSequencer)
 - [ofxBpm](https://github.com/mirrorboy714/ofxBpm)
 - [ofxConvexHull](https://github.com/genekogan/ofxConvexHull)
 - [ofxSyphon](https://github.com/astellato/ofxSyphon)
 - [ofxAudioUnit](https://github.com/admsyn/ofxAudioUnit)
 - [ofxSuperCollider](http://www.erase.net/projects/ofxSuperCollider/)
 - [ofxLeapMotion2](https://github.com/genekogan/ofxLeapMotion2)
 - [ofxTwistedRibbon](https://github.com/tado/ofxTwistedRibbon)
 - [ofxBlurShader](https://github.com/companje/ofxBlurShader)
 - [ofxDelaunay](https://github.com/obviousjim/ofxDelaunay)
 - [ofxPostGlitch](https://github.com/maxillacult/ofxPostGlitch)
 - [ofxPostProcessing](https://github.com/neilmendoza/ofxPostProcessing)
 - [ofxFx](https://github.com/patriciogonzalezvivo/ofxFX)
 - [ofxManta](https://github.com/genekogan/ofxManta/tree/master/src)
