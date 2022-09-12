void read_sensor(){
  static long last_read_time;

  if(millis() - last_read_time > SENSOR_READ_PERIOD){
    last_read_time = millis();

    float humidity = sensor.readHumidity();
    float temperature = sensor.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("[DHT] reading error");
      return;
    }

    Serial.print("[DHT] reading successsful: ");
    Serial.print(temperature);
    Serial.print(" C, ");
    Serial.print(humidity);
    Serial.println(" %");


    StaticJsonDocument<200> outbound_JSON_message;
    outbound_JSON_message["temperature"] = temperature;
    outbound_JSON_message["humidity"] = humidity;

    // Serialize JSON into a char array
    char JSONmessageBuffer[200];
    serializeJson(outbound_JSON_message, JSONmessageBuffer, sizeof(JSONmessageBuffer));

    // Send the char array with MQTT
    Serial.println(F("[MQTT] publish of sensor data"));
    String topic = iot_kernel.mqtt_base_topic + "/data";
    iot_kernel.mqtt.publish(topic.c_str(), JSONmessageBuffer, MQTT_RETAIN);
  }
}
