package com.example.custompuzzle.service;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import com.example.custompuzzle.timer.RepeatedTask;
import com.example.custompuzzle.timer.Timer;


public class TimerService extends Service {
    private Timer timer;
    private TimeBroadcaster broadcaster;

    /**
     * make instance of broadcaster and timer
     */
    @Override
    public void onCreate() {
        broadcaster = new TimeBroadcaster(this);
        timer = new Timer();
    }

    /**
     * this service is started service so do nothing
     * @param intent message
     * @return null
     */
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    /**
     * start timer
     * timer broadcast time each a second
     * @param intent message
     * @param flags flag
     * @param startId start id
     * @return start id
     */
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

    /**
     * cancel timer when service destroyed
     */
    @Override
    public void onDestroy() {
        cancelTimer();
        super.onDestroy();
    }

    /**
     * cancel timer
     */
    public void cancelTimer() {
        timer.endTimer();
    }

    /**
     * register task to timer
     * start timer
     * @param task task while timer running
     */
    public void startTimer(final RepeatedTask task) {
            this.cancelTimer();

            if (task == null) return;
            timer.setTask(task);
            timer.startTimer();
    }
}
