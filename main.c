#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "services/log/log.h"
#include "services/proc.h"


int main() {
    pid_t p_input;
    pid_t p_output;

    p_input = execf("input");
    p_output = execf("output");
    LOG_INFO("forked input process: %d", p_input);
    LOG_INFO("forked output process: %d", p_output);
    return 0;
}


