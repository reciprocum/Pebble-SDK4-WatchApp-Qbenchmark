/*
   Project: Qbenchmark (watchapp)
   File   : main.c
   Author : Afonso Santos, Portugal

   Last revision: 11h30 August 29 2016
*/

#include <pebble.h>
#include <karambola/Q.h>

#include "Config.h"

Window    *my_window ;
TextLayer *text_layer ;

#define LOOP_COUNT  20000000


void
run_benchmark( void )
{
  // native floats.
  float f_pi  = 0.314159265358979323846264338327f ;
  float f_e   = 0.271828182845904523536028747135f ;
  float f_acc = 0.0f ;

  static time_t   beforeS , afterS  ;
  static uint16_t beforeMs, afterMs ;

  time_ms( &beforeS, &beforeMs ) ;
  LOGD( "float.before := %d.%d", (int)beforeS, (int)beforeMs ) ;

  for (int i = 0  ;  i < LOOP_COUNT  ;  ++i)
  {
    float f_mul = f_e * f_pi ;
          f_acc = f_acc + f_mul ;
  }

  time_ms( &afterS, &afterMs ) ;
  LOGD( "float.after := %d.%d", (int)afterS, (int)afterMs ) ;

  LOGD( "float.elapsed (count %d) := %d (ms)"
      , LOOP_COUNT
      , (int)(1000*(afterS - beforeS) + afterMs - beforeMs)
      ) ;

  LOGD( "float.f_acc := %X", (int)f_acc ) ;  // Dummy print to avoid the compiler discarding the whole thing.

  // Q15.16 floats.
  Q q_e   = Q_E ;
  Q q_acc = Q_0 ;

  time_ms( &beforeS, &beforeMs ) ;
  LOGD( "Q.before := %d.%d", (int)beforeS, (int)beforeMs ) ;

  for (int i = 0  ;  i < LOOP_COUNT  ;  ++i)
  {
    Q q_mul = Q_mul( q_e, Q_PI ) ;
    q_acc   = q_acc + q_mul ;
  }

  time_ms( &afterS, &afterMs ) ;
  LOGD( "Q.after := %d.%d", (int)afterS, (int)afterMs ) ;

  LOGD( "Q.elapsed (count %d) := %d (ms)"
      , LOOP_COUNT
      , (int)(1000*(afterS - beforeS) + afterMs - beforeMs)
      ) ;

  LOGD( "Q.q_acc := %X", (int)q_acc ) ;  // Dummy print to avoid the compiler discarding the whole thing.
}


void
app_initialize
( void )
{
  my_window = window_create();

  text_layer = text_layer_create(GRect(0, 0, 144, 20));
  window_stack_push(my_window, true);
}

void
app_finalize
( void )
{
  text_layer_destroy(text_layer) ;
  window_destroy(my_window) ;
}

int
main
( void )
{
  app_initialize( ) ;
  run_benchmark( ) ;
  app_event_loop( ) ;
  app_finalize( ) ;
}