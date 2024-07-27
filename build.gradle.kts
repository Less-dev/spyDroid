buildscript {
    repositories {
        google()
        mavenCentral()
        maven (url = "https://jitpack.io" )
    }
    dependencies {
        classpath(libs.gradle)
        classpath(libs.kotlin.gradle.plugin.v190)
    }
}

allprojects {
    repositories {
        google()
        mavenCentral()
        maven (url = "https://jitpack.io" )
    }
}

plugins {
    alias(libs.plugins.android.application) apply false
    alias(libs.plugins.android.library) apply false
    alias(libs.plugins.kotlin.android) apply false
    alias(libs.plugins.kotlin.serialization) apply false
}


tasks.register("clean", Delete::class) {
    delete(rootProject.buildDir)
}
