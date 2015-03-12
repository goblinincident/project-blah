

/** @file ProjectBlah.h 
* 
* @brief An overly simplified project that exists purely
* to crank out the tutorials.
* 
* @author Dennis
* @date	01-03-15
*
* @copyright Modify-it / share-it / masturbate-on-it,  don't care.
**/



/** @mainpage Project Blah
*
* @section guide Guide
* An introduction to the 'Project Blah'.
* <br><br><br>
*
* <hr>
* About
* -------------
* This project was developed to meet the requirements
* of the AIE tutorials found here: <a href="http://aieportal.aie.edu.au/course/view.php?id=239">AIE OpenGL Tutorials</a>
* <br><br>
*
* <hr>
* Quick Class Reference
* -------------
* @ref ProjectBlah - Main access to functionality needed to complete the tutorials
* @todo Turn the project into a static lib or dll set.
* <br><br>
*
* <hr>
* How to Use
* -------------
* Un-comment the desired project to see it in action.
* @code 
* Here is a bunch of code, do stuuff with this later
* @endcode
* <br>
*
* <hr> 
* Completed Tutorial Links
* -------------
* @ref IntroToOpenGL - Scene using a simple AIE Gizmo;
* <br><br>
**/



/** @brief
* All the shared functionality needed for the tutorials (might one day become a lib).
**/
namespace pb 
{};


#pragma once

#include <pb\Window.h>
#include <pb\Camera.h>
#include <pb\CameraFly.h>
#include <pb\Grid.h>
#include <pb\Dummy.h>
#include <pb\Time.h>

class ProjectBlah
{
public:
	void Run();

protected:

	ProjectBlah();
	~ProjectBlah();

	virtual void Initialize(){}
	virtual void Update(){}
	virtual void Shutdown(){}
};
