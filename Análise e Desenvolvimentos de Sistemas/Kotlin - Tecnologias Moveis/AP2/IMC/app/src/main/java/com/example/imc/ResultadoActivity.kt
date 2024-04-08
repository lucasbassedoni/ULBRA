package com.example.imc

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.activity_resultado2.*

class ResultadoActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_resultado2)

        val imc = intent.getParcelableExtra<IMC>("value")
        titleDensidadeCorporal.text = imc.nome.toString()
        textViewHeaderDensidadeCorporal.text = imc.calcular()
        textViewResultadoDensidadeCorporal.text = "Seu IMC: " + imc.imc.toString().substring(0, 5)
        textViewPeso.text = "Seu peso: " +  imc.peso.toString() + " kg"
        textViewAltura.text = "Sua altura: " + imc.altura.toString().substring(0, 3) + " cm"
    }
}
