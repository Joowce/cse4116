package com.example.custompuzzle;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class PuzzleActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_puzzle);

        Button startBtn = findViewById(R.id.startPuzzle);
        final TextView input = findViewById(R.id.buttonDimension);

        startBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String rawInput = input.getText().toString();
                int[] dim = PuzzleActivity.parseInput(rawInput);
                int row = dim[0];
                int col = dim[1];
                Log.d(PuzzleActivity.class.getName(), "" + row + " " + col);
//                PuzzleActivity.this.makeButtons(row, col);
            }
        });
    }

//    private void makeButtons(int row, int col) {
//
//    }

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

        int[] result = {row, col};
        return result;
    }
}
