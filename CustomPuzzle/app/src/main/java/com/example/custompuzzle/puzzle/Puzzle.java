package com.example.custompuzzle.puzzle;

import android.util.Log;

import java.util.ArrayList;
import java.util.Random;


public class Puzzle {
    private ArrayList<ArrayList<Integer>> puzzle;
    private int row;
    private int col;
    private int[] emptyIndex = new int[] {0, 0};

    public Puzzle(int row, int col) {
        puzzle = new ArrayList<>();

        int i, j;
        for (i = 0; i < row; i++) {
            ArrayList<Integer> pieces = new ArrayList<>();
            for (j = 0; j < col; j++) {
                pieces.add(j * row + i + 1);
            }
            puzzle.add(pieces);
        }
        this.row = row;
        this.col = col;
        this.emptyIndex[0] = row - 1;
        this.emptyIndex[1] = col - 1;

        this.shuffle();
    }

    private void shuffle() {
        Random rand = new Random();
        for (int i = row * col - 1; i > 0; i--) {
            int changingIdx = rand.nextInt(i);
            int changingRow = changingIdx / col;
            int changingCol = changingIdx % col;
            int temp = puzzle.get(changingRow).get(changingCol);
            puzzle.get(changingRow)
                    .set(changingCol, puzzle.get(i / col).get(i % col));
            puzzle.get(i / col).set(i % col, temp);

            if (temp == row * col) {
                emptyIndex[0] = i / col;
                emptyIndex[1] = i % col;
            } else if (puzzle.get(changingRow).get(changingCol) == row * col) {
                emptyIndex[0] = changingRow;
                emptyIndex[1] = changingCol;
            }
        }
    }

    public ArrayList<ArrayList<Integer>> getPuzzle() {
        return this.puzzle;
    }

    public int[] getSize() {
        return new int[] {
                this.row, this.col
        };
    }

    public int[] getEmptyIndex() {
        return this.emptyIndex;
    }

    private void setEmptyIndex(int r, int c) {
        this.emptyIndex[0] = r;
        this.emptyIndex[1] = c;
    }

    public void moveEmpty(int[] dest) {
        int temp = this.puzzle.get(dest[0]).get(dest[1]);
        int emptyVal = this.puzzle.get(this.emptyIndex[0]).get(this.emptyIndex[1]);
        this.puzzle.get(dest[0]).set(dest[1], emptyVal);
        this.puzzle.get(this.emptyIndex[0]).set(this.emptyIndex[1], temp);
        this.setEmptyIndex(dest[0], dest[1]);
    }

    public boolean isAvailableMove(int[] idx) {
        Log.i(Puzzle.class.getName(), "idx: " + idx[0] + " " + idx[1]);
        return Math.abs(idx[0] - emptyIndex[0]) + Math.abs(idx[1] - emptyIndex[1]) == 1;
    }

    public boolean checkFinished() {
        int cnt = 1;
        for (ArrayList<Integer> row: this.puzzle) {
            for (int val: row) {
                if (cnt != val) return false;
                cnt++;
            }
        }
        return true;
    }
}
