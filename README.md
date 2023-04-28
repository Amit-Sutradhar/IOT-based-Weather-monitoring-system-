# IOT-based-Weather-monitoring-system🌦️
in this project we will learn  how to make IOT based weather monitoring system

In this project we will use verious type of sensors like 
- DHT11 to measure humidity 
- MQ135 to measure Air_Quality 
- BMP180 to measure altitude/pressure/temprature 

and we will use Thingspeak colude to upload the data on colude, and we also use one oled display to see the data ...


# ------CUNNECTION---------

-     esp8266.                  OLED                   BMP180                MQ135                DHT11
-     5V                       5V/3.5V                   3.5V                  5V                5V/3.5V   
-     SCL(D1)                    SCL                      SCL                   -                   -
-     SDA(D2)                    SDA                      SDA                   -                   -
-     DHT11                       -                        -                    -                D4(GPIO2)
-     MQ135                       -                        -                    A0                   -
                                                               
