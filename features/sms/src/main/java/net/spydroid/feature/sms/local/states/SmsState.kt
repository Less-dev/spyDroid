package net.spydroid.feature.sms.local.states

import net.spydroid.feature.sms.local.models.SmsHandler


sealed interface SmsState {
    data object Loading : SmsState
    data class Error(val throwable: Throwable) : SmsState
    data class Success(val data: List<SmsHandler>) : SmsState
}