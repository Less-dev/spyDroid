pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}

include(":app")
include(":core-ui")
include(":feature-vnc")
include(":feature-templates")

rootProject.name = "spyDroid"
