set(CMAKE_C_COMPILER arm-none-linux-gnueabi-gcc)
cmake_minimum_required(VERSION 3.13)
project(embeded C)

set(CMAKE_C_STANDARD 11)


add_executable(main main.c services/log/log.c services/log/log.h services/proc.h services/signal/signal.c services/signal/signal.h services/mq/mq.h services/mq/mq.c controllers/device/itf.h devices/lcd/lcd_itf.h controllers/device/client/device_client.c controllers/device/client/device_client.h controllers/input/input_itf.h controllers/input/receiver/receiver.c controllers/input/receiver/receiver.h controllers/mode/mode.c controllers/mode/mode.h mode/clock/clock.c mode/clock/clock.h services/timer/timer.c services/timer/timer.h)
add_executable(input input.c services/log/log.c services/log/log.h services/shared_memory/shared_memory.c services/shared_memory/shared_memory.h services/signal/signal.c services/signal/signal.h controllers/input/sender/sender.c controllers/input/sender/sender.h devices/read_key/read_key.c devices/read_key/read_key.h devices/read_key/rk_itf.h controllers/input/input_itf.h devices/switch/switch.c devices/switch/switch.h devices/switch/switch_itf.h )
add_executable(output output.c services/log/log.c services/log/log.h services/mq/mq.h services/mq/mq.c devices/dot/font.h devices/dot/dot.c devices/dot/dot.h controllers/device/device.c controllers/device/device.h controllers/device/itf.h devices/dot/dot_itf.h devices/led/led.c devices/led/led.h devices/led/led_itf.h devices/led/light.h devices/lcd/lcd.c devices/lcd/lcd.h devices/lcd/lcd_itf.h devices/fnd/fnd.c devices/fnd/fnd.h devices/fnd/fnd_itf.h)