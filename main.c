#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <ctype.h>

#include "services/log/log.h"
#include "services/proc.h"


int main() {
    pid_t p_input;
    pid_t p_output;

    p_input = execf("input");
    LOG__INFO("forked input process: %d", p_input);
    LOG__INFO("forked output process: %d", p_output);
    return 0;
}


