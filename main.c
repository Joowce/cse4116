#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <ctype.h>

#include "services/log/log.h"
#include "services/proc.h"


int main() {
    pid_t input_p;
    input_p = execf("input");
    LOG__INFO("fork process");
    return 0;
}


