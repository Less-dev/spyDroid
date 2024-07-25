package net.christianbeier.droidvnc_ng.sockets.configSockets


import android.util.Log
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withContext
import okhttp3.OkHttpClient
import okhttp3.Request
import java.net.Inet4Address
import java.net.InetAddress
import java.net.NetworkInterface
import java.util.*

fun GetIpDevice(): MutableList<String> {
    val listaMutable = mutableListOf<String>()
    runBlocking {
        val ipPublica = getPublicIP()
        listaMutable.add(ipPublica)
        //Log.d("direccion", "Dirección ip pública: $ipPublica")

    }
    val ipPrivada = obtenerDireccionIPPrivada()?.let { it }
    //Log.d("direccion", "Dirección ip privada: $ipPrivada")
    listaMutable.add(ipPrivada.toString())
    return listaMutable
}

suspend fun getPublicIP(): String {
    val client = OkHttpClient()
    val request = Request.Builder()
        .url("https://api.ipify.org")
        .build()

    return withContext(Dispatchers.IO) {
        val response = client.newCall(request).execute()
        if (response.isSuccessful) {
            response.body?.string() ?: ""
        } else {
            ""
        }
    }
}

fun obtenerDireccionIPPrivada(): String? {
    return try {
        val interfaces: Enumeration<NetworkInterface> = NetworkInterface.getNetworkInterfaces()
        while (interfaces.hasMoreElements()) {
            val iface: NetworkInterface = interfaces.nextElement()
            val addresses: Enumeration<InetAddress> = iface.inetAddresses
            while (addresses.hasMoreElements()) {
                val addr: InetAddress = addresses.nextElement()
                // Filtra las direcciones IPv4 privadas
                if (!addr.isLoopbackAddress && !addr.isLinkLocalAddress && addr.isSiteLocalAddress) {
                    return addr.hostAddress
                }
            }
        }
        null
    } catch (e: Exception) {
        e.printStackTrace()
        null
    }
}
