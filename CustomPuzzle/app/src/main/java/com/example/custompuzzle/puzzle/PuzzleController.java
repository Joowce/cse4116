package com.example.custompuzzle.puzzle;

import android.content.Intent;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.example.custompuzzle.MainActivity;
import com.example.custompuzzle.PuzzleActivity;
import com.example.custompuzzle.service.TimeReceiver;
import com.example.custompuzzle.service.TimerService;
import com.example.custompuzzle.timer.RepeatedTask;

import java.util.Locale;

public class PuzzleController {
    private Puzzle puzzle;
    private TimeReceiver timeReceiver = new TimeReceiver();
    private PuzzleActivity view;

    /**
     * Puzzle controller constructor
     * set view
     * @param activity view
     */
    public PuzzleController(PuzzleActivity activity) {
        view = activity;
    }

    /**
     * parse input text
     * make puzzle model
     * request to view for making buttons with puzzle model
     * register broadcaster receiver for timer message
     * @param rawInput input text
     */
    public void startPuzzle (String rawInput) {
        int[] dim = parseInteger(rawInput);
        int row = dim[0];
        int col = dim[1];

        if (row > 5 || col > 5) {
            Toast.makeText(view, "row, col are too big", Toast.LENGTH_LONG).show();
            return;
        }

        puzzle = new Puzzle(row, col);
        view.makeButtons(puzzle, new View.OnClickListener() {
            /**
             * puzzle button click handler
             * get button index
             * if puzzle can move, change button style
             * @param buttonView: button view
             */
            @Override
            public void onClick(View buttonView) {
                int[] clicked = PuzzleActivity.getClickedButtonIdx(buttonView);
                if (!puzzle.isAvailableMove(clicked)) return;
                int num = puzzle.getPuzzle().get(clicked[0]).get(clicked[1]);
                view.setPuzzlePieceStyle(puzzle.getEmptyIndex(), num);
                view.setEmptyButtonStyle(clicked);
                puzzle.moveEmpty(clicked);
                if (puzzle.checkFinished()) endPuzzle();
            }
        });

        timeReceiver.registerReceiver(view, new RepeatedTask(){
            /**
             * run when get timer message
             * update time text
             * @param sec duration of timer
             */
            @Override
            public void run(int sec) {
                view.setTime(String.format(Locale.KOREA,
                        "%02d:%02d", sec / 60, sec % 60));
            }
        });
        view.startService(new Intent(view, TimerService.class));
    }

    /**
     * when puzzle completed end puzzle
     * unregister time receiver
     * stop service
     * create toast message
     * clear puzzle container
     * back to main activity
     */
    private void endPuzzle() {
        timeReceiver.unregisterReceiver();
        view.stopService(new Intent(view, TimerService.class));
        Toast.makeText(view, "Puzzle Complete", Toast.LENGTH_SHORT).show();
        view.clearPuzzle();
        view.startActivity(new Intent(view, MainActivity.class));
    }

    /**
     * parse text input to row, col
     * @param raw raw input
     * @return {row, col}
     */
    static public int[] parseInteger (String raw) {
        String[] split = raw.split(" ");
        int row = 0;
        int col = 0;

        if (split.length < 2) return new int[] { 0, 0 };
        try {
            row = Integer.parseInt(split[0]);
            col = Integer.parseInt(split[1]);
        } catch (NumberFormatException e) {
            Log.e(PuzzleActivity.class.getName(), "Invalid Input: " + raw);
        }

        return new int[] { row, col };
    }
}
