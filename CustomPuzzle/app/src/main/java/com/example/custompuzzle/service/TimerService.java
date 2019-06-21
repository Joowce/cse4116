package com.example.custompuzzle.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import com.example.custompuzzle.timer.RepeatedTask;
import com.example.custompuzzle.timer.Timer;


public class TimerService extends Service {
    private Timer timer;
    private TimeBroadcaster broadcaster;

    @Override
    public void onCreate() {
        broadcaster = new TimeBroadcaster(this);
        timer = new Timer();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startTimer(new RepeatedTask() {
            @Override
            public void run(int sec) {
                broadcaster.broadcastTime(sec);
            }
        });
        return startId;
    }

    @Override
    public void onDestroy() {
        cancelTimer();
        super.onDestroy();
    }

    public void cancelTimer() {
        timer.endTimer();
    }

    public void startTimer(final RepeatedTask task) {
            this.cancelTimer();

            if (task == null) return;
            timer.setTask(task);
            timer.startTimer();
    }
}
