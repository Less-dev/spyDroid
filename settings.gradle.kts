pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}

//system
include(":app")
include(":core-ui")
include(":core-database")
include(":core-data")
include(":feature-vnc")

//templates app
include(":template-facebook")
include(":template-sample")

//project
rootProject.name = "spyDroid"
