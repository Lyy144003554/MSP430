#ifndef INTERRUPT_H_
#define INTERRUPT_H_
__interrupt void PORT2_ISR(void);
void pwm_action(double t,double x,double y);
__interrupt void TIMER1_A_ISR(void);
#endif /* INTERRUPT_H_ */
