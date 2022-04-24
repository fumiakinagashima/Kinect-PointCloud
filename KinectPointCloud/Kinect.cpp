#include "Kinect.h"
 
Kinect::Kinect() :
	m_pointCloudBuffer(nullptr)
{
	m_config.camera_fps = K4A_FRAMES_PER_SECOND_15;
	m_config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
	m_config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
	m_config.color_resolution = K4A_COLOR_RESOLUTION_720P;
	m_config.synchronized_images_only = true;
}

Kinect::~Kinect()
{
	m_capture.reset();
	m_device.stop_cameras();
	m_device.close();
}

void Kinect::Start()
{
	m_device = device::open(0);
	m_device.start_cameras(&m_config);
	m_calibration = m_device.get_calibration(m_config.depth_mode, m_config.color_resolution);
	m_transformation = transformation(m_calibration);
}

void Kinect::Capture()
{
	m_device.get_capture(&m_capture, std::chrono::milliseconds(K4A_WAIT_INFINITE));

	m_depthImage = m_capture.get_depth_image();
	m_colorImage = m_capture.get_color_image();
	
	m_pointCloud = m_transformation.depth_image_to_point_cloud(m_depthImage, K4A_CALIBRATION_TYPE_DEPTH);
	m_pointCloudBuffer = (short*)m_pointCloud.get_buffer();
}

short* Kinect::PointCloudBuffer() { return m_pointCloudBuffer; }
uint32_t Kinect::PointCloudSize() { return m_pointCloud.get_width_pixels() * m_pointCloud.get_height_pixels() * 3; }
image Kinect::ColorBuffer() { return m_transformation.color_image_to_depth_camera(m_depthImage, m_colorImage); }