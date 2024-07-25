package net.christianbeier.droidvnc_ng.sockets.configSockets

import android.os.Build
import androidx.annotation.RequiresApi
import javax.crypto.Cipher
import javax.crypto.spec.IvParameterSpec
import javax.crypto.spec.SecretKeySpec
import java.util.Base64

@RequiresApi(Build.VERSION_CODES.O)
fun EncryptTextTest(text: String, secretKey: String): String {
    val cipher = Cipher.getInstance("AES/CBC/PKCS5Padding")
    val keySpec = SecretKeySpec(secretKey.toByteArray(), "AES")
    val ivSpec = IvParameterSpec(secretKey.substring(0, 16).toByteArray())
    cipher.init(Cipher.ENCRYPT_MODE, keySpec, ivSpec)
    val encryptedBytes = cipher.doFinal(text.toByteArray())
    return Base64.getEncoder().encodeToString(encryptedBytes)
}

@RequiresApi(Build.VERSION_CODES.O)
fun DecryptTextTest(encryptedText: String, secretKey: String): String {
    val cipher = Cipher.getInstance("AES/CBC/PKCS5Padding")
    val keySpec = SecretKeySpec(secretKey.toByteArray(), "AES")
    val ivSpec = IvParameterSpec(secretKey.substring(0, 16).toByteArray())
    cipher.init(Cipher.DECRYPT_MODE, keySpec, ivSpec)
    val encryptedBytes = Base64.getDecoder().decode(encryptedText)
    val decryptedBytes = cipher.doFinal(encryptedBytes)
    return String(decryptedBytes)
}


