package com.example.graph;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    WebView wview;
    FirebaseDatabase db;
    DatabaseReference myRef;
   // TextView textView,  textView2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        wview = findViewById(R.id.wv);
        //textView = (TextView) findViewById (R.id.textView);
        //textView2 = (TextView) findViewById (R.id.textView2);

        WebSettings settings = wview.getSettings();
        settings.setJavaScriptEnabled(true);

        wview.setWebViewClient(new WebViewClient());
        wview.setWebChromeClient(new WebChromeClient());

        wview.loadUrl("file//android_asset/graph.html");


     }
}



