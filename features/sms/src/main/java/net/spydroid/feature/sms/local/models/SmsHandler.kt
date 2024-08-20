package net.spydroid.feature.sms.local.models

data class SmsHandler(
    val uid: String,
    val address: String,
    val body: String,
    val date: String
)