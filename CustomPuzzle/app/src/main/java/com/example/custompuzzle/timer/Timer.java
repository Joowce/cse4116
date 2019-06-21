package com.example.custompuzzle.timer;

import android.os.Handler;
import android.os.Message;

public class Timer extends Handler {
    private static final int MESSAGE_TIMER_START = 0;
    private static final int MESSAGE_TIMER_REPEAT = 1;
    private static final int MESSAGE_TIMER_END = -1;
    private static final int interval = 1000;

    private int seconds = 0;
    private RepeatedTask task = null;

    @Override
    public void handleMessage (Message msg) {
        switch (msg.what) {
            case MESSAGE_TIMER_START:
                seconds = 0;
                this.removeMessages(MESSAGE_TIMER_REPEAT);
                this.sendEmptyMessageDelayed(MESSAGE_TIMER_REPEAT, interval);
                break;
            case MESSAGE_TIMER_REPEAT:
                seconds++;
                if (task != null) task.run(seconds);
                this.sendEmptyMessageDelayed(MESSAGE_TIMER_REPEAT, interval);
                break;
            case MESSAGE_TIMER_END:
                this.removeMessages(MESSAGE_TIMER_REPEAT);
                break;
            default: break;
        }
    }

    public void setTask(RepeatedTask task) {
        this.task = task;
    }

    public void endTimer() {
        this.sendEmptyMessage(MESSAGE_TIMER_END);
    }

    public void startTimer() {
        this.sendEmptyMessage(MESSAGE_TIMER_START);
    }
}
