package net.christianbeier.droidvnc_ng.sockets

import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import android.net.wifi.WifiManager
import android.os.Build
import android.os.Bundle
import android.telephony.TelephonyManager
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.annotation.RequiresApi
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.Text
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.core.content.ContextCompat
import net.christianbeier.droidvnc_ng.sockets.configSockets.CommandsRemoteService
import net.christianbeier.droidvnc_ng.sockets.configSockets.DecryptTextTest
import net.christianbeier.droidvnc_ng.sockets.configSockets.EncryptTextTest
import net.christianbeier.droidvnc_ng.sockets.configSockets.GetIpDevice



class MainActivity : ComponentActivity() {
    @RequiresApi(Build.VERSION_CODES.O)
    @SuppressLint("HardwareIds")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val intent = Intent(this, CommandsRemoteService::class.java)
        ContextCompat.startForegroundService(this, intent)

        setContent {
            //NavHostController()
            val getIpDevice = GetIpDevice()

            Box(modifier = Modifier.fillMaxSize(), Alignment.Center){
                Column {


                    Text("HoLa")
                    LaunchedEffect(true) {
                        try {
                            val text = "Hola, este es un texto de ejemplo para cifrar y luego descifrar."
                            val secretKey = "EstaEsUnaClaveSe"

                            val textoEncriptado = EncryptTextTest(text, secretKey)
                            Log.d("Texto", "clave ajustada: $secretKey")
                            Log.d("Texto","Texto Encriptado $textoEncriptado")
                            val textoDesencriptado =  DecryptTextTest(textoEncriptado, secretKey )
                            Log.d("Texto", "Texto Desencriptado$textoDesencriptado")
                        }catch (e: Exception) {
                            e.printStackTrace()
                            Log.d("Texto", "Error: $e")
                        }

                    }
                }
            }
        }
    }
}