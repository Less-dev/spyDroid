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

package net.spydroid.feature.contacts

import android.content.Context
import android.util.Log
import androidx.work.Worker
import androidx.work.WorkerParameters
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch

class ContactsWork(appContext: Context, workerParams: WorkerParameters)  :
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