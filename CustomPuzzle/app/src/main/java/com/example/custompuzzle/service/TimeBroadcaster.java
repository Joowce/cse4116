package com.example.custompuzzle.service;

import android.content.Context;
import android.content.Intent;

import androidx.localbroadcastmanager.content.LocalBroadcastManager;

class TimeBroadcaster {
    static final public String TIMER_TICK =
            "com.example.custompuzzle.service.TimerService.TIMER_TICK";
    static final public String TIMER_TIME =
            "com.example.custompuzzle.service.TimerService.Time";

    private  LocalBroadcastManager broadcastManager;

    /**
     * timeBroadcaster constructor
     * @param context context that use this timeBroadcaster
     */
    TimeBroadcaster(Context context) {
        broadcastManager = LocalBroadcastManager.getInstance(context);
    }

    /**
     * broadcast sec message to broadcast receiver
     * @param sec sec
     */
    void broadcastTime(int sec) {
        Intent intent = new Intent(TIMER_TICK);
        intent.putExtra(TIMER_TIME, sec);
        broadcastManager.sendBroadcast(intent);
    }
}
