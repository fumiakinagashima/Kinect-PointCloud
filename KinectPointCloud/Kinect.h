#pragma once
#include <k4a/k4a.hpp>
#include <k4a/k4atypes.h>

using namespace k4a;

class Kinect
{
public:
	Kinect();
	~Kinect();

	void Start();
	void Capture();

	short* PointCloudBuffer();
	uint32_t PointCloudSize();
	image ColorBuffer();

private:
	device m_device;
	
	k4a_device_configuration_t m_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	calibration m_calibration;
	transformation m_transformation;
	
	capture m_capture;
	image m_depthImage;
	image m_colorImage;
	image m_pointCloud;

	short* m_pointCloudBuffer;

};

