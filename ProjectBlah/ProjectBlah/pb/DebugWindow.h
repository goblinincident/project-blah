
#pragma once

struct CTwBar;

namespace pb
{
	class DebugWindow
	{
	protected:
		CTwBar* bar;
	public:
		virtual void OpenDebugWindow() = 0;
		virtual void CloseDebugWindow() = 0;
	protected:
		virtual void InititializeDebugWindow(std::string name);
	};
};