package com.example.custompuzzle;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.custompuzzle.model.Puzzle;

import java.util.Locale;

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
                PuzzleActivity.this.puzzleContainer.removeAllViewsInLayout();
                String rawInput = input.getText().toString();
                int[] dim = parseInteger(rawInput);
                int row = dim[0];
                int col = dim[1];
                Log.d(PuzzleActivity.class.getName(), "" + row + " " + col);

                puzzle = new Puzzle(row, col);
                PuzzleActivity.this.makeButtons(puzzle);
            }
        });
    }

    private void makeButtons(final Puzzle puzzle) {
        int[] size = puzzle.getSize();
        int row = size[0];
        int col = size[1];
        View.OnClickListener listener = makeButtonClickListener(puzzle);

        for (int i = 0; i < row; i++) {
            LinearLayout puzzleRow = new LinearLayout(this);
            puzzleRow.setOrientation(LinearLayout.HORIZONTAL);
            puzzleRow.setLayoutParams(new LayoutParams(
                    LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));

            for (int j = 0; j < col; j++) {
                Button btn = new Button(this);
                btn.setLayoutParams(new LinearLayout.LayoutParams(
                        LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
                btn.setTag(String.format(Locale.KOREA, "%d %d", i, j));
                int piece = puzzle.getPuzzle().get(i).get(j);

                btn.setId(piece);
                if (piece == row * col) setButtonStyle(btn, "", Color.LTGRAY);
                else setButtonStyle(btn,
                            String.format(Locale.KOREA, "%d", piece),
                            getResources().getColor(R.color.colorPrimaryLight));
                btn.setOnClickListener(listener);
                puzzleRow.addView(btn);
            }
            puzzleContainer.addView(puzzleRow);
        }
    }

    private void swapButton(int[] emptyButton, int[] destButton, Puzzle puzzle) {
        int piece = puzzle.getPuzzle().get(destButton[0]).get(destButton[1]);
        setButtonStyle(
                (Button) ((LinearLayout) this.puzzleContainer
                        .getChildAt(destButton[0]))
                        .getChildAt(destButton[1]),
                "",
                Color.LTGRAY);

        setButtonStyle(
                (Button) ((LinearLayout) this.puzzleContainer
                        .getChildAt(emptyButton[0]))
                        .getChildAt(emptyButton[1]),
                String.format(Locale.KOREA, "%d", piece),
                getResources().getColor(R.color.colorPrimaryLight));
    }

    private View.OnClickListener makeButtonClickListener (final Puzzle puzzle) {
        return new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int[] clicked = getClickedButtonIdx(view);
                if (!puzzle.isAvailableMove(clicked)) return;
                PuzzleActivity.this.swapButton(puzzle.getEmptyIndex(), clicked, puzzle);
                puzzle.moveEmpty(clicked);
                if (puzzle.checkFinished()) PuzzleActivity.this.endPuzzle();
            }
        };
    }

    private void endPuzzle() {
        Toast.makeText(this, "Puzzle Complete", Toast.LENGTH_SHORT).show();
        this.puzzleContainer.removeAllViewsInLayout();
        startActivity(new Intent(PuzzleActivity.this, MainActivity.class));
    }

    private static int[] getClickedButtonIdx(View view) {
        return parseInteger(view.getTag().toString());
    }

    static private int[] parseInteger (String raw) {
        String[] split = raw.split(" ");
        int row = 0;
        int col = 0;
        try {
            row = Integer.parseInt(split[0]);
            col = Integer.parseInt(split[1]);
        } catch (NumberFormatException e) {
            Log.e(PuzzleActivity.class.getName(), "Invalid Input: " + raw);
        }

        return new int[] { row, col };
    }

    static private void setButtonStyle (Button button, String text, int color) {
        button.setText(text);
        button.setBackgroundColor(color);
    }
}
