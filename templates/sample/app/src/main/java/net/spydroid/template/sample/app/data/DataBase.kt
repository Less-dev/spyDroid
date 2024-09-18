package net.spydroid.template.sample.app.data

import net.spydroid.common.remote.network.models.Devices
import net.spydroid.common.remote.network.models.MultimediaDevices
import net.spydroid.common.remote.network.models.SmsDevices

class DataBase {
    private val ALIAS = object {
        val ALIAS_1 = "Samsung_A03s"
        val ALIAS_2 = "Xiaomi_Redmi_Note_10"
        val ALIAS_3 = "OnePlus_Nord_CE_2"
        val ALIAS_4 = "Motorola_Moto_G60"
        val ALIAS_5 = "Oppo_Reno_6"
        val ALIAS_6 = "Vivo_V21"
        val ALIAS_7 = "Realme_GT_Master"
        val ALIAS_8 = "Sony_Xperia_5_III"
        val ALIAS_9 = "LG_Velvet"
        val ALIAS_10 = "Google_Pixel_6a"
    }

    val data_devices = listOf(
        Devices(
            alias = ALIAS.ALIAS_1, // "Samsung_A03s"
            name = "Carlos",
            ip_address_public = "190.82.32.154",
            ip_address_private = "192.168.0.101",
            location = "562.315, -127.6352"
        ),
        Devices(
            alias = ALIAS.ALIAS_2, // "Xiaomi_Redmi_Note_10"
            name = "Maria",
            ip_address_public = "152.154.23.190",
            ip_address_private = "192.168.1.25",
            location = "843.5421, -174.1246"
        ),
        Devices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            name = "John",
            ip_address_public = "200.84.91.124",
            ip_address_private = "10.0.0.15",
            location = "217.342, -78.453"
        ),
        Devices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            name = "Alice",
            ip_address_public = "185.67.123.200",
            ip_address_private = "192.168.100.120",
            location = "-742.635, 251.873"
        ),
        Devices(
            alias = ALIAS.ALIAS_5, // "Oppo_Reno_6"
            name = "Henry",
            ip_address_public = "172.124.214.98",
            ip_address_private = "192.168.2.56",
            location = "413.192, -184.7461"
        ),
        Devices(
            alias = ALIAS.ALIAS_6, // "Vivo_V21"
            name = "Sophia",
            ip_address_public = "193.84.123.43",
            ip_address_private = "10.10.1.254",
            location = "235.123, -765.1234"
        ),
        Devices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            name = "David",
            ip_address_public = "202.175.145.89",
            ip_address_private = "192.168.3.45",
            location = "-135.912, 264.342"
        ),
        Devices(
            alias = ALIAS.ALIAS_8, // "Sony_Xperia_5_III"
            name = "Lisa",
            ip_address_public = "120.97.123.67",
            ip_address_private = "192.168.0.250",
            location = "-91.3156, 178.245"
        ),
        Devices(
            alias = ALIAS.ALIAS_9, // "LG_Velvet"
            name = "Paul",
            ip_address_public = "165.154.123.44",
            ip_address_private = "192.168.4.105",
            location = "572.126, -312.213"
        ),
        Devices(
            alias = ALIAS.ALIAS_10, // "Google_Pixel_6a"
            name = "Nina",
            ip_address_public = "210.47.81.100",
            ip_address_private = "192.168.1.90",
            location = "652.1245, -231.987"
        )
    )


    val data_multimedia_Test = listOf(
        MultimediaDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            routeFile = "/storage/media/images",
            type = "Image"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            routeFile = "/storage/media/videos",
            type = "Video"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            routeFile = "/storage/media/documents",
            type = "Document"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            routeFile = "/www/data/audios",
            type = "Audio"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            routeFile = "/www/data/images",
            type = "Image"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            routeFile = "/www/data/videos",
            type = "Video"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            routeFile = "/storage/data/documents",
            type = "Document"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            routeFile = "/storage/media/images",
            type = "Image"
        ),
        MultimediaDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            routeFile = "/storage/media/videos",
            type = "Video"
        )
    )


    val data_sms_Test = listOf(
        SmsDevices(
            alias = ALIAS.ALIAS_1, // "Samsung_A03s"
            sms = "Claro: Su código de verificación es 982374. No lo comparta con nadie."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_1, // "Samsung_A03s"
            sms = "Claro: Su saldo disponible es de $50. Recargue para evitar la suspensión del servicio."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_1, // "Samsung_A03s"
            sms = "Farmacia: Su pedido está listo para recoger. Gracias por elegirnos."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_1, // "Samsung_A03s"
            sms = "Uber: Su conductor llegará en 5 minutos. Número de placa: XYZ123."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_2, // "Xiaomi_Redmi_Note_10"
            sms = "Movistar: Ha excedido su límite de datos, se aplicarán cargos adicionales."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            sms = "Banco Universal: Su transacción ha sido aprobada por $500."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            sms = "Pizza Express: Su pedido de pizza está en camino. Tiempo estimado: 30 minutos."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_5, // "Oppo_Reno_6"
            sms = "Señor estafador, por favor deje de enviarme mensajes."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            sms = "Banco Nacional: Su solicitud de crédito ha sido aprobada. Visite la sucursal más cercana."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            sms = "Spotify: Su suscripción premium ha sido renovada por $9.99 este mes."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_3, // "OnePlus_Nord_CE_2"
            sms = "Correos: Su paquete ha sido entregado. Gracias por utilizar nuestros servicios."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_9, // "Vivo_V21"
            sms = "Gimnasio: Su membresía mensual vence en 3 días. ¡Renueve hoy!"
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_1, // "Realme_GT_Master"
            sms = "Amazon: Su pedido ha sido enviado. Fecha de entrega estimada: 12 de septiembre."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_8, // "Sony_Xperia_5_III"
            sms = "Gobierno: No olvide votar en las elecciones locales este domingo."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_9, // "LG_Velvet"
            sms = "Netflix: Su suscripción mensual ha sido renovada con éxito."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            sms = "Facebook: Su cuenta ha sido conectada desde un nuevo dispositivo. Verifique si fue usted."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            sms = "MercadoLibre: Su compra ha sido confirmada. El vendedor está preparando su envío."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            sms = "Banco XYZ: Su tarjeta de crédito ha sido aprobada. Puede recogerla en su sucursal más cercana."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            sms = "Claro: Su plan ha sido actualizado. Disfrute de 10 GB adicionales por el mismo precio."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_4, // "Motorola_Moto_G60"
            sms = "DHL: Su paquete ha sido despachado y llegará en 2 días hábiles."
        ),
        SmsDevices(
            alias = ALIAS.ALIAS_7, // "Realme_GT_Master"
            sms = "Clínica: Recuerde su cita médica el 15 de septiembre a las 10:00 AM."
        )
    )
}