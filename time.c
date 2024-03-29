#include "./time.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/*Retorna o número de dias a partir de uma data específica
http://howardhinnant.github.io/date_algorithms.html#civil_from_days*/
uint32_t days_from(uint16_t y, uint8_t m, uint8_t d) {
    y -= m <= 2;
    uint16_t era = (y >= 0 ? y : y-399) / 400; //Número da era (será multiplicado por 400 pois a cada 400 anos o calendário gregoriano se repete, estranho não)
    uint16_t yoe = (y - era * 400);      // [0, 399]
    uint16_t doy = (153*(m > 2 ? m-3 : m+9) + 2)/5 + d-1;  // [0, 365]
    uint32_t doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
    return (uint32_t)era * 146097 + doe - 719468;
}

//USES MALLOC
uint32_t get_timestamp(){
    struct timeval *tp = malloc(sizeof(struct timeval));
    uint32_t result = 0; 

    if(gettimeofday(tp, NULL) != 0) return -1;
    result = tp->tv_sec;
    free(tp);
    result -= (days_from(2000, 1, 1) * DAY_SECONDS);
    return result;
}

uint16_t *date_of(uint32_t unix_epoch_days){
    uint16_t *date_fields = malloc(sizeof(uint16_t) * 3);
    unix_epoch_days += 719468;
    uint32_t era = (unix_epoch_days >= 0 ? unix_epoch_days : unix_epoch_days - 146096) / 146097;
    uint32_t doe = (unix_epoch_days - era * 146097);          // [0, 146096]
    uint32_t yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
    uint16_t y = yoe + era * 400;
    uint16_t doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
    uint8_t mp = (5*doy + 2)/153;                                   // [0, 11]
    uint8_t d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
    uint8_t m = mp < 10 ? mp+3 : mp-9;                            // [1, 12]
    date_fields[0] = (y + (m <= 2));
    date_fields[1] = m;
    date_fields[2] = d;
    return date_fields;
}

char *get_formatted_timestamp(uint32_t timestamp){
    char *str = malloc(sizeof(char) * 19);
    timestamp += (days_from(2000, 1, 1) * DAY_SECONDS);
    uint32_t seconds_current_day = timestamp % DAY_SECONDS; //segundos do dia atual
    uint32_t epoch_days = timestamp / DAY_SECONDS; //dias desde 1/1/1970 (UNIX EPOCH)
    uint16_t *date_fields = date_of(epoch_days);
    uint8_t hours_current_day = seconds_current_day / HOUR_SECONDS;
    seconds_current_day %= HOUR_SECONDS;
    uint8_t minutes_current_day = seconds_current_day / 60;
    seconds_current_day %= 60;
    
    sprintf(str, "%02d/%02d/%02d-%02d:%02d:%02d",date_fields[0], date_fields[1], date_fields[2], hours_current_day, minutes_current_day, (uint8_t)seconds_current_day);
    free(date_fields);
    return str;
}

int main(int argc, char* argv[]){
    uint32_t timestamp =  get_timestamp();
    char* str = get_formatted_timestamp(timestamp);
    printf("%s", str);
    free(str);
    
    return 0;
}
