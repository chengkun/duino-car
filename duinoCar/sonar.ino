// --------------------------
// timerIsr() 50uS second interrupt ISR()
// Called every time the hardware timer 1 times out.
// --------------------------
void timerIsr()
{
    trigger_pulse();                                 // Schedule the trigger pulses
    //distance_flasher();                              // Flash the onboard LED distance indicator
}

// --------------------------
// trigger_pulse() called every 50 uS to schedule trigger pulses.
// Generates a pulse one timer tick long.
// Minimum trigger pulse width for the HC-SR04 is 10 us. This system
// delivers a 50 uS pulse.
// --------------------------
void trigger_pulse()
{
      static volatile int state = 0;                 // State machine variable

      if (!(--trigger_time_count))                   // Count to 200mS
      {                                              // Time out - Initiate trigger pulse
         trigger_time_count = TICK_COUNTS;           // Reload
         state = 1;                                  // Changing to state 1 initiates a pulse
      }
    
      switch(state)                                  // State machine handles delivery of trigger pulse
      {
        case 0:                                      // Normal state does nothing
            break;
        
        case 1:                                      // Initiate pulse
           digitalWrite(trigPin, HIGH);              // Set the trigger output high
           state = 2;                                // and set state to 2
           break;
        
        case 2:                                      // Complete the pulse
        default:      
           digitalWrite(trigPin, LOW);               // Set the trigger output low
           state = 0;                                // and return state to normal 0
           break;
     }
}

// --------------------------
// echo_interrupt() External interrupt from HC-SR04 echo signal. 
// Called every time the echo signal changes state.
//
// Note: this routine does not handle the case where the timer
//       counter overflows which will result in the occassional error.
// --------------------------
void echo_interrupt()
{
  switch (digitalRead(echoPin))                     // Test to see if the signal is high or low
  {
    case HIGH:                                      // High so must be the start of the echo pulse
      echo_end = 0;                                 // Clear the end time
      echo_start = micros();                        // Save the start time
      break;
      
    case LOW:                                       // Low so must be the end of hte echo pulse
      echo_end = micros();                          // Save the end time
      echo_duration = echo_end - echo_start;        // Calculate the pulse duration
      break;
  }
}

// --------------------------
// distance_flasher() Called from the timer 1 timerIsr service routine.
// Flashes the onboard LED at a rate inversely proportional
// to distance. The closer it gets the higher the frequency.
// --------------------------
void distance_flasher()
{
      if (--range_flasher_counter <= 0)                // Decrement and test the flash timer
      {                                                // Flash timer time out
         if (echo_duration < 25000)                    // If the echo duration is within limits
         {
           range_flasher_counter = echo_duration * 2;  // Reload the timer with the current echo duration
         }
         else
         {
           range_flasher_counter = 25000;              // If out of range use a default
         }
         
         digitalWrite( onBoardLED, digitalRead( onBoardLED ) ^ 1 );   // Toggle the onboard LED
      }
}
