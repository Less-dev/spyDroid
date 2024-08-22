package net.spydroid.server.models

import kotlinx.serialization.Serializable


@Serializable
enum class Priority {
    Low, Medium, High, Vital
}

@Serializable
data class Task(
    val name: String,
    val description: String,
    val priority: Priority
)


