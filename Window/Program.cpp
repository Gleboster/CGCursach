#include "MainWindow.h"

using namespace Window;
using namespace TestLibrary1;


int main() {
	(gcnew TestLibrary1::Class1())->printHello();
	Application::Run(gcnew MainWindow());
	return 1;
}
