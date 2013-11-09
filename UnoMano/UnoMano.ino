//includes
#include <Wire.h>

#include "UnoJoy.h"
#include "Adafruit_MCP23017.h"

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * MCP
 *
 * @see Adafruit_MCP23017.h
 */
Adafruit_MCP23017 mcp;

// {{{ preparePin

/**
 * Prepare a pin
 *
 * @param	int 	pin number
 * @param	bool	true if MCP
 */
void preparePin(int pin, bool ada) {
    if (ada == false) {
        pinMode(pin, INPUT);
        digitalWrite(pin, HIGH);
    } else {
        mcp.pinMode(pin, INPUT);
        mcp.digitalWrite(pin, HIGH);
    }
}

// }}}
// {{{ setupPins

/**
 * Prepare all pins
 *
 * 0 - 7 MCP
 * A0 & A1 left axis
 */
void setupPins() {
    //buttons on Adafruit
    for (int i = 0; i < 8; i++) {
        preparePin(i, true);
    }

    //axis
    preparePin(A0, false);
    preparePin(A1, false);
}

// }}}
// {{{ readPin

/**
 * Read a pin
 *
 * @param	int 	pin number
 * @param   bool    true if MCP
 * @return  int     value of pin
 */
int readPin(int pin, bool ada) {
    for (int i = 0; i < 8; i++) {
        if (ada == false) {
            return analogRead(pin);
        } else {
            return !mcp.digitalRead(pin);
        }
    }
}

// }}}
// {{{ getControllerData

/**
 * Read all pins
 *
 * @return	dataForController_t		all pin values
 */
dataForController_t getControllerData() {
    dataForController_t data = getBlankDataForController();

    data.triangleOn = readPin(28, true);
    data.circleOn = readPin(27, true);
    data.squareOn = readPin(26, true);
    data.crossOn = readPin(25, true);
    //data.dpadUpOn = readPin(, true);
    data.dpadDownOn = readPin(24, true);
    data.dpadLeftOn = readPin(23, true);
    data.dpadDownOn = readPin(22, true);
    data.l1On = readPin(21, true);
    //data.r1On = readPin(, true);
    //data.selectOn = readPin(, true);
    //data.startOn = readPin(, true);
    //data.homeOn = readPin(, true);

    data.leftStickX = readPin(A3, false);
    data.leftStickY = readPin(A2, false);

    return data;
}

// }}}
//////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    setupPins();
    setupUnoJoy();
    mcp.begin();
}

void loop() {
    dataForController_t data = getControllerData();
    setControllerData(data);
}
