class DecodeStage: public Stage
{

public: 
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
}; 
