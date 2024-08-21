package net.spydroid.template.sample.app.components

import android.media.MediaPlayer
import android.net.Uri
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext

@Composable
fun AudioPlayerScreen() {
    val context = LocalContext.current
    var mediaPlayer by remember { mutableStateOf<MediaPlayer?>(null) }
    var isPlaying by remember { mutableStateOf(false) }
    
    // Aquí colocas tu URI de audio
    val audioUri = Uri.parse("content://media/external/audio/media/1000000104")

    Column {
        Button(
            onClick = {
                if (mediaPlayer == null) {
                    mediaPlayer = MediaPlayer.create(context, audioUri)
                    mediaPlayer?.setOnCompletionListener {
                        isPlaying = false
                    }
                }
                mediaPlayer?.start()
                isPlaying = true
            },
            enabled = !isPlaying,
            modifier = Modifier.fillMaxWidth()
        ) {
            Text("Play")
        }
        
        Button(
            onClick = {
                mediaPlayer?.pause()
                isPlaying = false
            },
            enabled = isPlaying,
            modifier = Modifier.fillMaxWidth()
        ) {
            Text("Pause")
        }
        
        Button(
            onClick = {
                mediaPlayer?.stop()
                mediaPlayer?.reset()
                mediaPlayer?.release()
                mediaPlayer = null
                isPlaying = false
            },
            enabled = isPlaying,
            modifier = Modifier.fillMaxWidth()
        ) {
            Text("Stop")
        }
    }
}