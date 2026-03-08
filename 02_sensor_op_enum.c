#include <stdio.h>

#define INVALID_SENSOR_OP_RESULT ((int)((unsigned long)(~0) >> 1))

typedef enum {
	SENSOR_OP_INIT,
	SENSOR_OP_READ,
	SENSOR_OP_RESET,

	COUNT_SENSOR_OPS,
} SensorOp;

typedef int SensorOpResult;

typedef struct Sensor Sensor;

typedef SensorOpResult SensorHandler(Sensor *s, SensorOp op);

struct Sensor {
	const char *name;
	SensorHandler *handler;
};

void run_sensor_logic(Sensor *s);
SensorOpResult temp_sensor_handler(Sensor *s, SensorOp op);
SensorOpResult accel_sensor_handler(Sensor *s, SensorOp op);

int main(void) {
	Sensor temp  = {"Temp(LM75)", temp_sensor_handler};
	Sensor accel = {"Accel(ADXL)", accel_sensor_handler};

	Sensor *sensors[] = { &temp, &accel };

	for (int i = 0; i < 2; ++i) {
		run_sensor_logic(sensors[i]);
	}
}

void run_sensor_logic(Sensor *s) {
	printf("Configuring %s\n", s->name);
	s->handler(s, SENSOR_OP_INIT);
	printf("Read: %d\n", s->handler(s, SENSOR_OP_READ));
	s->handler(s, SENSOR_OP_INIT);
}

SensorOpResult temp_sensor_handler(Sensor *s, SensorOp op) {
	switch (op) {
		case SENSOR_OP_INIT:
			printf("LM75: Init\n");
			return 0;
		case SENSOR_OP_READ:
			return 25;
		case SENSOR_OP_RESET:
			printf("LM75: Reset\n");
			return 0;
		default:
			break;
	}

	return INVALID_SENSOR_OP_RESULT;
}

SensorOpResult accel_sensor_handler(Sensor *s, SensorOp op) {
	switch (op) {
		case SENSOR_OP_INIT:
			printf("ADXL: Init\n");
			return 0;
		case SENSOR_OP_READ:
			return 10;
		case SENSOR_OP_RESET:
			printf("ADXL: Reset\n");
			return 0;
		default:
			break;
	}

	return INVALID_SENSOR_OP_RESULT;
}
