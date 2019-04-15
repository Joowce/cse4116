# cross compiler arm-none-linux-gnueabi-gcc
set(CMAKE_C_COMPILER arm-none-linux-gnueabi-gcc)

cmake_minimum_required(VERSION 3.13)
project(embeded C)

set(CMAKE_C_STANDARD 11)

# 서비스 관련 변수 설정
set(SERVICES services)
set(SHM ${SERVICES}/shared_memory/shared_memory.c ${SERVICES}/shared_memory/shared_memory.h)
set(LOG ${SERVICES}/log/log.c ${SERVICES}/log/log.h)
set(SIG ${SERVICES}/signal/signal.c ${SERVICES}/signal/signal.h)
set(MQ  ${SERVICES}/mq/mq.h ${SERVICES}/mq/mq.c)
set(TIMER ${SERVICES}/timer/timer.c ${SERVICES}/timer/timer.h)

# controller 관련 변수 설정
set(CTRL controllers)
set(CTRL_OUTPUT_DEV ${CTRL}/device/device.c ${CTRL}/device/device.h ${CTRL}/device/itf.h)
set(CTRL_DEV_CLIENT ${CTRL}/device/itf.h ${CTRL}/device/client/device_client.c ${CTRL}/device/client/device_client.h)
set(CTRL_INPUT_SENDER ${CTRL}/input/sender/sender.c ${CTRL}/input/sender/sender.h)
set(CTRL_INPUT_RECEIVER ${CTRL}/input/input_itf.h ${CTRL}/input/receiver/receiver.c ${CTRL}/input/receiver/receiver.h)
set(CTRL_MODE ${CTRL}/mode/mode.c ${CTRL}/mode/mode.h)

# device 관련 변수 설정
set(DEVICES devices)

set(DEVICE_DOT_DIR ${DEVICES}/dot)
set(DEVICE_DOT ${DEVICE_DOT_DIR}/font.h ${DEVICE_DOT_DIR}/dot.h ${DEVICE_DOT_DIR}/dot.c ${DEVICE_DOT_DIR}/dot_itf.h)

set(DEVICE_LED_DIR ${DEVICES}/led)
set(DEVICE_LED  ${DEVICE_LED_DIR}/led.c ${DEVICE_LED_DIR}/led.h ${DEVICE_LED_DIR}/led_itf.h ${DEVICE_LED_DIR}/light.h)

set(DEVICE_LCD_DIR ${DEVICES}/lcd)
set(DEVICE_LCD ${DEVICE_LCD_DIR}/lcd.c ${DEVICE_LCD_DIR}/lcd.h ${DEVICE_LCD_DIR}/lcd_itf.h)

set(DEVICE_FND_DIR ${DEVICES}/fnd)
set(DEVICE_FND ${DEVICE_FND_DIR}/fnd.c ${DEVICE_FND_DIR}/fnd.h ${DEVICE_FND_DIR}/fnd_itf.h)

set(DEVICE_RK_DIR ${DEVICES}/read_key)
set(DEVICE_RK ${DEVICE_RK_DIR}/read_key.c ${DEVICE_RK_DIR}/read_key.h ${DEVICE_RK_DIR}/rk_itf.h)

set(DEVICE_SW_DIR ${DEVICES}/switch)
set(DEVICE_SW ${DEVICE_SW_DIR}/switch.c ${DEVICE_SW_DIR}/switch.h ${DEVICE_SW_DIR}/switch_itf.h)

set(OUTPUT_DEVICES ${DEVICE_DOT} ${DEVICE_LED} ${DEVICE_LCD} ${DEVICE_FND})
set(INPUT_DEVICES ${DEVICE_SW} ${DEVICE_RK})


# mode 관련 변수 설정
set(MODE_DIR mode)

set(MODE_CLOCK ${MODE_DIR}/clock/clock.c ${MODE_DIR}/clock/clock.h)

set(MODES ${MODE_CLOCK})

add_executable(main main.c ${LOG} services/proc.h ${SIG} ${SHM} ${MQ} ${TIMER} devices/lcd/lcd_itf.h ${CTRL_DEV_CLIENT} ${CTRL_INPUT_RECEIVER} ${CTRL_MODE} ${MODES})
add_executable(input input.c ${LOG} ${SHM} ${SIG} ${CNTRL_INPUT_SENDER} ${INPUT_DEVICES})
add_executable(output output.c ${LOG} ${MQ} ${CTRL_OUTPUT_DEV} ${OUTPUT_DEVICES})