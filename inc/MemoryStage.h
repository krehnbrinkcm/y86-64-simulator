class MemoryStage: public Stage
{

public:
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
      void setWInput(PipeReg * wreg, uint64_t w_stat, uint64_t w_icode, uint64_t w_vale, uint64_t w_valm, uint64_t w_dste, uint64_t w_dstm);
}; 
