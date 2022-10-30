#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "PipeReg.h"
#include "PipeRegField.h"
#include "RegisterFile.h"
#include "D.h"
#include "Stage.h"
#include "DecodeStage.h"
#include "Debug.h"

bool DecodeStage::doClockLow(PipeReg ** pregs) {
	return false;	
} 

void DecodeStage::doClockHigh(PipeReg ** pregs) {
	
}

