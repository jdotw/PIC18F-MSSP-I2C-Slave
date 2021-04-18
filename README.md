# i2c slave on PIC18F with MSSP

The PIC18F (and others, I'm sure), include an MSSP peripheral for acting as an I2C and SPI master or slave. For my use case, I wanted to the PIC (actually, 10 of them!) to be the i2c slave for a single STM32 MCU. Within MPLAB X IDE and the MCC plugin, you can configure this peripheral ... but the result doesn't work out of the box. 

You need to do four important things:

1) Call the I2C_Open() created in the i2c1_slave.c MCC-generated file to start the peripheral and state machine

2) Enable the Global and Peripheral Interrupts (the MCC-generated main.c will have these commented out by default -- thanks MCC)

3) Enable 'Clock Stretch' in the MSSP peripheral 'Advanced' setting. The state machine code that MCC creates relies on this to hold the clock line low until it's ready for the master to begin transmitting again. Failure to enable this, results in the master transmitting before the PIC is ready. The result is an unhandled overflow. 
 
4) You should find a way to handle overflows. Look at the OVP flag in the i2c1_slave.c file that MCC creates. There's a method for checking if this flag is set, but no handling for it being set nor any code that resets it. Once this flag is set by the hardware, the PIC is wedged and will NACK any other i2c messages sent to it. That's bad! Although enabling clock stretch should prevent this particular overflow, I'm uneasy about this fatal unhandled condition. 

Once you have this working, look over the i2c_slave.c file and consider making your own implementation. The lack of handling for overflow, and other collision conditions makes me less than happy about the MCC-generated code in terms of reliability and resilience. 

Enjoy! 

-j.w