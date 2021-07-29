#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#include <streambuf>
#endif

#include <QtWidgets/QApplication>
#include "view/WindowMain.h"
#include "presenter/presenter.h"
#include "model/Config.h"
#include <omp.h>
#include "tracker/TrackerFactory.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <stdlib.h>
#include "model/UpdateChecker.h"
#include <filesystem>

int main(int argc, char *argv[])
{
    std::string prefs_path{"/home/"};
    std::string user{ (const char *)getenv("USER") };

    prefs_path.append(user);
    prefs_path.append("/.local/share/aitrack");

    std::filesystem::path path(prefs_path);
    if (not std::filesystem::exists(path))
    {
        std::filesystem::create_directory(path);
    }

    prefs_path.append("/");

    putenv((char *)"OMP_NUM_THREADS=1");
    omp_set_num_threads(1);  // Disable ONNX paralelization so we dont steal all cpu cores.
    omp_set_dynamic(0);

#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


    
    std::shared_ptr<spdlog::logger> logger;
    try
    {
        logger = spdlog::basic_logger_mt("aitrack", prefs_path + "log.txt", true);
        logger->flush_on(spdlog::level::info);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }


    logger->info(" ----------  AITRACK LOG   ----------");


    QApplication app(argc, argv);

    WindowMain w;
    w.show();
    
    auto conf_mgr = std::make_unique<ConfigMgr>(prefs_path + "prefs.ini");
    logger->info("Created/Found prefs.ini");

    auto t_factory = std::make_unique<TrackerFactory>(prefs_path + "models/");

    Presenter p((IView&)w, std::move(t_factory), std::move(conf_mgr));
    logger->info("App initialized");

    return app.exec();
}
