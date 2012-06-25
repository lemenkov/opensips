#include "timer.h"
#include "../../dprint.h"
#include "../../sr_module.h"

#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#define MAX_TIMEOUT_S  10
#define MIN_TIMEOUT_MCS 100000

/* Default is 3.0 second */
struct itimerval request_tm = {{0,0}, {3,0}};
// unsigned request_tm;

/* Default is 0.2 second */
struct itimerval restore_tm = {{0,0}, {0,200000}};

struct itimerval stop_tm = {{0,0}, {0,0}};

/* Simple error handling functions */

#define handle_error_en(en, msg) \
	do { LM_ERR(msg": %s\n", strerror(en)); return 1; } while (0)
	
static ora_con_t *g_con;

static int set_tv(unsigned type, const char* val, struct timeval* tv)
{
	char *eptr;
	struct itimerval tt;
	unsigned long s, ms;
	double dv;
	
	if (type != STR_PARAM) {
		LM_ERR("type of parameter is no STR\n");
		return -1;
	}
	
	if (!val || !*val) {
		LM_ERR("empty parameter\n");
		return -1;
	}
	
	errno = 0;
	dv = strtod(val, &eptr);
	
	if (*eptr) {
		LM_ERR("invalid parameter string\n");
		return -2;
	}
	
	if (   errno
		|| dv > (double)MAX_TIMEOUT_S
		|| (dv < ((double)MIN_TIMEOUT_MCS)/100000))
	{
		LM_ERR("value must be between 0.%.6u and %u.0\n",
		MIN_TIMEOUT_MCS, MAX_TIMEOUT_S);
		return -3;
	}
	
	s = (unsigned)dv;
	dv -= (double)s;
	ms = (unsigned)(dv * 1000000);
	tv->tv_sec = (time_t)s;
	tv->tv_usec = (suseconds_t)ms;
	return 0;
}


/*
	* set operation timeout
	*/
int set_timeout(unsigned type, const char* val)
{
	return set_tv(type, val, &request_tm.it_value);
}


/*
	* set (re)connect timeout
	*/
int set_reconnect(unsigned type, const char* val)
{
	return set_tv(type, val, &restore_tm.it_value);
}

void ora_alarm_handle(int sig) {
	LM_INFO("ora_alarm_handle\n");
	sword status;
	status = OCIBreak(g_con->svchp, g_con->errhp);
	if (status != OCI_SUCCESS) {
		LM_ERR("OCIBreak: %s\n", db_oracle_error(g_con, status));
	}
}

int init_ora_timer(ora_con_t* con) {
	g_con = con;
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ora_alarm_handle;
	if (sigaction(SIGALRM, &sa, NULL) < -1)
		handle_error_en(errno, "sigaction");
	
	return 0;
}

int destroy_ora_timer()
{
	timer_stop();
}

void request_timer()
{
	if (setitimer(ITIMER_REAL, &request_tm, NULL) < 0)
		LM_ERR("setitimer: %s\n", strerror(errno));
}

void restore_timer()
{
	if (setitimer(ITIMER_REAL, &restore_tm, NULL) < 0)
		LM_ERR("setitimer: %s\n", strerror(errno));
}

void timer_stop()
{
	if (setitimer(ITIMER_REAL, &stop_tm, NULL) < 0)
		LM_ERR("setitimer: %s\n", strerror(errno));
}
	