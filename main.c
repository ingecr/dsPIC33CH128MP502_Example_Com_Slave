/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.135.0
        Device            :  dsPIC33CH128MP508S1
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36b
        MPLAB 	          :  MPLAB X v5.20
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"
 
#define DATA_UNDER_TEST 0xAAAA
 
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
  
    ProtocolA_DATA dataSend;
    ProtocolB_DATA dataReceive;
 
    dataSend.ProtocolA[0] = 0;                      //Initializing to known value.
    dataReceive.ProtocolB[0] = 0;                      //Initializing to known value.
 
    
    while(!MASTER_IsInterruptRequested());
    MASTER_InterruptRequestAcknowledge();
    while(MASTER_IsInterruptRequested());
    MASTER_InterruptRequestAcknowledgeComplete();
 
    //Mailbox read    
    MASTER_ProtocolBRead((ProtocolB_DATA*)&dataReceive);
    dataSend.ProtocolA[0] = dataReceive.ProtocolB[0] & 0x00FF;
    
    write_Data_Memory(0 , (dataReceive.ProtocolB[0] & 0x00FF) );
    write_Data_Memory(1 , (dataReceive.ProtocolB[0] >> 8)     );
    write_Data_Memory(2 , (dataReceive.ProtocolB[1] & 0x00FF) );
    write_Data_Memory(3 , (dataReceive.ProtocolB[1] >> 8)     );
    write_Data_Memory(4 , (dataReceive.ProtocolB[2] & 0x00FF) );
    write_Data_Memory(5 , (dataReceive.ProtocolB[2] >> 8)     );
    //Mailbox write 
    MASTER_ProtocolAWrite((ProtocolA_DATA*)&dataSend);
 
    //Issue interrupt to master
    MASTER_InterruptRequestGenerate();
    while(!MASTER_IsInterruptRequestAcknowledged());
    MASTER_InterruptRequestComplete();
    while(MASTER_IsInterruptRequestAcknowledged());
    
    
    
    while (1)
    {
        if(MASTER_IsInterruptRequested()){
        MASTER_InterruptRequestAcknowledge();
        while(MASTER_IsInterruptRequested());
        MASTER_ProtocolBRead((ProtocolB_DATA*)&dataReceive);
        MASTER_InterruptRequestAcknowledgeComplete();  
        write_Data_Memory(1 ,  dataReceive.ProtocolB[0] >> 8);
        write_Data_Memory(2 , (dataReceive.ProtocolB[1] & 0x00FF) );
        write_Data_Memory(3 , (dataReceive.ProtocolB[1] >> 8) );
        write_Data_Memory(4 , (dataReceive.ProtocolB[2] & 0x00FF) );
        write_Data_Memory(5 , (dataReceive.ProtocolB[2] >> 8) );
        
            
        }
    }
}
