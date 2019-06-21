package com.example.custompuzzle.service;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.example.custompuzzle.timer.RepeatedTask;


public class TimeReceiver extends BroadcastReceiver {
    RepeatedTask task;
    Context context;

    public void registerReceiver(Context context, RepeatedTask task) {
        this.task = task;
        this.context = context;
        LocalBroadcastManager.getInstance(this.context).registerReceiver(
                this,
                new IntentFilter(TimeBroadcaster.TIMER_TICK));
    }

    public void unregisterReceiver() {
        if (context == null) return;
        LocalBroadcastManager.getInstance(context).unregisterReceiver(this);
        context = null;
        task = null;
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        int sec = intent.getIntExtra(TimeBroadcaster.TIMER_TIME, 0);
        if (task != null) task.run(sec);
    }
}
