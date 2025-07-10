#pragma once

int random_int(int end, int start = 0) {
    return (rand() % (end - start)) + start;
}

float random_float(float end, float start = 0) {
    int end_int = (end - start) * 10000;
    return (rand() % end_int) * 0.0001 + start;
}