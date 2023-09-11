#pragma once

#include "CameraSettings.h"
#include <cstdint>

class Camera
{
public:
    int  width, height, fps;
    bool is_valid = false;

    virtual void           start_camera()                                  = 0;
    virtual void           stop_camera()                                   = 0;
    virtual void           get_frame( uint8_t *buffer )                    = 0;
    virtual void           set_settings( CameraSettings &settings )        = 0;
    virtual void           set_settings( const CameraSettings &&settings ) = 0;
    virtual CameraSettings get_settings()                                  = 0;
    inline virtual ~Camera(){};
};