package com.example.custompuzzle.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;

import java.util.Timer;
import java.util.TimerTask;

public class TimerService extends Service {
    public interface RepeatedTask {
        void run (int sec);
    }

    public class TimerBinder extends Binder {
        public void startTimer (RepeatedTask task) {
            TimerService.this.startTimer(task);
        }

        public void cancelTimer () {
            TimerService.this.cancelTimer();
        }
    }

    private Timer timer;
    private int sec = 0;
    private IBinder binder = new TimerBinder();

    @Override
    public void onCreate() {
        timer = new Timer();
        sec = 0;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    @Override
    public void onDestroy() {
        cancelTimer();
        super.onDestroy();
    }

    private void cancelTimer() {
        timer.cancel();
        sec = 0;
    }

    private void startTimer(final RepeatedTask task) {
            this.cancelTimer();
            timer = new Timer();

            if (task == null) return;
            timer.scheduleAtFixedRate(new TimerTask() {
                @Override
                public void run() {
                    task.run(sec++);
                }
            }, 0L, 1000L);
    }
}
