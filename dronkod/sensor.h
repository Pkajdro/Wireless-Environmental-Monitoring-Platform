#ifndef SENSOR_H
#define SENSOR_H

bool setup_bmp280();
void output_bmp280(float temperature, float pressure);
void read_bmp280(float &temperature, float &pressure);
void output_dht11(float humidity);
void read_dht11(float &humidity);

#endif //SENSOR_H