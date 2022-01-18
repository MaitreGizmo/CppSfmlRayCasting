#include "Utils.h"
#include "Settings.h"

using namespace gst;
using namespace std;

float Utils::degToRad(float deg)
{
	return deg * PI / 180.0f;
}

float Utils::radToDeg(float rad) {
	return 180.0f * rad / PI;
}
