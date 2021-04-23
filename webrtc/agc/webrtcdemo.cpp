// webrtc.cpp: 定义应用程序的入口点。
//

#include "webrtcdemo.h"
#include "modules/audio_processing/gain_control_impl.h"
using namespace std;

int main()
{
	webrtc::GainControlImpl imp;
	cout << "Hello CMake." << endl;
	return 0;
}
