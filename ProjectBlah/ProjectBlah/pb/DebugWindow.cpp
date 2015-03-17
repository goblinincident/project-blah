
#include <ant\AntTweakBar.h>
#include <pb\Window.h>

#include <pb\DebugWindow.h>

namespace pb
{


	void DebugWindow::InititializeDebugWindow(const char* name)
	{
		if (bar != nullptr) return;

		bar = TwNewBar(name);
		std::string bar_setting = "'"; 
		bar_setting += name; 

		bar_setting += "' ";
		bar_setting +=
			"refresh=0.5 "
			"position='0 0' "
			"size='230 "; bar_setting += std::to_string(Window::GetWindow()->height - 20); bar_setting += "' ";
		TwDefine(bar_setting.c_str());
	}

}