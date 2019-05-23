CC=arm-none-linux-gnueabi-gcc
CFLAGS=-static -Wall
PWD = $(shell pwd)

SER_DIR = $(PWD)/services
CTRL_DIR = $(PWD)/controllers
DEV_DIR = $(PWD)/devices
MODE_DIR =$(PWD)/mode

INPUT_DEV = rk_dev.o sw_dev.o
OUTPUT_DEV = fnd_dev.o lcd_dev.o led_dev.o dot_dev.o

MAIN_OBJS = main.o log_service.o signal_service.o shared_memory_service.o mq_service.o timer_service.o dev_client_ctrl.o reciever_ctrl.o mode_ctrl.o clock_mode.o counter_mode.o editor_mode.o board_mode.o util_mode.o

INPUT_OBJS = input.o log_service.o signal_service.o shared_memory_service.o sender_ctrl.o $(INPUT_DEV)

OUTPUT_OBJS = output.o log_service.o signal_service.o mq_service.o dev_ctrl.o $(OUTPUT_DEV)

all: main input output

main: $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)
input: $(INPUT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(INPUT_OBJS)
output: $(OUTPUT_OBJS)
	$(CC) $(CFLAGS) -o $@ $(OUTPUT_OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<
input.o: input.c
	$(CC) $(CFLAGS) -c -o $@ $<
output.o: output.c	
	$(CC) $(CFLAGS) -c -o $@ $<

log_service.o: $(SER_DIR)/log/log.c
	$(CC) $(CFLAGS) -c -o $@ $<
signal_service.o: $(SER_DIR)/signal/signal.c
	$(CC) $(CFLAGS) -c -o $@ $<
shared_memory_service.o: $(SER_DIR)/shared_memory/shared_memory.c
	$(CC) $(CFLAGS) -c -o $@ $<
timer_service.o: $(SER_DIR)/timer/timer.c
	$(CC) $(CFLAGS) -c -o $@ $<
mq_service.o: $(SER_DIR)/mq/mq.c
	$(CC) $(CFLAGS) -c -o $@ $<

dev_ctrl.o:$(CTRL_DIR)/device/device.c
	$(CC) $(CFLAGS) -c -o $@ $<
dev_client_ctrl.o:$(CTRL_DIR)/device/client/device_client.c
	$(CC) $(CFLAGS) -c -o $@ $<
reciever_ctrl.o:$(CTRL_DIR)/input/receiver/receiver.c
	$(CC) $(CFLAGS) -c -o $@ $<
sender_ctrl.o:$(CTRL_DIR)/input/sender/sender.c
	$(CC) $(CFLAGS) -c -o $@ $<
mode_ctrl.o:$(CTRL_DIR)/mode/mode.c
	$(CC) $(CFLAGS) -c -o $@ $<

dot_dev.o: $(DEV_DIR)/dot/dot.c
	$(CC) $(CFLAGS) -c -o $@ $<
led_dev.o: $(DEV_DIR)/led/led.c
	$(CC) $(CFLAGS) -c -o $@ $<
lcd_dev.o: $(DEV_DIR)/lcd/lcd.c
	$(CC) $(CFLAGS) -c -o $@ $<
fnd_dev.o: $(DEV_DIR)/fnd/fnd.c
	$(CC) $(CFLAGS) -c -o $@ $<
rk_dev.o: $(DEV_DIR)/read_key/read_key.c
	$(CC) $(CFLAGS) -c -o $@ $<
sw_dev.o: $(DEV_DIR)/switch/switch.c
	$(CC) $(CFLAGS) -c -o $@ $<

clock_mode.o: $(MODE_DIR)/clock/clock.c
	$(CC) $(CFLAGS) -c -o $@ $<
counter_mode.o: $(MODE_DIR)/counter/counter.c
	$(CC) $(CFLAGS) -c -o $@ $<
editor_mode.o: $(MODE_DIR)/editor/editor.c
	$(CC) $(CFLAGS) -c -o $@ $<
board_mode.o: $(MODE_DIR)/board/board.c
	$(CC) $(CFLAGS) -c -o $@ $<
util_mode.o: $(MODE_DIR)/util/util.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(MAIN_OBJS) $(INPUT_OBJS) $(OUTPUT_OBJS) main input output

