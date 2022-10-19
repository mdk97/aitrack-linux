#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#include <streambuf>
#endif

#include "model/Config.h"
#include "model/UpdateChecker.h"
#include "presenter/presenter.h"
#include "tracker/TrackerFactory.h"
#include "view/WindowMain.h"
#include <QtWidgets/QApplication>
#include <codecvt>
#include <cstdlib>
#include <filesystem>
#include <omp.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

int main( int argc, char *argv[] )
{
    std::string prefs_path{ "/home/" };
    std::string models_path{ "/usr/share/aitrack/" };
    std::string user{ (const char *) getenv( "USER" ) };

    prefs_path.append( user );
    prefs_path.append( "/.local/share/aitrack" );

    std::filesystem::path path( prefs_path );
    if ( not std::filesystem::exists( path ) )
    {
        std::filesystem::create_directory( path );
    }

    prefs_path.append( "/" );

    putenv( (char *) "OMP_NUM_THREADS=1" );
    omp_set_num_threads( 1 ); // Disable ONNX paralelization so we dont steal all cpu cores.
    omp_set_dynamic( 0 );

    std::shared_ptr<spdlog::logger> logger;
    try
    {
        logger = spdlog::basic_logger_mt( "aitrack", prefs_path + "log.txt", true );
        logger->flush_on( spdlog::level::info );
    }
    catch ( const spdlog::spdlog_ex &ex )
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }

    logger->info( " ----------  AITRACK LOG   ----------" );

    auto conf_mgr = std::make_unique<ConfigMgr>( "./prefs.ini" );
    logger->info( "Created/Found prefs.ini" );

    auto state = conf_mgr->getConfig();
    if ( state.onnx_set_env_threads )
    {
        std::wstring ws = std::to_wstring( state.onnx_env_threads );
        putenv( (char *) ( "OMP_NUM_THREADS=" + converter.to_bytes( ws ) ).c_str() );
    }
    if ( state.onnx_set_num_threads )
    {
        omp_set_num_threads( state.onnx_num_threads );
    }
    if ( state.onnx_set_dynamic )
    {
        omp_set_dynamic( state.onnx_dynamic );
    }

    QApplication app( argc, argv );

    WindowMain w;
    w.show();

    auto t_factory = std::make_unique<TrackerFactory>( models_path + "models/" );

    Presenter p( (IView &) w, std::move( t_factory ), std::move( conf_mgr ) );
    logger->info( "App initialized" );

    return app.exec();
}
