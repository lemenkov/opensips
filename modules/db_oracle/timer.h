#ifndef ORA_TIMER_H
#define ORA_TIMER_H

#include "ora_con.h"

/*
 * parse timeout value for operation in syntax: nnn.mmm (sec/ms)
 */
int set_timeout(unsigned type, const char* val);

/*
 * parse timeout value for reconnect in syntax: nnn.mmm (sec/ms)
 */
int set_reconnect(unsigned type, const char* val);

int init_ora_timer(ora_con_t* con);
int destroy_ora_timer();

void request_timer();
void restore_timer();
void timer_stop();
#endif // ORA_TIMER_H