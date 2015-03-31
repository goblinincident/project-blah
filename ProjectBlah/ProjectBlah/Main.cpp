

#include <iostream>

#include <tutorials\Playground.cpp>

#include <tutorials\Cameras_and_projections.cpp>
#include <tutorials\Rendering_Geometry.cpp>

/** @brief
*  Un-comment desired tutorial to see it in action.
*
* @todo Convert project into library with acompanying sub-projects.
**/

int main()
{



	tutorials::Playground app;


	//tutorials::Cameras_and_Projections app;
	//tutorials::Rendering_Geometry app;



	app.Run();

	return 0;
};