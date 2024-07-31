Proyecto de Medición de Pulsaciones con Arduino
Descripción
Este proyecto utiliza una placa Arduino para medir las pulsaciones cardíacas. Se emplea un sensor de pulso que detecta la variación de la luz al atravesar el dedo, permitiendo calcular la frecuencia cardíaca en tiempo real. La información se muestra en una pantalla LCD conectada al Arduino.

Componentes
Arduino (cualquier modelo compatible)
Sensor de pulso (e.g., MAX30100, MAX30102, etc.)
Pantalla LCD (e.g., 16x2 o 20x4 con módulo I2C)
Resistencias y cables (según sea necesario)
Fuente de alimentación (batería o adaptador)
Instrucciones de Instalación
Montaje del Hardware

Conecta el sensor de pulso al Arduino siguiendo el diagrama de conexión específico para tu modelo de sensor.
Conecta la pantalla LCD al Arduino usando un módulo I2C para simplificar el cableado.
Asegúrate de que todas las conexiones sean firmes y correctas.
Configuración del Software

Descarga e instala el IDE de Arduino desde arduino.cc.
Instala las bibliotecas necesarias:
Wire (para comunicación I2C)
LiquidCrystal_I2C (para controlar la pantalla LCD)
PulseSensor o cualquier biblioteca específica para tu sensor de pulso.
Código de la Aplicación

Clona o descarga el código fuente de este repositorio.
Abre el archivo .ino en el IDE de Arduino.
Verifica y carga el código en tu placa Arduino.
Uso
Coloca tu dedo sobre el sensor de pulso.
Observa la pantalla LCD para ver la frecuencia cardíaca en pulsaciones por minuto (BPM).
Asegúrate de que el sensor esté bien colocado y que no haya movimientos bruscos que puedan afectar la precisión de la medición.
Personalización
Ajuste de Sensibilidad: Puedes ajustar la sensibilidad del sensor cambiando los parámetros en el código.
Salida de Datos: Modifica el código para enviar datos a una computadora o dispositivo móvil para un análisis más detallado.
Contribuciones
Si deseas contribuir a este proyecto, siéntete libre de hacer un fork y enviar un pull request. ¡Apreciamos cualquier mejora o sugerencia!

Licencia
Este proyecto está licenciado bajo la MIT License. Puedes usarlo, modificarlo y distribuirlo libremente con atribución.

Contacto
Para preguntas o comentarios, puedes contactar al desarrollador principal:

Nombre: Uriel Hernández Carrera
Email: uriel100.chdz@gmail.com
