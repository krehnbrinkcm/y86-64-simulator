class DecodeStage: public Stage
{

private: 
      void setEInput(PipeReg * dreg, uint64_t e_stat, uint64_t e_icode, uint64_t e_ifun, uint64_t e_valc, uint64_t e_vala,
uint64_t e_valb, uint64_t e_dste, uint64_t e_dstm, uint64_t e_srca, uint64_t e_srcb);

public: 
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
}; 
