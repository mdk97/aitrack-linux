#pragma once
#include "Camera.h"

class NullCamera : public Camera
{
  public:
    inline NullCamera( int width = -1, int height = -1, int fps = 0 )
    {
        this->width  = width;
        this->height = height;
        this->fps    = fps;
    }

    inline ~NullCamera(){};
    inline void start_camera() override {}
    inline void stop_camera() override {}
    inline void get_frame( uint8_t *buffer ) override {}
    inline void set_settings( CameraSettings &settings ) override {}
    inline void set_settings( const CameraSettings &&settings ) override {}

    inline CameraSettings get_settings() override
    {
        CameraSettings settings;
        return settings;
    };
};
