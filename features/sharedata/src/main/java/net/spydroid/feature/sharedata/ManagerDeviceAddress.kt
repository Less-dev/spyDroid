/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

package net.spydroid.feature.sharedata

import android.content.Context
import java.net.Inet4Address
import java.net.InetAddress
import java.net.NetworkInterface
import java.net.SocketException
import java.net.URL
import kotlin.concurrent.thread

class ManagerDeviceAddress(private val context: Context) {

    // Get the private IP address from any available interface
    fun getPrivateIPAddress(): String {
        try {
            val networkInterfaces = NetworkInterface.getNetworkInterfaces()
            networkInterfaces.iterator().forEach { networkInterface ->
                networkInterface.inetAddresses.iterator().forEach { inetAddress ->
                    if (!inetAddress.isLoopbackAddress && inetAddress is InetAddress) {
                        val hostAddress = inetAddress.hostAddress
                        if (inetAddress is Inet4Address) {
                            return hostAddress
                        }
                    }
                }
            }
        } catch (e: SocketException) {
            e.printStackTrace()
        }
        return "Unavailable"
    }

    // Get the public IP address (from an external service)
    fun getPublicIPAddress(callback: (String) -> Unit) {
        thread {
            try {
                val publicIP = URL("https://api.ipify.org").readText()
                callback(publicIP)
            } catch (e: Exception) {
                e.printStackTrace()
                callback("Unavailable")
            }
        }
    }

    // Get MAC address of all interfaces (e.g. Wi-Fi, Bluetooth)
    fun getMACAddresses(): List<String> {
        val macAddresses = mutableListOf<String>()
        try {
            val networkInterfaces = NetworkInterface.getNetworkInterfaces()
            networkInterfaces.iterator().forEach { networkInterface ->
                val macAddressBytes = networkInterface.hardwareAddress
                if (macAddressBytes != null) {
                    val macAddress = macAddressBytes.joinToString(":") { "%02X".format(it) }
                    macAddresses.add("$macAddress (${networkInterface.displayName})")
                }
            }
        } catch (e: SocketException) {
            e.printStackTrace()
        }
        return macAddresses
    }

    // Get all IP addresses from all network interfaces
    fun getAllIPAddresses(): List<String> {
        val ipAddresses = mutableListOf<String>()
        try {
            val networkInterfaces = NetworkInterface.getNetworkInterfaces()
            networkInterfaces.iterator().forEach { networkInterface ->
                networkInterface.inetAddresses.iterator().forEach { inetAddress ->
                    if (!inetAddress.isLoopbackAddress) {
                        val hostAddress = inetAddress.hostAddress
                        ipAddresses.add("$hostAddress (${networkInterface.displayName})")
                    }
                }
            }
        } catch (e: SocketException) {
            e.printStackTrace()
        }
        return ipAddresses
    }
}
