#include <stdio.h>

#define INVALID_TEMP ((int)((unsigned long)(~0) >> 1))

typedef enum {
	SENSOR_TYPE_TEMP,
	SENSOR_TYPE_ACCEL,

	COUNT_SENSOR_TYPE,
} SensorType;

typedef struct {
	const char *name;
	SensorType type;
} Sensor;

void run_sensor_logic(Sensor *s);
void sensor_init(Sensor *s);
int sensor_read(Sensor *s);
void sensor_reset(Sensor *s);

int main(void) {
	Sensor temp  = {"Temp(LM75)", SENSOR_TYPE_TEMP};
	Sensor accel = {"Accel(ADXL)", SENSOR_TYPE_ACCEL};

	Sensor *sensors[] = { &temp, &accel };

	for (int i = 0; i < 2; ++i) {
		run_sensor_logic(sensors[i]);
	}
}

static inline void temp_sensor_init(Sensor *s);
static inline int temp_sensor_read(Sensor *s);
static inline void temp_sensor_reset(Sensor *s);
static inline void accel_sensor_init(Sensor *s);
static inline int accel_sensor_read(Sensor *s);
static inline void accel_sensor_reset(Sensor *s);

void run_sensor_logic(Sensor *s) {
	printf("Configuring %s\n", s->name);
	sensor_init(s);
	printf("Read: %d\n", sensor_read(s));
	sensor_reset(s);
}

void sensor_init(Sensor *s) {
	switch (s->type) {
		case SENSOR_TYPE_TEMP:
			temp_sensor_init(s);
			break;
		case SENSOR_TYPE_ACCEL:
			accel_sensor_init(s);
			break;
		default:
			break;
	}
}

int sensor_read(Sensor *s) {
	switch (s->type) {
		case SENSOR_TYPE_TEMP:
			return temp_sensor_read(s);
		case SENSOR_TYPE_ACCEL:
			return accel_sensor_read(s);
		default:
			break;
	}

	return INVALID_TEMP;
}

void sensor_reset(Sensor *s) {
	switch (s->type) {
		case SENSOR_TYPE_TEMP:
			temp_sensor_reset(s);
			break;
		case SENSOR_TYPE_ACCEL:
			accel_sensor_reset(s);
			break;
		default:
			break;
	}
}

static inline void temp_sensor_init(Sensor *s) {
	printf("LM75: Init\n");
}

static inline int temp_sensor_read(Sensor *s) {
	return 25;
}

static inline void temp_sensor_reset(Sensor *s) {
	printf("LM75: Reset\n");
}

static inline void accel_sensor_init(Sensor *s) {
	printf("ADXL: Init\n");
}

static inline int accel_sensor_read(Sensor *s) {
	return 10;
}

static inline void accel_sensor_reset(Sensor *s) {
	printf("ADXL: Reset\n");
}
