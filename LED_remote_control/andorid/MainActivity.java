package com.example.ledf;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    Button btn_LED_ON;
    Button btn_LED_OFF;
    TextView textView;

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference("LED_STATUS"); //데이터베이스에서 자식객체 reference

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.InitializeView();
        this.SetListener();
    }

    public void InitializeView() {
        btn_LED_ON = (Button)findViewById(R.id.btn1);
        btn_LED_OFF = (Button)findViewById(R.id.btn2);
        textView = (TextView)findViewById(R.id.textView);
        setTitle("LED Remote Control");
        textView.setText(myRef.getKey());
    }

    public  void SetListener() {

        myRef.addValueEventListener(new ValueEventListener() {
            //데이터베이스에서  값이 추가되면(변경)
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) { //스냇샵(상태)을 가져옴
                String ledState = (String) dataSnapshot.getValue(); //led의 상태값 변수에 저장
                //String value = dataSnapshot.getValue(String.class);

                textView.setText("LED is " + ledState);
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });

        // ON_Button 버튼 클릭시
        btn_LED_ON.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view)
            {
                textView.setBackgroundColor(Color.YELLOW);
                // db 상태값 on으로 전환
                myRef.setValue("ON");
            }
        });

        // OFF_Button 버튼 클릭 시
        btn_LED_OFF.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view)
            {
                textView.setBackgroundColor(Color.WHITE);
                //  db 상태값 off로 전환
                myRef.setValue("OFF");
            }
        });
    }
}///