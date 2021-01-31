#include "ESCamera.h"
#include <opencv2/core.hpp>
#include <iostream>

bool ESCamera::is_camera_available()
{
	return false;
}

ESCamera::ESCamera(int width, int height, int fps, int index) :
	Camera(width, height, fps),
	capture()
{
	cam_index = index;
	capture.mHeight = height;
	capture.mWidth = width;
	capture.mTargetBuf = new int[capture.mWidth * capture.mHeight];
}

ESCamera::~ESCamera()
{
	this->stop_camera();
	delete(capture.mTargetBuf);
}

void ESCamera::start_camera()
{
	int devices = setupESCAPI();
	std::cout << devices << std::endl;

	if (initCapture(cam_index, &capture) == 0)
	{
		printf("Capture failed - device may already be in use.\n");
		return;
	}
}

void ESCamera::stop_camera()
{
	deinitCapture(this->cam_index);
}

void ESCamera::get_frame(uint8_t* buffer)
{
	// TODO Make more efficient
	doCapture(0);
	// Active wait untill the frame is captured.
	// Warning: This could cause the program freeze if the user
	// unplugs the camera while it's capturing video.
	while (isCaptureDone(0) == 0) {}

	uint8_t* ptr = (uint8_t*)capture.mTargetBuf;

	// MSMF uses RGBA format. We need to copy only the 3 first channels.
	for (int i = 0; i < capture.mHeight * capture.mWidth; i++)
	{
		buffer[i * 3] = ptr[i * 4];
		buffer[i * 3+1] = ptr[i * 4 +1];
		buffer[i * 3 +2 ] = ptr[i * 4 +2];
	}
}

void ESCamera::set_settings(CameraSettings& settings)
{
}

CameraSettings ESCamera::get_settings()
{
	return CameraSettings();
}

int ESCamera::init_cameras()
{
	// Loads the ESCAPI dll and returns the number of compatible devices. 
	return setupESCAPI();
}
