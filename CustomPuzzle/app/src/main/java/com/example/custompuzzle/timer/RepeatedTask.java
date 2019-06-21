package com.example.custompuzzle.timer;

public interface RepeatedTask {
    /**
     * method called whenever timer tick
     * @param sec timer duration
     */
    void run(int sec);
}
