package com.example.custompuzzle;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    /**
     * set view
     * register start button click listener
     * @param savedInstanceState instanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button startButton = findViewById(R.id.startButton);
        View.OnClickListener listener = new View.OnClickListener() {
            /**
             * go puzzle activity
             * @param view button view
             */
            @Override
            public void onClick(View view) {
                Log.i(MainActivity.class.getName(), "clicked");
                startActivity(new Intent(MainActivity.this, PuzzleActivity.class));
            }
        };
        startButton.setOnClickListener(listener);
    }
}
