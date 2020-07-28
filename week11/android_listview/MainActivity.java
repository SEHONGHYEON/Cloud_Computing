package com.example.temp;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    FirebaseDatabase db;
    DatabaseReference myRef;

    ArrayList<String> arrayList = new ArrayList<>();
    ArrayAdapter<String> arrayAdapter;

    ListView listV;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //logDHT 의 값을 참조
        myRef = db.getInstance().getReference("logDHT"); //DB에서 logDHT객체를 변수에 저장

        listV = (ListView)findViewById(R.id.lvList); //리스트뷰 변수

        //참조하는 자식에 데이터 넣어줌
       myRef.addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {
                //자식 객체값을 읽어들여 변수에 저장
                String temp = dataSnapshot.child("temperature").getValue().toString(); //온도
                String humi = dataSnapshot.child("humidity").getValue().toString(); //습도
                String time = dataSnapshot.child("time").getValue().toString(); //시간

                String weatherInfo ="온도: " + temp + "도\n" +  "습도: " + humi + "%\n" + "시간: " + time;


                // 레이아웃에 설정
                arrayList.add(0, weatherInfo);
                arrayAdapter = new ArrayAdapter<String>(MainActivity.this, android.R.layout.simple_list_item_1, arrayList);
                listV.setAdapter(arrayAdapter);
                arrayAdapter.notifyDataSetChanged();
            }

            @Override
            public void onChildChanged(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {

            }

            @Override
            public void onChildRemoved(@NonNull DataSnapshot dataSnapshot) {

            }

            @Override
            public void onChildMoved(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }
}