/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

/** \file
 *
 *  Main source file for the posts printer demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "Joystick.h"
#include "instructions.h"
#include "settings.h"
#include "egg_cycles.h"

extern const uint8_t image_data[0x12c1] PROGMEM;

// Main entry point.
int main(void) {
	// We'll start by performing hardware and peripheral setup.
	SetupHardware();
	// We'll then enable global interrupts for our use.
	GlobalInterruptEnable();
	// Once that's done, we'll enter an infinite loop.
	for (;;)
	{
		// We need to run our task to process and deliver data for our IN and OUT endpoints.
		HID_Task();
		// We also need to run the main USB management task.
		USB_USBTask();
	}
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void) {
	// We need to disable watchdog if enabled by bootloader/fuses.
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// We need to disable clock division before initializing the USB hardware.
	clock_prescale_set(clock_div_1);
	// We can then initialize our hardware and peripherals, including the USB stack.

	#ifdef ALERT_WHEN_DONE
	// Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
	#warning LED and Buzzer functionality enabled. All pins on both PORTB and \
PORTD will toggle when printing is done.
	DDRD  = 0xFF; //Teensy uses PORTD
	PORTD =  0x0;
                  //We'll just flash all pins on both ports since the UNO R3
	DDRB  = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
	PORTB =  0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
	#endif
	// The USB stack should be initialized last.
	USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
	// We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
	// We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;

	// We setup the HID report endpoints.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	// We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
	// We can handle two control requests: a GetReport and a SetReport.

	// Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
	// If the device isn't connected and properly configured, we can't do anything here.
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

	// We'll start with the OUT endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
	// We'll check to see if we received something on the OUT endpoint.
	if (Endpoint_IsOUTReceived())
	{
		// If we did, and the packet has data, we'll react to it.
		if (Endpoint_IsReadWriteAllowed())
		{
			// We'll create a place to store our data received from the host.
			USB_JoystickReport_Output_t JoystickOutputData;
			// We'll then take in that data, setting it up in our storage.
			while(Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError);
			// At this point, we can react to this data.

			// However, since we're not doing anything with this data, we abandon it.
		}
		// Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
		Endpoint_ClearOUT();
	}

	// We'll then move on to the IN endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
	// We first check to see if the host is ready to accept data.
	if (Endpoint_IsINReady())
	{
		// We'll create an empty report.
		USB_JoystickReport_Input_t JoystickInputData;
		// We'll then populate this report with what we want to send to the host.
		GetNextReport(&JoystickInputData);
		// Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
		while(Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);
		// We then send an IN packet on this endpoint.
		Endpoint_ClearIN();
	}
}

void reset_report(USB_JoystickReport_Input_t* const ReportData) {
	memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;
}

void take_action(action_t action, USB_JoystickReport_Input_t* const ReportData) {
	switch (action)
	{
		case press_a:
			ReportData->Button |= SWITCH_A;
			break;

		case press_b:
			ReportData->Button |= SWITCH_B;
			break;

		case press_x:
			ReportData->Button |= SWITCH_X;
			break;

		case press_y:
			ReportData->Button |= SWITCH_Y;
			break;

		case press_r:
			ReportData->Button |= SWITCH_R;
			break;

		case press_l:
			ReportData->Button |= SWITCH_L;
			break;

		case press_plus:
			ReportData->Button |= SWITCH_PLUS;
			break;

		case press_home:
			ReportData->Button |= SWITCH_HOME;
			break;

		case hang:
			reset_report(ReportData);
			break;

		case L_left:
			ReportData->LX = STICK_MIN;
			break;
		
		case L_right:
			ReportData->LX = STICK_MAX;
			break;

		case L_up:
			ReportData->LY = STICK_MIN;
			break;

		case L_down:
			ReportData->LY = STICK_MAX;
			break;

		case L_up_right:
			ReportData->LY = STICK_MIN;
			ReportData->LX = STICK_MAX;
			break;

		case L_up_right_slight:
			ReportData-> LY = 60;
			ReportData-> LX = 200;
			break;

		case L_left_slight:
			ReportData-> LX = 100;
			break;
		
		case L_right_slight:
			ReportData-> LX = 160;
			break;

		case L_up_slight:
			ReportData-> LY = 100;
			break;
			
		case L_down_slight:
			ReportData-> LY = 160;
			break;

		default:
			reset_report(ReportData);
			break;

	}
}


typedef enum {
	SYNC_CONTROLLER,
	BREATHE,
	FLY_TO_NURSERY,
	IN_OUT_NURSERY,
	GO_TO_CIRCLE1,
	CIRCLE1,
	APPROACH_NPC,
	SPEAK,
	GO_TO_CIRCLE2,
	GO_TO_CIRCLE3,
	OPEN_BOX,
	SELECT_COL,
	GRAB_EGGS1_PRE,
	GRAB_EGGS2_PRE,
	GRAB_EGGS3_PRE,
	GRAB_EGGS4_PRE,
	GRAB_EGGS5_PRE,
	GRAB_EGGS6_PRE,
	SELECT_COL2,
	GRAB_EGGS1_POST,
	GRAB_EGGS2_POST,
	GRAB_EGGS3_POST,
	GRAB_EGGS4_POST,
	GRAB_EGGS5_POST,
	GRAB_EGGS6_POST,
	CLOSE_BOX,
	CIRCLE_CW,
	FLY_TO_NURSERY2,
	SAVE,
	SLEEP,
	DONE
} State_t;

State_t state = SYNC_CONTROLLER;

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

int duration_count = 0;
int bufindex = 0;
int portsval = 0;
uint8_t num_boxes = number_of_boxes;
uint8_t egg_count = initial_egg_checks;
uint8_t egg_set = 1;
int breeding_duration = 5500;
uint8_t new_round = 0;

inline void do_steps(const command_t* steps, uint16_t steps_size, USB_JoystickReport_Input_t* const ReportData, State_t nextState, int egg_counting) {
	take_action(steps[bufindex].action, ReportData);
	duration_count ++;
	
	if (duration_count > steps[bufindex].duration)
	{
		bufindex ++;
		duration_count = 0;
	}

	if (bufindex > steps_size - 1) 
	{
		bufindex = 0;
		duration_count = 0;
		if (egg_counting) {
			egg_count--;
			egg_set++;

			if (egg_set >= 7 ) {
				egg_set = 1;
			}
		}


		state = nextState;
		reset_report(ReportData);
	}
}


// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData) {

	// Prepare an empty report
	reset_report(ReportData);

	// Repeat ECHOES times the last report
	if (echoes > 0)
	{
		memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
		echoes--;
		return;
	}

	// States and moves management
	switch (state)
	{
		case SYNC_CONTROLLER:
			bufindex = 0;
			duration_count = 0;
			state = BREATHE;
			if (flame_body) {
				breeding_duration = (1.046 * (egg_cycles[nat_dex_number]/2)) - 32.583;
			}
			else {
				breeding_duration = (1.046 * egg_cycles[nat_dex_number]) - 32.583;
			}
			break;
		
		case BREATHE:
			do_steps(wake_up_hang, ARRAY_SIZE(wake_up_hang), ReportData, FLY_TO_NURSERY, 0);
			break;

		case FLY_TO_NURSERY:
			if (egg_set > 1) {
				do_steps(fly_to_breading_steps, ARRAY_SIZE(fly_to_breading_steps), ReportData, GO_TO_CIRCLE3, 0);
			}
			else if (new_round) {
				do_steps(fly_to_breading_steps, ARRAY_SIZE(fly_to_breading_steps), ReportData, GO_TO_CIRCLE1, 0);
			}
			else {
				do_steps(fly_to_breading_steps, ARRAY_SIZE(fly_to_breading_steps), ReportData, IN_OUT_NURSERY, 0);
			}
			break;

		case IN_OUT_NURSERY:
			do_steps(go_in_out_nursery, ARRAY_SIZE(go_in_out_nursery), ReportData, GO_TO_CIRCLE1, 0);
			break;

		case GO_TO_CIRCLE1:
			if (new_round && egg_count > 0) {
				do_steps(go_to_circle1, ARRAY_SIZE(go_to_circle1), ReportData, APPROACH_NPC, 0);
			}
			else if (egg_count > 0) {
				do_steps(go_to_circle1, ARRAY_SIZE(go_to_circle1), ReportData, CIRCLE1, 0);
			}
			else {
				egg_set = 1;
				state = GO_TO_CIRCLE3;
			}
			break;

		case CIRCLE1:
			duration_count++;

			if (duration_count % 48 <= 11) {
				take_action(L_left, ReportData);
			}
			else if (duration_count % 48 <= 23) {
				take_action(L_down, ReportData);
			}
			else if (duration_count % 48 <= 35) {
				take_action(L_right, ReportData);
			}
			else if (duration_count % 48 <= 47) {
				take_action(L_up, ReportData);
			}


			if (duration_count > 350) {
				duration_count = 0;
				bufindex = 0;
				state = APPROACH_NPC;
			}

			break;
			
		case APPROACH_NPC:
			new_round = 0;
			do_steps(approach, ARRAY_SIZE(approach), ReportData, SPEAK, 0);
			break;

		case SPEAK:
			do_steps(speak, ARRAY_SIZE(speak), ReportData, GO_TO_CIRCLE2, 1);
			break;

		case GO_TO_CIRCLE2:
			if (egg_count >= 1) {
				do_steps(go_to_circle2, ARRAY_SIZE(go_to_circle2), ReportData, CIRCLE1, 0);
			}
			else {
				egg_set = 1;
				state = GO_TO_CIRCLE3;
			}
			break;

		case GO_TO_CIRCLE3:
			do_steps(go_to_circle3, ARRAY_SIZE(go_to_circle3), ReportData, OPEN_BOX, 0);
			break;

		case OPEN_BOX:
			do_steps(open_box, ARRAY_SIZE(open_box), ReportData, SELECT_COL, 0);
			break;

		case SELECT_COL:
			switch(egg_set) {
				case 1:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS1_PRE, 0);
					break;
				case 2:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS2_PRE, 0);
					break;
				case 3:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS3_PRE, 0);
					break;
				case 4:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS4_PRE, 0);
					break;
				case 5:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS5_PRE, 0);
					break;
				case 6:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS6_PRE, 0);
					break;
			}
			break;

		case GRAB_EGGS1_PRE:
			do_steps(grab_eggs1_pre, ARRAY_SIZE(grab_eggs1_pre), ReportData, SELECT_COL2, 0);
			break;

		case GRAB_EGGS2_PRE:
			do_steps(grab_eggs2_pre, ARRAY_SIZE(grab_eggs2_pre), ReportData, SELECT_COL2, 0);
			break;

		case GRAB_EGGS3_PRE:
			do_steps(grab_eggs3_pre, ARRAY_SIZE(grab_eggs3_pre), ReportData, SELECT_COL2, 0);
			break;

		case GRAB_EGGS4_PRE:
			do_steps(grab_eggs4_pre, ARRAY_SIZE(grab_eggs4_pre), ReportData, SELECT_COL2, 0);
			break;

		case GRAB_EGGS5_PRE:
			do_steps(grab_eggs5_pre, ARRAY_SIZE(grab_eggs5_pre), ReportData, SELECT_COL2, 0);
			break;

		case GRAB_EGGS6_PRE:
			do_steps(grab_eggs6_pre, ARRAY_SIZE(grab_eggs6_pre), ReportData, SELECT_COL2, 0);
			break;

		case SELECT_COL2:
			switch(egg_set) {
				case 1:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS1_POST, 0);
					break;
				case 2:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS2_POST, 0);
					break;
				case 3:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS3_POST, 0);
					break;
				case 4:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS4_POST, 0);
					break;
				case 5:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS5_POST, 0);
					break;
				case 6:
					do_steps(select_col, ARRAY_SIZE(select_col), ReportData, GRAB_EGGS6_POST, 0);
					break;
			}
			break;
		
		case GRAB_EGGS1_POST:
			do_steps(grab_eggs1_post, ARRAY_SIZE(grab_eggs1_post), ReportData, CLOSE_BOX, 0);
			break;

		case GRAB_EGGS2_POST:
			do_steps(grab_eggs2_post, ARRAY_SIZE(grab_eggs2_post), ReportData, CLOSE_BOX, 0);
			break;

		case GRAB_EGGS3_POST:
			do_steps(grab_eggs3_post, ARRAY_SIZE(grab_eggs3_post), ReportData, CLOSE_BOX, 0);
			break;

		case GRAB_EGGS4_POST:
			do_steps(grab_eggs4_post, ARRAY_SIZE(grab_eggs4_post), ReportData, CLOSE_BOX, 0);
			break;

		case GRAB_EGGS5_POST:
			do_steps(grab_eggs5_post, ARRAY_SIZE(grab_eggs5_post), ReportData, CLOSE_BOX, 0);
			break;

		case GRAB_EGGS6_POST:
			do_steps(grab_eggs6_post, ARRAY_SIZE(grab_eggs6_post), ReportData, CLOSE_BOX, 0);
			break;

		case CLOSE_BOX:
			do_steps(close_box, ARRAY_SIZE(close_box), ReportData, CIRCLE_CW, 1);
			break;

		case CIRCLE_CW:
			duration_count++;

			if (duration_count % 48 <= 11) {
				take_action(L_right, ReportData);
			}
			else if (duration_count % 48 <= 23) {
				take_action(L_down, ReportData);
			}
			else if (duration_count % 48 <= 35) {
				take_action(L_left, ReportData);
			}
			else if (duration_count % 48 <= 47) {
				take_action(L_up, ReportData);
			}
			// if (duration_count > (breeding_duration - 500) && duration_count % 24 >= 0 && duration_count % 24 <= 5) {
			if (duration_count % 24 >= 0 && duration_count % 24 <= 5) {
				take_action(press_a, ReportData);
			}


			if (duration_count > breeding_duration + 4200) {
			//if (duration_count > 1) {
				duration_count = 0;
				bufindex = 0;
				//break;

				if (egg_set == 1) {
					egg_count = subsequent_egg_checks;
					num_boxes--;
					
					if ( (save == 1) || ((save == 2) && (num_boxes) <= 0) ) {
						state = SAVE;
					}
					else if (num_boxes > 0) {
						new_round = 1;
						state = FLY_TO_NURSERY;
					}
					else {
						state = SLEEP;
					}
				}
				else {
					state = FLY_TO_NURSERY;
				}
			}

			break;

		case SAVE:
			if (num_boxes > 0) {
				new_round = 1;
				do_steps(save_game, ARRAY_SIZE(save_game), ReportData, FLY_TO_NURSERY, 0);
			}
			else {
				do_steps(save_game, ARRAY_SIZE(save_game), ReportData, SLEEP, 0);
			}
			break;
			
		case SLEEP:
			do_steps(sleep, ARRAY_SIZE(sleep), ReportData, DONE, 0);
			break;

		case DONE:
			#ifdef ALERT_WHEN_DONE
			portsval = ~portsval;
			PORTD = portsval; //flash LED(s) and sound buzzer if attached
			PORTB = portsval;
			_delay_ms(250);
			#endif
			return;
	}

	// // Inking
	// if (state != SYNC_CONTROLLER && state != SYNC_POSITION)
	// 	if (pgm_read_byte(&(image_data[(xpos / 8) + (ypos * 40)])) & 1 << (xpos % 8))
	// 		ReportData->Button |= SWITCH_A;

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;

}


