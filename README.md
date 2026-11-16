# Electronics Laboratory: MSP430 in C

My code from the *Electronics Laboratory* course at Riga Technical University (RTU, Smart Electronic Systems programme). Each lab builds on the one before it. It starts with toggling a buzzer and ends with a working four-digit clock that has an alarm, all written in bare-metal C on an MSP430 microcontroller (MSP430G2452, 12 MHz).

The code comments are in Latvian, the language the course is taught in.

## Labs

### Lab 7: Buzzer, melodies and interrupts · [`lab07-buzzer/`](lab07-buzzer)

The buzzer is wired to P2.2 and P2.3. Buttons: SW1 on P2.5, SW2 on P2.4.

| Task | File | What it does |
|---|---|---|
| 1 | [`task1_xor_blink.c`](lab07-buzzer/task1_xor_blink.c) | Toggles the buzzer pins with XOR in a busy loop |
| 2 | [`task2_melody_loud.c`](lab07-buzzer/task2_melody_loud.c) | Plays a melody by generating square waves at note frequencies |
| 3 | [`task3_melody_quiet.c`](lab07-buzzer/task3_melody_quiet.c) | Same melody, but the pins are configured as inputs with pull resistors, which makes the speaker very quiet |
| 4 | [`task4_button_interrupt.c`](lab07-buzzer/task4_button_interrupt.c) | Plays a different note depending on which button triggers the Port 2 interrupt |

### Lab 8: Four-digit seven-segment display · [`lab08-seven-segment/`](lab08-seven-segment)

The segments are driven from P1OUT. The digit position is selected with P2.0 to P2.3.

| Task | File | What it does |
|---|---|---|
| 1 | [`task1_single_digit.c`](lab08-seven-segment/task1_single_digit.c) | Counts 0–9 on one digit |
| 2 | [`task2_digit_positions.c`](lab08-seven-segment/task2_digit_positions.c) | Cycles the digit across all four positions |
| 3 | [`task3_two_digit_number.c`](lab08-seven-segment/task3_two_digit_number.c) | Splits a number into tens and ones and multiplexes them on two digits |
| 4 | [`task4_four_digits.c`](lab08-seven-segment/task4_four_digits.c) | Multiplexes two two-digit numbers across all four digits |
| 5 | [`task5_slow_counter.c`](lab08-seven-segment/task5_slow_counter.c) | Separates the display refresh from the counter speed, so the display stays stable while the count runs slowly |

### Lab 9: Digital clock with alarm · [`lab09-clock/`](lab09-clock)

| Task | File | What it does |
|---|---|---|
| 2 | [`task2_clock_modes.c`](lab09-clock/task2_clock_modes.c) | Clock that keeps seconds, minutes and hours. SW1 switches between MM:SS and HH:MM |
| 3a | [`task3a_blinking_dot.c`](lab09-clock/task3a_blinking_dot.c) | Blinks the separator dot once per second |
| 3b | [`task3b_blinking_digits.c`](lab09-clock/task3b_blinking_digits.c) | Blinks a chosen pair of digits (used later when setting the time) |
| 4 | [`task4_short_long_press.c`](lab09-clock/task4_short_long_press.c) | Tells a short press of SW2 from a long one by switching the interrupt edge on press and release |
| 6 | [`task6_aux_functions/`](lab09-clock/task6_aux_functions) | Display, delay and blinking helpers moved into their own module (`aux_functions.h` / `.c`) |
| 8 | [`task8_set_time_and_alarm/`](lab09-clock/task8_set_time_and_alarm) | Four modes: MM:SS, HH:MM, set time, and set alarm. Short press changes the value, long press moves to the next field. The display shows letter codes for alarm on and off |
| 9 | [`task9_alarm_melody/`](lab09-clock/task9_alarm_melody) | When the time matches the alarm, it plays the melody from lab 7. SW1 dismisses it |

## How the display multiplexing works

There is only one set of segment lines (P1OUT) for all four digits. The main loop lights one digit at a time: it switches off all four positions, writes that digit's segment pattern, then turns on its position bit on P2. It repeats this every ~1 ms, which is fast enough that your eye sees all four digits lit at once. Timekeeping runs off a counter in the same loop: every 1000 refreshes is one second.

## Building

The code was written in Energia for the course's MSP430G2452 board. Open a task file (or a task folder, for tasks 6–9 of lab 9) as a project and flash it to the board.
