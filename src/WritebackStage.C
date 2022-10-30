#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "W.h"
#include "Stage.h"
#include "WritebackStage.h"
#include "Status.h"
#include "Debug.h"



bool WritebackStage::doClockLow(PipeReg ** pregs) {
        return false;
}

void WritebackStage::doClockHigh(PipeReg ** pregs) {

}


