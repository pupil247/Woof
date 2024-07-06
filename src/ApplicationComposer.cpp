#include "ApplicationComposer.h"

esp_err_t ApplicationComposer::init(){
    M5.begin();
    camHandler.start();
    wifiHandler.start();
    Serial.begin(115200);
    return ESP_OK;
}

esp_err_t ApplicationComposer::loop(){
    //main task loop
    M5.IMU.Init(); 
    float accX = 0.0F;  // Define variables for storing inertial sensor data
    float accY = 0.0F;  // 定义存储惯性传感器相关数据的相关变量
    float accZ = 0.0F;

    float gyroX = 0.0F;
    float gyroY = 0.0F;
    float gyroZ = 0.0F;

    float pitch = 0.0F;
    float roll  = 0.0F;
    float yaw   = 0.0F;

    float temp = 0.0F;
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    
    M5.IMU.getAccelData(
        &accX, &accY,
        &accZ);  // Stores the triaxial accelerometer.  存储三轴加速度计数据
    M5.IMU.getAhrsData(
        &pitch, &roll,
        &yaw);  // Stores the inertial sensor attitude.  存储惯性传感器的姿态
    
    M5.IMU.getTempData(&temp);
     M5.Lcd.setCursor(
        0, 20);  // Move the cursor position to (x,y).  移动光标位置到(x,y)处
    M5.Lcd.printf("gyroX,  gyroY, gyroZ");  // Screen printingformatted string.
                                            // 输出格式化字符串
    M5.Lcd.setCursor(0, 42);
    M5.Lcd.printf("%6.2f %6.2f%6.2f o/s", gyroX, gyroY, gyroZ);

    // Accelerometer output is related
    // 加速度计输出相关
    M5.Lcd.setCursor(0, 70);
    M5.Lcd.printf("accX,   accY,  accZ");
    M5.Lcd.setCursor(0, 92);
    M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);

    // Pose output is related
    // 姿态输出相关
    M5.Lcd.setCursor(0, 120);
    M5.Lcd.printf("pitch,  roll,  yaw");
    M5.Lcd.setCursor(0, 142);
    M5.Lcd.printf("%5.2f  %5.2f  %5.2f deg", pitch, roll, yaw);

    // Inertial sensor temperature output related
    // 惯性传感器温度输出相关
    M5.Lcd.setCursor(0, 175);
    M5.Lcd.printf("Temperature : %.2f C", temp);
    M5.update();
    if (M5.BtnA.wasReleased()) {  
        // Implement your shutdown logic here
        M5.shutdown();  // Power off M5Stack
    }
    return ESP_OK;
}

esp_err_t ApplicationComposer::hardwareSetup(){
    pinMode(LED_ONBOARD, OUTPUT);
    return ESP_OK;
}

ApplicationComposer * ApplicationComposer::my_app = NULL;
