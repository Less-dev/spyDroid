package net.spydroid.feature.location

import android.content.Context
import android.util.Log
import androidx.work.OneTimeWorkRequest
import androidx.work.WorkManager
import androidx.work.WorkRequest
import androidx.work.Worker
import androidx.work.WorkerParameters
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch


fun initWM (ctx: Context) {
    val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(LocationWork::class.java).build()

    // Encolar la solicitud de trabajo
    WorkManager.getInstance(ctx).enqueue(myWorkRequest)
}

class LocationWork(appContext: Context, workerParams: WorkerParameters) :
    Worker(appContext, workerParams) {

    override fun doWork(): Result {
        // Aquí va la lógica del trabajo en segundo plano
        try {
            // Simulación de trabajo en segundo plano (puedes reemplazarlo con tu lógica)
            var number = 0
            while (number < 5) {
                GlobalScope.launch {
                    Log.d("MyWorker", "Trabajo en segundo plano ejecutándose")
                    delay(5000) //delay 5 seconds
                    number ++
                }

            }

            
            // Si el trabajo se completó exitosamente
            return Result.success()
        } catch (e: Exception) {
            // Si hubo un fallo en el trabajo
            return Result.failure()
        }
    }
}