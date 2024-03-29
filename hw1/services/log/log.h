//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_LOG_H
#define EMBEDED_LOG_H

#define LOG_LVL_TRACE   50
#define LOG_LVL_DEBUG   40
#define LOG_LVL_INFO    30
#define LOG_LVL_WARNING 20
#define LOG_LVL_ERROR   10
#define LOG_LVL_FATAL   0


#define LOG_IS_TRACE    (LOGgetLevel() >= LOG_LVL_TRACE)
#define LOG_IS_DEBUG    (LOGgetLevel() >= LOG_LVL_DEBUG)
#define LOG_IS_INFO     (LOGgetLevel() >= LOG_LVL_INFO)
#define LOG_IS_WARNING  (LOGgetLevel() >= LOG_LVL_WARNING)
#define LOG_IS_ERROR    (LOGgetLevel() >= LOG_LVL_ERROR)
#define LOG_IS_FATAL    (LOGgetLevel() >= LOG_LVL_FATAL)

int LOGlogging(char log_type, const char *src_file, const char *func, int line_no, const char *fmt, ...);
int LOGsetLevel(int log_lvl);
int LOGgetLevel(void);

#define LOG_CALL(func)\
	LOG_TRACE("%s #### starting...", #func);\
	func;\
	LOG_TRACE("%s #### end.", #func)


/**
* Trace Log macro
*/
#define LOG_TRACE(...) \
    do { \
        if(LOG_IS_TRACE) { \
            LOGlogging('T', __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } \
    } while(0)

/**
* debug Log macro
*/
#define LOG_DEBUG(...) \
    do { \
        if(LOG_IS_DEBUG) { \
            LOGlogging('D', __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } \
    } while(0)

/**
* info Log macro
*/
#define LOG_INFO(...) \
    do { \
        if(LOG_IS_INFO) { \
            LOGlogging('I', __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } \
    } while(0)

/**
* warning Log macro
*/
#define LOG_WARNING(...) \
    do { \
        if(LOG_IS_WARNING) { \
            LOGlogging('W', __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } \
    } while(0)

/**
* error Log macro
*/
#define LOG_ERROR(...) \
    do { \
        if(LOG_IS_ERROR) { \
            LOGlogging('E', __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } \
    } while(0)


/**
* fatal error Log macro
*/
#define LOG_FATAL(...) \
    do { \
        if(LOG_IS_FATAL) { \
            LOGlogging('F', __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } \
    } while(0)


#endif //EMBEDED_LOG_H
