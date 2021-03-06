#include "stdio.h"
#include "../dlogger/dlogger.h"

int main()
{
    //init sdk logger.
    if (!dlogger::get_instance()->init_logger("e://log", NULL, log_type_file, log_level_debug))
    {
        printf("logger init failure.\n");
        return -1;
    }

    int age = 28;
    LOG_INFO("my wife is a beautiful girl, her name is %s, and her age is %d.", "gaojing", age);

    dlogger::get_instance()->uninit_logger();

    return 0;
}