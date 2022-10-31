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
    PipeReg * wreg = pregs[WREG];
    uint64_t stat = wreg->get(W_STAT);
    uint64_t icode = wreg->get(W_ICODE);
    uint64_t vale = wreg->get(W_VALE);
    uint64_t valm = wreg->get(W_VALM);
    uint64_t dste = wreg->get(W_DSTE);
    uint64_t dstm = wreg->get(W_DSTM);
        return true;
}

void WritebackStage::doClockHigh(PipeReg ** pregs) {

}


