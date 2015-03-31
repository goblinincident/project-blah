
#include <ant\AntTweakBar.h>
#include <pb\Window.h>
#include <string>
#include <pb\DebugWindow.h>

using namespace std;

namespace pb
{
	void DebugWindow::InititializeDebugWindow(string name)
	{
		if (bar != nullptr) return;

		bar = TwNewBar(name.c_str());
		std::string bar_setting = "'"; 
		bar_setting += name; 

		bar_setting += "' ";
		bar_setting +=
			"refresh=0.5 "
			"position='0 0' "
			"size='230 "; bar_setting += std::to_string(Window::GetHeight() - 20); bar_setting += "' ";
		TwDefine(bar_setting.c_str());
	}

}