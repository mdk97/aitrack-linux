#pragma once

#include <QtCore/QSettings>
#include <string>


/**
 * Struct which holds both the program state and the serializable part of this
 * state (aka. preferences).
 */
struct ConfigData
{
    std::string ip;
    int         port;
    int         video_height;
    int         video_width;
    int         video_fps;
    double      prior_distance, camera_fov;
    bool        show_video_feed;
    bool        use_landmark_stab;
    bool        autocheck_updates;
    bool        tracking_shortcut_enabled;

    float x, y, z, yaw, pitch, roll;

    double head_scale_x, head_scale_y, head_scale_z;

    int selected_camera;
    int num_cameras_detected;
    int cam_exposure;
    int cam_gain;

    bool onnx_set_env_threads;
    int  onnx_env_threads;
    bool onnx_set_num_threads;
    int  onnx_num_threads;
    bool onnx_set_dynamic;
    int  onnx_dynamic;

    std::vector<std::string> model_names;
    int                      selected_model;

    static ConfigData getGenericConfig();
};


/**
 * Incharged of building/retrieving/saving a config object.
 */
class ConfigMgr
{
public:
    ConfigMgr( std::string ini_path );
    void       updateConfig( const ConfigData &data );
    ConfigData getConfig();

private:
    QSettings conf;
};