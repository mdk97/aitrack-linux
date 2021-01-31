#pragma once
#include "Camera.h"
#include "escapi.h"

class ESCamera : public Camera
{
private:
	int cam_native_height, cam_native_width, cam_native_fps;
	int cam_index;

	SimpleCapParams capture;

	bool is_camera_available();
public:
	ESCamera(int width = 640, int height = 480, int fps = 30, int index = 0);
	~ESCamera();

	void start_camera();
	void stop_camera();
	void get_frame(uint8_t* buffer);
	void set_settings(CameraSettings& settings);
	CameraSettings get_settings();
	static int init_cameras();
};

