/******************************************************************************
 *	
 * Øving 1 UCSysDes
 *	
 *****************************************************************************/

.include "io.s"  /* inkludere noen nyttige symboler (konstanter) */

/*****************************************************************************/

.text

.globl  _start
_start: /* initializing: */

        /* load pio pointers */
        lddpc r1, piob  		// R1 points to PIOB (led)
        lddpc r0, pioc			// R0 points to PIOC (buttons)
        lddpc r9, intc			// R9 points to INTC (interrupt controller)
        
        mov r4, 0xFF 			// R4 asserts all 8 bits (0xFF)
        
        /* enable LED */
        st.w r1[AVR32_PIO_PER], r4	// enable piob (led)

        /* set PIOB to output */
        st.w r1[AVR32_PIO_OER], r4

        mov r3, 5			// bit pattern for buttons

        /* enable buttons */
        st.w r0[AVR32_PIO_PER], r3	//turn on two buttons

        /* set PIOC to input */
        st.w r0[AVR32_PIO_PUER], r3	//enable two pull-up resistors

        /* set bits in IER to enable interrupts */
        st.w r0[AVR32_PIO_IER], r3	//enable two interrupt buttons

        /* set EVBA system register */
        mov r5, interrupt
        mtsr 4, r5
        
        /* set INTC-info for PIOC */
        mov r5, 0
        st.w r9[AVR32_INTC_IPR15], r5
        
        csrf 16		//enable interrupts globaly


        /* disable all lights, then turn on first light */
        st.w r1[AVR32_PIO_CODR], r4
        mov r12, 0x04			// R12 holds LED formation
        st.w r1[AVR32_PIO_SODR], r12

        mov r6, 1			// R6 given value 1 (SW0)
        mov r7, 4			// R7 given value 4 (SW2)
        mov r8, 256			// R8 = 256


loop:   /* main loop */
        sleep 1

        /* logic for interpreting buttons */

        cp.b r10, r6
        breq rightshift	// SW0 shifts right

        cp.b r10, r7
        breq leftshift	// SW2 shifts left

        ld.w r9, r0[AVR32_PIO_ISR]	// read ISR to enable new interrupts

        rjmp loop
        
interrupt:
        /* debouncing */
        mov r2, 1000	// R2 holds debounce counter
delay:	
        sub r2, 1
        brne delay

        ld.w r10, r0[AVR32_PIO_PDSR]	// R10 holds current button state
        com r10				// inverts buttons
        
        rete

leftshift:
        lsl r12, 1
        cp.w r12, 256
        moveq r12, 1
        st.w r1[AVR32_PIO_CODR], r4		// turn off all lights
        st.w r1[AVR32_PIO_SODR], r12		// set new light
        rjmp loop

rightshift:
        cp.b r12, r6
        moveq r12, r8
        lsr r12, 1
        st.w r1[AVR32_PIO_CODR], r4		// turn off all lights
        st.w r1[AVR32_PIO_SODR], r12		// set new light
        rjmp loop


/* pekere til PIO variable */

piob: 
        .int AVR32_PIOB
pioc:
        .int AVR32_PIOC
intc:
        .int AVR32_INTC
        
/*****************************************************************************/
/* data-segment */
/* alle dataområder som skal kunne skrives til må plasseres her */

.data

