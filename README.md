# aqi_prototype
Simple yet useful AQI prototype with SDS011 + DHT11 + SSH1106 Oled display setted up with Arduino UNO board

With this prototype you will get sensor readings (Humidity, Temperature, PM2.5 and PM10) right away on OLED display in 3 seconds interval. Regarding the values, 
AQI indexes will appear below them.

In oled display indexes are in Azerbaijani. But you can replace them with the help of below table. 


AQI index--------------PM2.5----------PM10

Good-------------------0-12.0---------0-54
Moderate--------------12.1-35.4------55-154
Unhealthy 
for sensitive 
groups---------------35.5-55.4-------155-254
Unhealthy-----------55.5-150.4-------255-354
Very Unhealthy-----150.5-250.4-------355-424
Hazardous----------250.5-500.4-------425-604

Further for AQI index: https://www3.epa.gov/airnow/aqi-technical-assistance-document-sept2018.pdf

Tural Alizada (c)
github.com/revolver038
