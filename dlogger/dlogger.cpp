#include <io.h>
#include <time.h>
#include <string.h>
#include "dlogger.h"

#ifdef _WIN32
#include <direct.h>
#endif // _WIN32

using namespace std;

dlogger* dlogger::m_instance = NULL;

dlogger::dlogger()
{
    m_fout = stdout;
    m_log_level = log_level_debug;
    memset(m_current_log_file_name, 0x00, 50);
}

dlogger::~dlogger()
{
    uninit_logger();
}

bool dlogger::init_logger(char* log_path, char* module_name, log_type_e type, log_level_e level)
{
    m_log_level = level;

    if (log_type_file == type)
    {
        if(log_path)
        {
            if (is_log_directory_exist(log_path))
            {
                return create_log_file(log_path, module_name);
            }
            else
            {
                if (create_log_directory(log_path))
                {
                    return create_log_file(log_path, module_name);
                }
            }
        }
    }
    else
    {
        m_fout = stdout;
    }
}

log_type_e dlogger::get_log_type()
{
    return m_log_type;
}

void dlogger::uninit_logger()
{
    if (log_type_file == m_log_type)
    {
        fclose(m_fout);
        m_fout = NULL;
    }
}

bool dlogger::is_log_directory_exist(char* log_dir)
{
    if (log_dir)
    {
        if (_access(log_dir, 0) == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

bool dlogger::create_log_directory(char* log_dir)
{
    //string log_dir_string(log_dir);
    if (log_dir)
    {
#ifdef _WIN32
        _mkdir(log_dir);
#endif // _WIN32
    }
    return true;
}

bool dlogger::create_log_file(char* log_path, char* module_name)
{
    char time_string[50] = { 0 };
    time_t t = time(0);
    strftime(time_string, 50, "%Y_%m_%d_%H", localtime(&t));
    if (log_path)
    {
        if (log_path[strlen(log_path) - 1] == '/')
        {
            sprintf(m_current_log_file_name, "%s%s.log", log_path, time_string);
        }
        else
        {
            sprintf(m_current_log_file_name, "%s/%s.log", log_path, time_string);
        }
    }

    m_fout = fopen(m_current_log_file_name, "w+");
    if (m_fout)
    {
        printf("create log file success.\n");
        return true;
    }
    else
    {
        printf("create log file failure.\n");
        return false;
    }
}

char* dlogger::get_local_time()
{
    //memset(m_time_string, 0x00, 50);
    time_t t = time(0);
    strftime(m_time_string, 50, "%Y/%m/%d %X", localtime(&t));
    return m_time_string;
}

FILE* dlogger::get_fout()
{
    return m_fout;
}

log_level_e dlogger::get_log_level()
{
    return m_log_level;
}


