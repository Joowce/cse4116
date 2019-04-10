cmake_minimum_required(VERSION 3.13)
project(embeded C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c services/log/log.c services/log/log.h services/proc.h services/signal/signal.c services/signal/signal.h services/message_queue/mq.c devices/type.h)
add_executable(input input.c services/log/log.c services/log/log.h services/message_queue/mq.h services/message_queue/mq.c devices/type.h devices/dot/font.h devices/dot/dot.c)