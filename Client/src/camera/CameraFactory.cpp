#include "CameraFactory.h"

#include "NullCamera.h"
#include "OCVCamera.h"

std::unique_ptr<Camera> CameraFactory::buildCamera( int width, int height, int cam_index, int exposure, int gain )
{
    std::unique_ptr<Camera> camera;
    bool                    error = false;

    try
    {
        camera = std::make_unique<OCVCamera>( width, height, 60, cam_index );
    }
    catch ( std::exception &e )
    {
        error = true;
    }

    if ( error )
    {
        camera = std::make_unique<NullCamera>();
    }

    return camera;
}

std::vector<std::shared_ptr<Camera>> CameraFactory::getCameras( CameraSettings &settings )
{
    std::vector<std::shared_ptr<Camera>> cams;

    for ( int i = 0; i < 5; i++ )
    {
        try
        {
            std::shared_ptr<Camera> c = std::make_shared<OCVCamera>( settings.width, settings.height, settings.fps, i );
            c->set_settings( settings ); // Brightness / Exposure
            cams.push_back( std::move( c ) );
            std::cout << "Found ID: " << i << std::endl;
        }
        catch ( const std::exception & )
        {
            std::cout << "Not found device" << i << std::endl;
        }
    }

    return cams;
}
