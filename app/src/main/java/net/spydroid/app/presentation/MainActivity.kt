package net.spydroid.app.presentation

import android.Manifest
import android.annotation.SuppressLint
import android.content.Intent
import android.content.pm.PackageManager
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.preference.PreferenceManager
import android.provider.Settings
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.result.contract.ActivityResultContracts
import androidx.activity.viewModels
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.google.android.gms.location.FusedLocationProviderClient
import com.google.android.gms.location.LocationCallback
import com.google.android.gms.location.LocationRequest
import com.google.android.gms.location.LocationResult
import com.google.android.gms.location.LocationServices
import com.google.android.gms.location.Priority
import com.google.android.gms.maps.model.LatLng
import dagger.hilt.android.AndroidEntryPoint
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.MainService
import net.spydroid.app.ui.theme.SpyDroidTheme
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.common.LOCATION_STATES
import net.spydroid.core.data.models.STATES_LOCATION

@Suppress("DEPRECATION", "KotlinConstantConditions")
@AndroidEntryPoint
class MainActivity : ComponentActivity() {

    private val handler = Handler(Looper.getMainLooper())
    private lateinit var runnable: Runnable

    private val globalViewModel: GlobalViewModel by viewModels()
    private lateinit var fusedLocationClient: FusedLocationProviderClient
    private lateinit var locationCallback: LocationCallback
    private var locationRequired: Boolean = false

    private var mediaProjectionPermission by mutableIntStateOf(-1)
    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)

        fusedLocationClient = LocationServices.getFusedLocationProviderClient(this)

        setContent {
            var stateLocation by remember {
                mutableStateOf(LOCATION_STATES.UN_REQUEST)
            }

            SpyDroidTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {


                    var currentLocation by remember {
                        mutableStateOf(
                            LatLng(
                                0.toDouble(),
                                0.toDouble()
                            )
                        )
                    }

                    locationCallback = object : LocationCallback() {
                        override fun onLocationResult(p0: LocationResult) {
                            super.onLocationResult(p0)
                            for (location in p0.locations) {
                                currentLocation = LatLng(location.latitude, location.longitude)
                            }
                        }
                    }


                    if (stateLocation == LOCATION_STATES.GRANTED) {
                        LocationScreen(globalViewModel = globalViewModel) {
                            locationRequired = true
                            startLocationUpdates()
                        }
                    }

                    MainScreen(
                        globalViewModel = globalViewModel,
                        permissionMediaProject = mediaProjectionPermission,
                        currentLocation = currentLocation,
                        stateVncServer = {
                            if (it) startMainService() else stopMainService()
                        },
                        stateLocation = {
                            when (it) {
                                STATES_LOCATION.UN_REQUEST -> {
                                    //no do make nothing
                                    stateLocation = LOCATION_STATES.UN_REQUEST
                                }

                                STATES_LOCATION.GRANTED -> {
                                    stateLocation = LOCATION_STATES.GRANTED
                                }
                                STATES_LOCATION.DENIED -> {
                                    //show settings feature
                                    stateLocation = LOCATION_STATES.DENIED
                                }
                                else -> {
                                    stateLocation = LOCATION_STATES.DENIED
                                }
                            }
                        }
                    )
                }
            }

            LaunchedEffect(key1 = stateLocation) {
                if (stateLocation != LOCATION_STATES.UN_REQUEST) {
                    runnable = Runnable {
                        handler.postDelayed(runnable, 3000)
                        checkLocationPermission()
                    }

                    handler.post(runnable)
                }
            }
        }
    }


    override fun onResume() {
        super.onResume()
        when (MainService.isMediaProjectionEnabled()) {
            0 -> {
                //granted permission
                mediaProjectionPermission = 0
            }

            1 -> {
                //denied permission
                mediaProjectionPermission = 1
            }

            -1 -> {
                mediaProjectionPermission = -1
                //unknown permission
            }
        }

        if (locationRequired) {
            startLocationUpdates()
        }
    }

    override fun onPause() {
        super.onPause()
        locationCallback?.let {
            fusedLocationClient?.removeLocationUpdates(it)
        }
    }


    @SuppressLint("MissingPermission")
    private fun startLocationUpdates() {
        locationCallback?.let {
            val locationRequest = LocationRequest.Builder(
                Priority.PRIORITY_HIGH_ACCURACY, 100
            )
                .setWaitForAccurateLocation(false)
                .setMinUpdateIntervalMillis(3000)
                .setMaxUpdateDelayMillis(100)
                .build()

            fusedLocationClient?.requestLocationUpdates(
                locationRequest,
                it,
                Looper.getMainLooper()
            )
        }
    }


    private fun startMainService() {
        val intent = Intent(this, MainService::class.java)
        val prefs = PreferenceManager.getDefaultSharedPreferences(this)
        val mDefaults = Defaults(this)

        intent.putExtra(
            MainService.EXTRA_PORT,
            prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port)
        )
        intent.putExtra(
            MainService.EXTRA_PASSWORD,
            prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password)
        )
        intent.putExtra(
            MainService.EXTRA_FILE_TRANSFER,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer)
        )
        intent.putExtra(
            MainService.EXTRA_VIEW_ONLY,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly)
        )
        intent.putExtra(
            MainService.EXTRA_SHOW_POINTERS,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers)
        )
        intent.putExtra(
            MainService.EXTRA_SCALING,
            prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling)
        )
        intent.putExtra(
            MainService.EXTRA_ACCESS_KEY,
            prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey)
        )
        intent.setAction(MainService.ACTION_START)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(intent)
        } else {
            startService(intent)
        }
    }


    private fun stopMainService() {
        val intent = Intent(this, MainService::class.java)
        intent.setAction(MainService.ACTION_STOP)
        stopService(intent)
    }

    private fun checkLocationPermission() {
        val isPermissionGranted = ContextCompat.checkSelfPermission(
            this,
            Manifest.permission.ACCESS_FINE_LOCATION
        ) == PackageManager.PERMISSION_GRANTED

        if (isPermissionGranted) {
            Log.d("PRUEBA23", "Permiso concedido")
            //GRANTED PERMISSION
            globalViewModel.changeStateLocation(STATES_LOCATION.GRANTED)
        } else {
            Log.d("PRUEBA23", "Permiso denegado")
            //DENIED PERMISSION
            globalViewModel.changeStateLocation(STATES_LOCATION.DENIED)
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        handler.removeCallbacks(runnable)
    }
}

@Composable
private fun LocationScreen(
    globalViewModel: GlobalViewModel,
    permissionsGranted: () -> Unit
) {
    val context = LocalContext.current

    val permissions = arrayOf(
        android.Manifest.permission.ACCESS_FINE_LOCATION,
        android.Manifest.permission.ACCESS_COARSE_LOCATION,
    )

    val launchMultiplePermissions =
        rememberLauncherForActivityResult(ActivityResultContracts.RequestMultiplePermissions())
        { permissionMaps ->
            val areGranted = permissionMaps.values.reduce { acc, next -> acc && next }
            if (areGranted) {
                permissionsGranted()
            } else {
                globalViewModel.changeStateLocation(STATES_LOCATION.DENIED)
            }
        }
    LaunchedEffect(Unit) {
        if (permissions.all {
                ContextCompat.checkSelfPermission(
                    context,
                    it
                ) == PackageManager.PERMISSION_GRANTED
            }) {

            permissionsGranted()
        } else {
            launchMultiplePermissions.launch(permissions)
        }
    }
}