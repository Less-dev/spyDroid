package net.spydroid.common.remote.data.models

data class InfoDevices(
    val id: Int,
    val alias: String,
    val ip_address_public: String,
    val ip_address_private: String,
    val location: String
)
