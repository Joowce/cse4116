package com.example.custompuzzle.service;

import android.app.Service;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;

import java.util.Timer;
import java.util.TimerTask;

public class TimerService extends Service {
    public interface RepeatedTask {
        void run (int sec);
    }
    private Timer timer;
    private int sec = 0;

    @Override
    public void onCreate() {
        timer = new Timer();
        sec = 0;
    }


    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Bundle extras = intent.getExtras();
        final RepeatedTask timerTask = extras != null ? (RepeatedTask) extras.get("timerTask") : null;
        timer.cancel();

        if (timerTask == null) return startId;
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                timerTask.run(sec++);
            }
        }, 0L, 1000L);
        return startId;
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        timer.cancel();
        sec = 0;
        super.onDestroy();
    }
}
