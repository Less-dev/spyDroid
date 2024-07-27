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

tasks.register("clean", Delete::class) {
    delete(rootProject.buildDir)
}
