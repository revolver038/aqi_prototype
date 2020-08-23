# aqi_prototype
Simple yet useful AQI prototype with SDS011 + DHT11 + SSH1106 Oled display setted up with Arduino UNO board

With this prototype you will get sensor readings (Humidity, Temperature, PM2.5 and PM10) right away on OLED display in 3 seconds interval. Regarding the values, 
AQI indexes will appear below them.

In oled display indexes are in Azerbaijani. But you can replace them with the help of below table. 


AQI index (PM2.5: between X1 - X2) (PM10: between X1 - X2)

Good(PM2.5: 0-12.0) (PM10: 0-54)
Moderate(PM2.5: 12.1-35.4) (PM10: 55-154)
Unhealthy 
for sensitive 
groups(PM2.5: 35.5-55.4) (PM10: 155-254)
Unhealthy(PM2.5: 55.5-150.4) (PM10: 255-354)
Very Unhealthy(PM2.5: 150.5-250.4) (PM10: 355-424)
Hazardous(PM2.5: 250.5-500.4) (PM10: 425-604)

Further info (Table with descriptions as well) for AQI index: https://www3.epa.gov/airnow/aqi-technical-assistance-document-sept2018.pdf

Tural Alizada (c)
github.com/revolver038
