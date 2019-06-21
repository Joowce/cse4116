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

    /**
     * register broadcast receiver to android
     * @param context component that use this broadcast receiver
     * @param task task that run when get message
     */
    public void registerReceiver(Context context, RepeatedTask task) {
        this.task = task;
        this.context = context;
        LocalBroadcastManager.getInstance(this.context).registerReceiver(
                this,
                new IntentFilter(TimeBroadcaster.TIMER_TICK));
    }

    /**
     * unregister receiver
     * initialize members
     */
    public void unregisterReceiver() {
        if (context == null) return;
        LocalBroadcastManager.getInstance(context).unregisterReceiver(this);
        context = null;
        task = null;
    }

    /**
     * callback method called when get message
     * get sec from intent
     * run task that already registered
     * @param context component that use this receiver
     * @param intent message contained time
     */
    @Override
    public void onReceive(Context context, Intent intent) {
        int sec = intent.getIntExtra(TimeBroadcaster.TIMER_TIME, 0);
        if (task != null) task.run(sec);
    }
}
