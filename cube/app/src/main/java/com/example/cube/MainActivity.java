package com.example.cube;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.cube.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'cube' library on application startup.
    static {
        System.loadLibrary("cube");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Call the native methods from openglrenderer.cpp
        OpenGLRenderer.init();
        // Call other methods as needed
    }

    /**
     * A native method that is implemented by the 'cube' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}