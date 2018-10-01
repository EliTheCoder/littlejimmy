/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
  speakerInit();
  //speakerPlayRtttl("Unfortunately: d=8,o=4,b=120: c, c, e, g, a, g, e, f, p, f, p, e, d, e, d, c, c, c, e, g, a, g, e, 2a3, 2c");
  delay(2000);
  //speakerPlayRtttl("DropofWater: d=8,o=4,b=128: c, e, e, e, e, e, d, c, d, 4c, 4p, 2c5, 4p, b, a, g, a, g, e, d, e, 2p, p, c, e, e, e, e, e, d, c, d, 4c");
  speakerPlayRtttl("FightSong: d=4,o=4,b=140: a, c5, b, a, g, e, c, d, 8e, 8g, 8p, 8f, e, d, 8c, 16g, 16g, 16g, 16p, 16g, 16g, 16g, 8e, 8f, 8g, 2e, d, e, 8f, 8f, 8p., 8e, 8f, p., 8f, 8f, 8p, 8f, e, f, 8g, 8g, 8p., 8f#, 8g, p., a, c5, b, a, g, e, c, d, 8e, 8g, 8p, 8f, e, d, 8c, 16g, 16g, 16g, 16p, 8g, c5");
  speakerPlayRtttl("Fortnite: d=16,o=5,b=92: 4f, f, g#, a6#, 8a#6., 8g#., p, 8p, 4f, f, g#, a#6, 8a#6, 8g#, 8f, d#6, 8f, 8p, a#6, g#, f, d#6, 2f");
}
