/**
 * @file T1_Program.c
 * @author Mohammed Diaa    (mohammeddiaato@gmail.com)  Developer 
 * @author Hesham Ahmed     (Hisham4Ahmed@gmail.com)    Reviewer
 * @brief  This File is made for implementing The APIs in Interface.h
 * @version 0.3
 * @date 2025-08-30
 * 
 * @copyright Copyright (c) 2025 , Gestell Company 
 * 
 */

 #include "../../Common/Config.h"
#if TIMER1_Driver
#include "T1_Interface.h"

void mTimer1_InitFastPWMMode(uint8_t Channel)
{
    uint8_t TempA = 0;
    uint8_t TempB = 0;

    // Common Fast PWM setup (Mode 14)
    SetBit(TempA, WGM11_Bit);
    ClearBit(TempA, WGM10_Bit);

    SetBit(TempB, WGM12_Bit);
    SetBit(TempB, WGM13_Bit);

    // Select Compare Output Mode based on the channel
    #if CompareOutputMode == NonInverting
        if (Channel == OC1A_Channel)
            TempA |= NonInverting_BitMask_A;
        else if (Channel == OC1B_Channel)
            TempA |= NonInverting_BitMask_B;
    #elif CompareOutputMode == Inverting
        if (Channel == OC1A_Channel)
            TempA |= Inverting_BitMask_A;
        else if (Channel == OC1B_Channel)
            TempA |= Inverting_BitMask_B;
    #else
        // Error Handle
    #endif

    // Apply settings to TCCR1A and TCCR1B
    TCCR1A_Reg = TempA;
    TCCR1B_Reg = TempB | Timer1_Prescaller;

    // Set initial duty cycle for the selected channel only
    mTimer1_ChangeDutyCycle(initialDutyCycle, Channel);
}

void mTimer1_ChangeDutyCycle(uint8_t DutyCycle ,uint8_t Channel)
{
    uint16_t CompareValue = 0;
    ICR1_Reg=Timer1_Top;
    #if CompareOutputMode == NonInverting

    CompareValue = (Timer1_Top * (double)DutyCycle) / 100;

    #elif CompareOutputMode == Inverting
        CompareValue = Timer1_Top * (1 - (double)DutyCycle / 100);

    #endif


    if (Channel==Channel_All)
    {
        OCR1A_Reg = CompareValue;
        OCR1B_Reg = CompareValue;
    }
    else if (Channel==OC1A_Channel)
    {
        OCR1A_Reg = CompareValue;

    }
    else if (Channel==OC1B_Channel)
    {
        OCR1B_Reg = CompareValue;
    }
    else
    {
        // Handle Error
    }        


    
}
 


void mTimer1_FastPWMStop(uint8_t Channel)
{
    if (Channel==Channel_All)
    {
        TCCR1A_Reg=Timer1_OC1A_PWMStop;
        TCCR1A_Reg=Timer1_OC1B_PWMStop;

    }
    else if (Channel==OC1A_Channel)
    {

        TCCR1A_Reg=Timer1_OC1B_PWMStop;
    }
    else if (Channel==OC1B_Channel)
    {
        TCCR1A_Reg=Timer1_OC1B_PWMStop;
    }
    else
    {
        // Handle Error
    }

}

void mTimer1_TimerStop(void)
{
    TCCR1B_Reg&=Timer1_NoClkMask;
}


#endif /* TIMER1_Driver */
