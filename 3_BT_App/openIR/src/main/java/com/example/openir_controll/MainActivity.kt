package com.example.openir_controll

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        /*start on Front Page*/
        setContentView(R.layout.activity_main)

        /* Handle Buttons*/
        About_Button.setOnClickListener { startActivity(Intent(this,About:: class.java)) }
        Modules_Button.setOnClickListener { startActivity(Intent(this, Modules::class.java))}
    }
}
