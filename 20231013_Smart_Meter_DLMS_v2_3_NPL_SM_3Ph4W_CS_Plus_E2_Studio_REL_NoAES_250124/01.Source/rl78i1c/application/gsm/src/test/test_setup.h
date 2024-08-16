#ifndef __TEST_SETUP_H__
#define __TEST_SETUP_H__

typedef void (*TestHandler_t)(void);

TestHandler_t* get_test_set(void);

#endif