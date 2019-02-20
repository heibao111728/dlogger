#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifdef _WIN32
#ifdef WINDOWS_DLOGGER_EXPORT
#define DLOGGER_EXPORT _declspec(dllexport)
#else
#define DLOGGER_EXPORT _declspec(dllimport)
#endif
#else
#define DLOGGER_EXPORT 
#endif

#include "stdio.h"

typedef enum log_type
{
    log_type_stdout = 1,
    log_type_file = 2
}log_type_e;

typedef enum log_level
{
    log_level_error = 1,
    log_level_debug = 2,
    log_level_info = 3,  
}log_level_e;

class DLOGGER_EXPORT dlogger
{
private:
    dlogger();
public:
    ~dlogger();

public:
    static dlogger* m_instance;
    static dlogger* get_instance()
    {
        if (NULL != m_instance)
        {
            return m_instance;
        }
        else
        {
            m_instance = new dlogger();
            return m_instance;
        }
    }

    bool init_logger(char* file_name, log_type_e type, log_level_e level);
    void uninit_logger();

    bool is_log_directory_exist(char* log_dir);
    bool create_log_directory(char* log_dir);

    char* get_local_time();

    FILE* get_fout();
    log_level_e get_log_level();
    log_type_e get_log_type();

private:
    FILE* m_fout;
    log_level_e m_log_level;
    log_type_e m_log_type;
    char m_time_string[50];
};

#define LOG_ERROR(fmt, ...) do{\
    if(log_level_error >= dlogger::get_instance()->get_log_level())\
    {\
        fprintf(dlogger::get_instance()->get_fout(), "%s %s %s:%d:" fmt "\n", dlogger::get_instance()->get_local_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        fflush(dlogger::get_instance()->get_fout());\
    }\
} while (0);\

#define LOG_DEBUG(fmt, ...) do{\
    if(log_level_debug >= dlogger::get_instance()->get_log_level())\
    {\
        fprintf(dlogger::get_instance()->get_fout(), "%s %s %s:%d:" fmt "\n", dlogger::get_instance()->get_local_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        fflush(dlogger::get_instance()->get_fout());\
    }\
} while (0);\

#define LOG_INFO(fmt, ...) do{\
    if(log_level_info >= dlogger::get_instance()->get_log_level())\
    {\
        fprintf(dlogger::get_instance()->get_fout(), "%s %s %s:%d:" fmt "\n", dlogger::get_instance()->get_local_time(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        fflush(dlogger::get_instance()->get_fout());\
    }\
} while (0);\



#endif // !__LOGGER_H__

