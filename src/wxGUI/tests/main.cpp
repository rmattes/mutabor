#include "src/kernel/Defs.h"
#include "src/wxGUI/tests/MkIDlist.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/kernel/routing/Route-inlines.h"
#include "wx/app.h"
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>

// Skip the GUI related checks from DebugRoute.cpp
//#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
//#undef no_wxGUI

int 
main(int argc, char** argv)
{
	wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");
	
	wxInitializer initializer;
	if ( !initializer )
	{
		fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
		return -1;
	}


	// We are using .png files for some extra bitmaps.
	wxImageHandler * pnghandler = new wxPNGHandler;
	wxImage::AddHandler(pnghandler);
	wxImage::AddHandler(new wxGIFHandler);

	mutaborGUI::initMutIconShapes();
	mutaborGUI::InitGUIRouteFactories();


	

#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that cppunit is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	CPPUNIT_NS::TextUi::TestRunner runner;
	
	CppUnit::BriefTestProgressListener listener; 
	runner.eventManager().addListener(&listener);

	runner.addTest( MkIDlist::suite() );
	
	bool wasSuccessful = runner.run();

	return wasSuccessful ? 0 : 1;
}
