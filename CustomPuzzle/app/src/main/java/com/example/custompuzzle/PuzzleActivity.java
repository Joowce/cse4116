package com.example.custompuzzle;

import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.custompuzzle.model.Puzzle;

public class PuzzleActivity extends AppCompatActivity {
    private LinearLayout puzzleContainer;
    private Puzzle puzzle;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_puzzle);

        Button startBtn = findViewById(R.id.startPuzzle);
        final TextView input = findViewById(R.id.buttonDimension);
        puzzleContainer = findViewById(R.id.puzzleContainer);

        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String rawInput = input.getText().toString();
                int[] dim = PuzzleActivity.parseInput(rawInput);
                int row = dim[0];
                int col = dim[1];
                Log.d(PuzzleActivity.class.getName(), "" + row + " " + col);

                puzzle = new Puzzle(row, col);
                PuzzleActivity.this.makeButtons(puzzle);
            }
        });
    }

    private void makeButtons(Puzzle puzzle) {
        int[] size = puzzle.getSize();
        int row = size[0];
        int col = size[1];

        for (int i = 0; i < row; i++) {
            LinearLayout puzzleRow = new LinearLayout(this);
            puzzleRow.setOrientation(LinearLayout.HORIZONTAL);
            for (int j = 0; j < col; j++) {
                Button btn = new Button(this);
                btn.setLayoutParams(new LinearLayout.LayoutParams(
                        LinearLayout.LayoutParams.WRAP_CONTENT,
                        LinearLayout.LayoutParams.WRAP_CONTENT));

                int piece = puzzle.getPuzzle().get(i).get(j);

                btn.setId(piece);
                if (piece == row * col) btn.setBackgroundColor(Color.BLACK);
                else btn.setText(piece);
                puzzleRow.addView(btn);
            }
            puzzleContainer.addView(puzzleRow);
        }
    }

    private void swapButton(int[] idx1, int[] idx2) {
        Button btn1 = (Button) ((LinearLayout) puzzleContainer
                .getChildAt(idx1[0]))
                .getChildAt(idx1[1]);
        ((LinearLayout) puzzleContainer.getChildAt(idx1[0])).removeViewAt(idx1[1]);

        Button btn2 = (Button) ((LinearLayout) puzzleContainer
                .getChildAt(idx2[0]))
                .getChildAt(idx2[1]);
        ((LinearLayout) puzzleContainer.getChildAt(idx2[0])).removeViewAt(idx2[1]);

        ((LinearLayout) puzzleContainer.getChildAt(idx1[0])).addView(btn2, idx1[1]);
        ((LinearLayout) puzzleContainer.getChildAt(idx2[0])).addView(btn1, idx2[1]);
    }

    static private int[] parseInput (String raw) {
        String[] splitted = raw.split(" ");
        int row = 0;
        int col = 0;
        try {
            row = Integer.parseInt(splitted[0]);
            col = Integer.parseInt(splitted[1]);
        } catch (NumberFormatException e) {
            Log.e(PuzzleActivity.class.getName(), "Invalid Input: " + raw);
        }

        return new int[] { row, col };
    }
}
