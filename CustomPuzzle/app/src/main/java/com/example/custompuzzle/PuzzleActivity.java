package com.example.custompuzzle;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.custompuzzle.puzzle.Puzzle;
import com.example.custompuzzle.puzzle.PuzzleController;

import java.util.Locale;


public class PuzzleActivity extends AppCompatActivity {
    private LinearLayout puzzleContainer;
    private TextView timerText;
    private PuzzleController controller;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_puzzle);

        Button startBtn = findViewById(R.id.startPuzzle);
        final TextView input = findViewById(R.id.buttonDimension);
        puzzleContainer = findViewById(R.id.puzzleContainer);
        timerText = findViewById(R.id.timer);

        controller = new PuzzleController(this);

        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                PuzzleActivity.this.clearPuzzle();
                controller.startPuzzle(input.getText().toString());
            }
        });
    }

    public void setTime(String string) {
        timerText.setText(string);
    }

    public void makeButtons(final Puzzle puzzle, View.OnClickListener listener) {
        int[] size = puzzle.getSize();
        int row = size[0];
        int col = size[1];

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
                btn.setWidth(puzzleContainer.getWidth() / col);
                btn.setHeight(puzzleContainer.getHeight() / row);

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

    public void setPuzzlePieceStyle(int[] idx, int num) {
        setButtonStyle((Button) ((LinearLayout) this.puzzleContainer
                        .getChildAt(idx[0]))
                        .getChildAt(idx[1]),
                String.format(Locale.KOREA, "%d", num),
                getResources().getColor(R.color.colorPrimaryLight));
    }
    public void setEmptyButtonStyle(int[] idx) {
        setButtonStyle((Button) ((LinearLayout) this.puzzleContainer
                        .getChildAt(idx[0]))
                        .getChildAt(idx[1]),
                "",
                Color.LTGRAY);
    }

    public void clearPuzzle() {
        this.puzzleContainer.removeAllViewsInLayout();
    }

    public static int[] getClickedButtonIdx(View view) {
        return PuzzleController.parseInteger(view.getTag().toString());
    }

    static private void setButtonStyle (Button button, String text, int color) {
        button.setText(text);
        button.setBackgroundColor(color);
    }
}
