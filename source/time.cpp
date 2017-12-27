#include "header.h"
#include <sys/time.h>

enum msec_status {
	InIT,
	CuRRENT,
	DiFF,
	LaST_DiFF,
};

struct timeval myTime;
int cnt[5], msec[5][4], sec[5];

double time_now(int id) {
	gettimeofday(&myTime, NULL);
	if (cnt[id] == 0) msec[id][InIT] = (int)myTime.tv_usec;
	msec[id][CuRRENT] = (int)myTime.tv_usec;
	msec[id][LaST_DiFF] = msec[id][DiFF];
	msec[id][DiFF] = msec[id][CuRRENT] - msec[id][InIT];
	if (msec[id][DiFF] < 0) msec[id][DiFF] = 1000000 - msec[id][DiFF] * -1;
	if (msec[id][LaST_DiFF] > msec[id][DiFF]) sec[id]++;
	cnt[id]++;
	//printf("%04d:%06d\n", sec, msec[id][DiFF]);
	return sec[id]+msec[id][DiFF]/1000000.0;
}

void time_ini() {
	for (int i = 0; i < 5; i++) {
		for (int n = 0; n < 4; n++) {
			msec[i][n] = 0;
		}
		sec[i] = 0;
		cnt[i] = 0;
	}
}