#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "D.h"
#include "E.h"
#include "Stage.h"
#include "DecodeStage.h"
#include "Status.h"
#include "Debug.h"


bool DecodeStage::doClockLow(PipeReg ** pregs) {
	return false;	
} 

void DecodeStage::doClockHigh(PipeReg ** pregs) {
	
}

